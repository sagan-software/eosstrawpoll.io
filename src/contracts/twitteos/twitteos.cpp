
#include <eosiolib/action.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>

#include "twitteos.hpp"

using eosio::const_mem_fun;
using eosio::indexed_by;
using std::string;

// @abi action
void twitteos::create(
    const account_name author,
    const string &text)
{
    require_auth(author);

    // TODO check text length

    post_index posts(_self, author);
    auto new_post = posts.emplace(author, [&](auto &p) {
        p.id = posts.available_primary_key();
        p.text = text;
        p.created = now();
        p.parent_id = NULL_PARENT_ID;
        p.parent_author = NULL_PARENT_AUTHOR;
    });

    eosio::print("Created post with ID ", new_post->id);
}

// @abi action
void twitteos::reply(
    const account_name author,
    const string &text,
    const uuid parent_id,
    const account_name parent_author)
{
    require_auth(author);

    // TODO check text length

    post_index parent_posts(_self, parent_author);
    auto itr = parent_posts.find(parent_id);
    eosio_assert(itr != parent_posts.end(), "post doesn't exist");

    post_index posts(_self, author);
    auto new_post = posts.emplace(author, [&](auto &p) {
        p.id = posts.available_primary_key();
        p.text = text;
        p.created = now();
        p.parent_id = parent_id;
        p.parent_author = parent_author;
    });

    eosio::print("Created reply with ID ", new_post->id);
}

// @abi action
void twitteos::update(
    const account_name author,
    const string &text,
    const uuid post_id)
{
    require_auth(author);

    // Check if post exists
    post_index posts(_self, author);
    auto itr = posts.find(post_id);
    eosio_assert(itr != posts.end(), "post doesn't exist");

    posts.modify(itr, author /*payer*/, [&](auto &post) {
        post.text = text;
    });

    eosio::print("Updated post: ", post_id);
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

    eosio::print("Deleted post: ", post_id);
}

EOSIO_ABI(twitteos, (create)(reply)(update)(destroy))
