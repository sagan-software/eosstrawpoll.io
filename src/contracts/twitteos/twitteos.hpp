#pragma once

#include <eosiolib/action.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>

using eosio::const_mem_fun;
using eosio::indexed_by;
using std::string;

typedef uint64_t uuid;
typedef uint32_t timestamp;

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

// typedef eosio::multi_index<
//     N(post),
//     post,
//     indexed_by<N(created), const_mem_fun<post, timestamp, &post::by_created>>>
//     post_index;

typedef eosio::multi_index<
    N(posts),
    post>
    post_index;

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
    static const uuid NULL_PARENT_ID = 0;
    static const account_name NULL_PARENT_AUTHOR = N();
};
