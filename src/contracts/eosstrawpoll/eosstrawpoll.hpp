#pragma once

#include <eosiolib/action.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/multi_index.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/singleton.hpp>
#include <sstream>
#include <string>

using eosio::asset;
using eosio::const_mem_fun;
using eosio::indexed_by;
using std::set;
using std::string;
using std::vector;

typedef uint64_t uuid;
typedef uint32_t timestamp;

// @abi table config i64
struct config_t
{
    uuid id;
    uint16_t max_title_length = 100;
    uint32_t max_description_length = 2000;
    uint16_t max_options_size = 100;
    uint16_t max_option_length = 280;
    uint16_t max_whitelist_size = 300;
    uint16_t max_blacklist_size = 300;
    uint16_t min_poll_age = 60 * 5; // 5 minutes
    vector<account_name> banlist;

    EOSLIB_SERIALIZE(config_t, (id)(max_title_length)(max_options_size)(max_option_length)(max_whitelist_size)(max_blacklist_size)(min_poll_age)(banlist))
};

typedef eosio::singleton<N(config), config_t> config_index;

// @abi table polls i64
struct poll_t
{
    uuid id;
    uint16_t num_options;
    uint16_t min_choices;
    uint16_t max_choices;
    vector<account_name> whitelist;
    vector<account_name> blacklist;
    timestamp open_time;
    timestamp close_time;

    uuid primary_key() const { return id; }

    bool has_opened() const { return open_time == 0 || open_time <= now(); }

    bool is_closed() const { return close_time > 0 && close_time <= now(); }

    EOSLIB_SERIALIZE(poll_t, (id)(num_options)(min_choices)(max_choices)(whitelist)(blacklist)(open_time)(close_time))
};

typedef eosio::multi_index<N(polls), poll_t> polls_index;

class eosstrawpoll : public eosio::contract
{

  public:
    eosstrawpoll(account_name self)
        : contract(self)
    {
    }

    void create(
        const account_name creator,
        const string &title,
        const string &description,
        const vector<string> &options,
        const vector<account_name> &whitelist,
        const vector<account_name> &blacklist,
        const uint16_t min_choices,
        const uint16_t max_choices,
        const timestamp open_time,
        const timestamp close_time);

    void close(
        const account_name creator,
        const uuid poll_id);

    void destroy(
        const account_name creator,
        const uuid poll_id);

    void vote(
        const account_name creator,
        const uuid poll_id,
        const account_name voter,
        const vector<uint16_t> &choices);

    void comment(
        const account_name creator,
        const uuid poll_id,
        const account_name commenter,
        const string &content);

    void update(
        const account_name creator,
        const uuid poll_id,
        const string &new_description);
};
