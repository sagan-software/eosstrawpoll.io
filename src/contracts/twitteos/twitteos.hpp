#pragma once

#include <eosiolib/action.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/multi_index.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/singleton.hpp>
#include <string>

using eosio::const_mem_fun;
using eosio::indexed_by;
using std::string;

typedef uint64_t uuid;
typedef uint64_t timestamp;
typedef string ipfs_hash;

// @abi table posts i64
struct post
{
    uuid id;
    string text;
    timestamp created;

    uuid parent_id;
    account_name parent_author;

    uuid primary_key() const { return id; }
    timestamp by_created() const { return created; }

    EOSLIB_SERIALIZE(post, (id)(text)(created)(parent_id)(parent_author))
};

typedef eosio::multi_index<
    N(posts),
    post,
    indexed_by<N(created), const_mem_fun<post, timestamp, &post::by_created>>>
    post_index;

// @abi table profile i64
struct profile_t
{
    string display_name = "";
    string biography = "";
    string location = "";
    ipfs_hash profile_photo = "";
    ipfs_hash header_photo = "";
    uint64_t num_posts = 0;
    uint64_t num_following = 0;
    uint64_t num_followers = 0;
    uint64_t num_liked = 0;
    timestamp created;
    uuid last_post_id;
};

typedef eosio::singleton<N(profile), profile_t> profile_singleton;

class twitteos : public eosio::contract
{

  public:
    explicit twitteos(account_name self)
        : contract(self)
    {
    }

    void create(const account_name author, const string &text);
    void reply(const account_name author, const string &text, const uuid parent_id, const account_name parent_author);
    void update(const account_name author, const string &text, const uuid post_id);
    void destroy(const account_name author, const uuid post_id);

  private:
    profile_t get_or_create_profile(const account_name author);
};
