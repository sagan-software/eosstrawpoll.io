#pragma once

#include <eosiolib/eosio.hpp>

using std::string;
using std::vector;

typedef account_name uuid;
typedef uint32_t timestamp;
typedef account_name reaction_name;

constexpr uint8_t MIN_ID_LENGTH = 1;
constexpr uint8_t MAX_ID_LENGTH = 12;
constexpr uint16_t MAX_TITLE_LENGTH = 100;
constexpr uint32_t MAX_DESCRIPTION_LENGTH = 2000;
constexpr uint16_t MAX_OPTIONS_SIZE = 100;
constexpr uint16_t MAX_OPTION_LENGTH = 280;
constexpr uint16_t MAX_ACCOUNT_LIST_SIZE = 500;
constexpr uint16_t MIN_POLL_AGE_SECONDS = 60;
constexpr uint8_t MAX_APP_LABEL_LENGTH = 50;
constexpr uint32_t MAX_JSON_LENGTH = 2500;
constexpr uint16_t MAX_COMMENT_LENGTH = 1000;

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
        const account_name poll_creator,
        const uuid poll_id,
        const string &title,
        const string &description,
        const vector<string> &options,
        const vector<account_name> &whitelist,
        const vector<account_name> &blacklist,
        const uint16_t min_choices,
        const uint16_t max_choices,
        const timestamp open_time,
        const timestamp close_time,
        const string &app_label);

    void close(
        const account_name poll_creator,
        const uuid poll_id,
        const string &app_label);

    void vote(
        const account_name poll_creator,
        const uuid poll_id,
        const account_name voter,
        const vector<uint16_t> &choices,
        const string &app_label);

    void comment(
        const account_name poll_creator,
        const uuid poll_id,
        const account_name commenter,
        const string &content,
        const string &app_label);

    void react(
        const account_name poll_creator,
        const uuid poll_id,
        const account_name reacter,
        const reaction_name reaction,
        const string &app_label);

    void settings(
        const account_name account,
        const string &json_metadata,
        const vector<account_name> default_whitelist,
        const vector<account_name> default_blacklist,
        const string &app_label);
};
