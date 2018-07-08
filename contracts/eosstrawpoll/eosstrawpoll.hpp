#pragma once

#include <eosiolib/eosio.hpp>

using std::string;
using std::vector;

typedef account_name uuid;
typedef uint32_t timestamp;
typedef account_name reaction_name;

class eosstrawpoll : public eosio::contract
{

  public:
    eosstrawpoll(account_name self)
        : contract(self)
    {
    }

    void create(
        const account_name poll_creator,
        const uuid poll_name,
        const string &title,
        const string &description,
        const vector<string> &options,
        const vector<account_name> &whitelist,
        const vector<account_name> &blacklist,
        const uint16_t min_choices,
        const uint16_t max_choices,
        const timestamp open_time,
        const timestamp close_time,
        const string &metadata);

    void close(
        const account_name poll_creator,
        const uuid poll_name,
        const string &metadata);

    void vote(
        const account_name poll_creator,
        const uuid poll_name,
        const account_name voter,
        const vector<uint16_t> &choices,
        const string &metadata);

    void comment(
        const account_name poll_creator,
        const uuid poll_name,
        const account_name commenter,
        const string &content,
        const string &metadata);

    void react(
        const account_name poll_creator,
        const uuid poll_name,
        const account_name reacter,
        const reaction_name reaction,
        const string &metadata);

    void settings(
        const account_name account,
        const vector<account_name> default_whitelist,
        const vector<account_name> default_blacklist,
        const string &metadata);
};
