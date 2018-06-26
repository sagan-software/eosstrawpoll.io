
// #include <algorithm>
// #include <cmath>
#include <eosiolib/action.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/transaction.hpp>
#include <inttypes.h>
#include <string>

#include "eosstrawpoll.hpp"

using eosio::asset;
using eosio::const_mem_fun;
using eosio::indexed_by;
using std::string;
using std::vector;

template <typename T>
T clamp(const T &n, const T &lower, const T &upper)
{
    return std::max(lower, std::min(n, upper));
}

template <typename T>
bool has_duplicates(const vector<T> &items)
{
    vector<T> sorted(items);
    auto end = sorted.end();
    std::sort(sorted.begin(), end);
    return std::adjacent_find(sorted.begin(), end) != end;
}

// @abi action
void eosstrawpoll::create(
    const account_name creator,
    const string &title,
    const string &description,
    const vector<string> &options,
    const vector<account_name> &whitelist,
    const vector<account_name> &blacklist,
    const uint16_t min_choices,
    const uint16_t max_choices,
    const timestamp open_time,
    const timestamp close_time)
{
    require_auth(creator);

    // check that at least 2 options have been specified
    eosio_assert(options.size() >= 2, "must have at least 2 options");

    // check that there are no empty options
    for (auto &option : options)
    {
        eosio_assert(!option.empty(), "empty options are not allowed");
    }

    // check that there are no duplicate options
    eosio_assert(!has_duplicates(options), "duplicate options are not allowed");

    // check that title is less than or equal to the max title length

    // check that options are less than or equal to the max option length

    // check that accounts are not in both whitelist and blacklist

    // check that close time is not before open time
    eosio_assert(
        close_time == 0 || close_time > open_time,
        "close time must be after open time");

    // check that close time has not already past
    eosio_assert(
        close_time == 0 || close_time > now(),
        "close time must not be in the past");

    // create the poll
    polls_index polls(_self, creator);
    const uint16_t num_options = options.size();
    auto poll = polls.emplace(creator, [&](auto &p) {
        p.id = polls.available_primary_key();
        p.num_options = options.size();
        p.min_choices = clamp<uint16_t>(min_choices, 1, num_options);
        p.max_choices = clamp<uint16_t>(max_choices, p.min_choices, num_options);
        p.whitelist = whitelist;
        p.blacklist = blacklist;
        p.open_time = std::max(open_time, now());
        p.close_time = close_time;
    });

    eosio::print("successfully created poll (creator=", creator, ", poll_id=", poll->id, ")");
}

// @abi action
void eosstrawpoll::close(
    const account_name creator,
    const uuid poll_id)
{
    require_auth(creator);

    // check if poll exists
    polls_index polls(_self, creator);
    auto poll = polls.find(poll_id);
    eosio_assert(poll != polls.end(), "poll doesn't exist");

    // check if poll is scheduled to close
    eosio_assert(poll->close_time == 0, "poll is already scheduled to close");

    // check if poll is already closed
    eosio_assert(!poll->is_closed(), "poll is already closed");

    // close poll
    polls.modify(poll, creator, [&](auto &p) {
        p.close_time = now();
    });

    eosio::print("successfully closed poll (creator=", creator, ", poll_id=", poll->id, ")");
}

// @abi action
void eosstrawpoll::destroy(
    const account_name creator,
    const uuid poll_id)
{
    require_auth(creator);

    // check if poll exists
    polls_index polls(_self, creator);
    auto poll = polls.find(poll_id);
    eosio_assert(poll != polls.end(), "poll doesn't exist");

    // erase poll
    polls.erase(poll);

    eosio::print("successfully destroyed poll (creator=", creator, ", poll_id=", poll_id, ")");
}

// @abi action
void eosstrawpoll::vote(
    const account_name creator,
    const uuid poll_id,
    const account_name voter,
    const vector<uint16_t> &choices)
{
    require_auth(voter);

    // check if poll exists
    polls_index polls(_self, creator);
    auto poll = polls.find(poll_id);
    eosio_assert(poll != polls.end(), "poll doesn't exist");

    // check if poll has opened yet
    eosio_assert(poll->has_opened(), "poll has not opened yet");

    // check if poll is closed
    eosio_assert(!poll->is_closed(), "poll is closed");

    // check number choices can be selected
    const auto num_choices = choices.size();
    eosio_assert(num_choices >= poll->min_choices, "too few choices");
    eosio_assert(num_choices <= poll->max_choices, "too many choices");

    // check for duplicates
    eosio_assert(!has_duplicates(choices), "duplicate choices are not allowed");

    // check if choices are valid
    const auto max_choice = poll->num_options - 1;
    for (auto &choice : choices)
    {
        char error_msg[99];
        sprintf(error_msg, "received invalid choice %d, must be within 0-%d", choice, max_choice);
        eosio_assert(choice >= 0 && choice <= max_choice, error_msg);
    }

    // check if poll has whitelist, and if voter is on whitelist
    const auto wl = poll->whitelist;
    eosio_assert(
        wl.empty() || std::find(wl.begin(), wl.end(), voter) != wl.end(),
        "voter is not on whitelist");

    // check if voter is on blacklist
    const auto bl = poll->blacklist;
    eosio_assert(
        bl.empty() || std::find(bl.begin(), bl.end(), voter) == bl.end(),
        "voter is blacklisted");

    eosio::print("successfully cast vote on poll (id=", poll_id, ", poll_ref_id=", "", ")");
}

asset eosstrawpoll::calculate_holdings(const account_name account)
{
    // get unstaked balance from table: eosio.token account accounts

    // get staked balance and RAM from table: eosio account userres

    // get exchange rate of RAM for system token from table: eosio eosio rammarket

    // sum up unstaked balance, staked balance, and RAM value

    return asset();
}

EOSIO_ABI(eosstrawpoll, (create)(close)(destroy)(vote))
