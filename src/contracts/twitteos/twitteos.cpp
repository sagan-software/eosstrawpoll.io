
#include <eosiolib/action.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <inttypes.h>
#include <string>

#include "twitteos.hpp"

using eosio::const_mem_fun;
using eosio::indexed_by;
using std::string;

constexpr uuid NULL_UUID = 0;
constexpr account_name NULL_AUTHOR = N();
constexpr size_t MIN_POST_SIZE = 1;
constexpr size_t MAX_POST_SIZE = 280;

void assert_text_size(const string &text)
{
    size_t text_size = text.size();

    char too_short_msg[99];
    sprintf(too_short_msg, "post text is too short, must be greater than or equal to %d character(s) long", MIN_POST_SIZE);
    eosio_assert(text_size >= MIN_POST_SIZE, too_short_msg);

    char too_long_msg[99];
    sprintf(too_long_msg, "post text is too long, must be less than or equal to %d character(s) long", MAX_POST_SIZE);
    eosio_assert(text_size <= MAX_POST_SIZE, too_long_msg);
}

// @abi action
void twitteos::create(
    const account_name author,
    const string &text)
{
    require_auth(author);
    assert_text_size(text);

    post_index posts(_self, author);
    auto new_post = posts.emplace(author, [&](auto &p) {
        p.id = posts.available_primary_key();
        p.text = text;
        p.created = now();
        p.parent_id = NULL_UUID;
        p.parent_author = NULL_AUTHOR;
    });

    profile_t profile = get_or_create_profile(author);
    profile.num_posts += 1;
    profile.last_post_id = new_post->id;
    profile_singleton profile_index(_self, author);
    profile_index.set(profile, author);

    eosio::print("successfully created post (id=", new_post->id, ")");
}

// @abi action
void twitteos::reply(
    const account_name author,
    const string &text,
    const uuid parent_id,
    const account_name parent_author)
{
    require_auth(author);
    assert_text_size(text);

    post_index parent_posts(_self, parent_author);
    auto itr = parent_posts.find(parent_id);
    eosio_assert(itr != parent_posts.end(), "parent post doesn't exist");

    post_index posts(_self, author);
    auto new_post = posts.emplace(author, [&](auto &p) {
        p.id = posts.available_primary_key();
        p.text = text;
        p.created = now();
        p.parent_id = parent_id;
        p.parent_author = parent_author;
    });

    profile_t profile = get_or_create_profile(author);
    profile.num_posts += 1;
    profile.last_post_id = new_post->id;
    profile_singleton profile_index(_self, author);
    profile_index.set(profile, author);

    eosio::print("successfully created reply (id=", new_post->id, ")");
}

// @abi action
void twitteos::update(
    const account_name author,
    const string &text,
    const uuid post_id)
{
    require_auth(author);
    assert_text_size(text);

    // Check if post exists
    post_index posts(_self, author);
    auto itr = posts.find(post_id);
    eosio_assert(itr != posts.end(), "post doesn't exist");

    posts.modify(itr, author /*payer*/, [&](auto &post) {
        post.text = text;
    });

    eosio::print("successfully updated post (id=", post_id, ")");
}

// @abi action
void twitteos::destroy(
    const account_name author,
    const uuid post_id)
{
    require_auth(author);

    // Check if post exists
    post_index posts(_self, author);
    auto itr = posts.find(post_id);
    eosio_assert(itr != posts.end(), "post doesn't exist");

    // Remove post
    posts.erase(itr);

    profile_t profile = get_or_create_profile(author);
    profile.num_posts -= 1;
    profile_singleton profile_index(_self, author);
    profile_index.set(profile, author);

    eosio::print("successfully deleted post (id=", post_id, ")");
}

profile_t twitteos::get_or_create_profile(const account_name author)
{
    profile_singleton profile_index(_self, author);

    if (profile_index.exists())
    {
        return profile_index.get();
    }
    else
    {
        profile_t profile = profile_t{};
        profile.created = now();
        profile_index.set(profile, author);
        return profile;
    }
}

EOSIO_ABI(twitteos, (create)(reply)(update)(destroy))
