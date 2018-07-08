#include "eosstrawpoll.hpp"

constexpr uint8_t MIN_ID_LENGTH = 1;
constexpr uint8_t MAX_ID_LENGTH = 12;
constexpr uint16_t MAX_TITLE_LENGTH = 100;
constexpr uint32_t MAX_DESCRIPTION_LENGTH = 2000;
constexpr uint16_t MAX_OPTIONS_SIZE = 100;
constexpr uint16_t MAX_OPTION_LENGTH = 280;
constexpr uint16_t MAX_ACCOUNT_LIST_SIZE = 500;
constexpr uint16_t MIN_POLL_AGE_SECONDS = 60;
constexpr uint16_t MAX_METADATA_LENGTH = 300;
constexpr uint16_t MAX_COMMENT_LENGTH = 1000;

// @abi table polls i64
struct poll_t
{
    uuid poll_name;
    uint16_t num_options;
    uint16_t min_choices;
    uint16_t max_choices;
    vector<account_name> whitelist;
    vector<account_name> blacklist;
    timestamp open_time;
    timestamp close_time;

    uuid primary_key() const { return poll_name; }

    bool has_opened() const { return open_time == 0 || open_time <= now(); }

    bool is_closed() const { return close_time > 0 && close_time <= now(); }

    EOSLIB_SERIALIZE(poll_t, (poll_name)(num_options)(min_choices)(max_choices)(whitelist)(blacklist)(open_time)(close_time))
};

typedef eosio::multi_index<N(polls), poll_t> polls_index;

template <typename T>
bool has_duplicates(const vector<T> &items)
{
    vector<T> sorted(items);
    auto end = sorted.end();
    std::sort(sorted.begin(), end);
    return std::adjacent_find(sorted.begin(), end) != end;
}

void validate_account_list(const vector<account_name> &account_list)
{
    eosio_assert(!has_duplicates(account_list), "account lists must not contain duplicates");
    eosio_assert(account_list.size() <= MAX_ACCOUNT_LIST_SIZE, "account lists must have <= 500 entries");
}

void validate_metadata(const string &metadata)
{
    eosio_assert(metadata.length() <= MAX_METADATA_LENGTH, "metadata must be 300 characters or less");
}

// @abi action
void eosstrawpoll::create(
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
    const string &metadata)
{
    require_auth(poll_creator);

    validate_metadata(metadata);

    {
        const string poll_name_str = eosio::name{poll_name}.to_string();
        const auto poll_name_length = poll_name_str.length();
        eosio_assert(poll_name_length >= MIN_ID_LENGTH, "poll_name must be at least 1 character long");
        eosio_assert(poll_name_length <= MAX_ID_LENGTH, "poll_name must be 12 characters or less");
    }

    const uint16_t num_options = options.size();
    eosio_assert(title.length() <= MAX_TITLE_LENGTH, "title must be 100 characters or less");
    eosio_assert(description.length() <= MAX_DESCRIPTION_LENGTH, "descriptions must be 2000 characters or less");
    eosio_assert(num_options >= 2, "must have at least 2 options");
    eosio_assert(num_options <= MAX_OPTIONS_SIZE, "must have 100 options or less");

    for (auto &option : options)
    {
        eosio_assert(!option.empty(), "empty options are not allowed");
        eosio_assert(option.length() <= MAX_OPTION_LENGTH, "options must be less than 280 characters long");
    }

    // check that there are no duplicate options
    eosio_assert(!has_duplicates(options), "duplicate options are not allowed");
    validate_account_list(whitelist);
    validate_account_list(blacklist);

    eosio_assert(close_time > open_time, "close time must be after open time");
    eosio_assert(close_time > now(), "close time must not be in the past");
    eosio_assert(close_time - std::max(open_time, now()) >= MIN_POLL_AGE_SECONDS, "polls must be open for at least 60 seconds");
    eosio_assert(min_choices >= 1, "min_choices must be >= 1");
    eosio_assert(max_choices <= num_options, "max_choices must be <= the number of options");
    eosio_assert(max_choices >= min_choices, "max_choices must be >= min_choices");

    // create the poll
    polls_index polls(_self, poll_creator);

    // check if poll exists
    auto existing_poll = polls.find(poll_name);
    eosio_assert(existing_poll == polls.end(), "poll already exists with this id");

    auto poll = polls.emplace(poll_creator, [&](auto &p) {
        p.poll_name = poll_name;
        p.num_options = num_options;
        p.min_choices = min_choices;
        p.max_choices = max_choices;
        p.whitelist = whitelist;
        p.blacklist = blacklist;
        p.open_time = open_time;
        p.close_time = close_time;
    });

    eosio::print(
        "success: action=create",
        ", poll_creator=", eosio::name{poll_creator},
        ", poll_name=", eosio::name{poll_name});
}

// @abi action
void eosstrawpoll::close(
    const account_name poll_creator,
    const uuid poll_name,
    const string &metadata)
{
    require_auth(poll_creator);

    validate_metadata(metadata);

    // check if poll exists
    polls_index polls(_self, poll_creator);
    auto poll = polls.find(poll_name);
    eosio_assert(poll != polls.end(), "poll doesn't exist");

    polls.erase(poll);

    eosio::print(
        "success: action=close",
        ", poll_creator=", eosio::name{poll_creator},
        ", poll_name=", eosio::name{poll_name});
}

// @abi action
void eosstrawpoll::vote(
    const account_name poll_creator,
    const uuid poll_name,
    const account_name voter,
    const vector<uint16_t> &choices,
    const string &metadata)
{
    require_auth(voter);

    validate_metadata(metadata);

    // check if poll exists
    polls_index polls(_self, poll_creator);
    auto poll = polls.find(poll_name);
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
        eosio_assert(choice >= 0 && choice <= max_choice, "received invalid choice");
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

    eosio::print(
        "success: action=vote",
        ", poll_creator=", eosio::name{poll_creator},
        ", poll_name=", eosio::name{poll_name},
        ", voter=", eosio::name{voter});
}

// // @abi action
void eosstrawpoll::comment(
    const account_name poll_creator,
    const uuid poll_name,
    const account_name commenter,
    const string &content,
    const string &metadata)
{
    require_auth(commenter);

    validate_metadata(metadata);
    eosio_assert(content.length() <= MAX_COMMENT_LENGTH, "comments must be <= 1000 characters");

    // check if poll exists
    polls_index polls(_self, poll_creator);
    auto poll = polls.find(poll_name);
    eosio_assert(poll != polls.end(), "poll doesn't exist");

    eosio::print(
        "success: action=comment",
        ", poll_creator=", eosio::name{poll_creator},
        ", poll_name=", eosio::name{poll_name},
        ", commenter=", eosio::name{commenter});
}

// @abi action
void eosstrawpoll::react(
    const account_name poll_creator,
    const uuid poll_name,
    const account_name reacter,
    const reaction_name reaction,
    const string &metadata)
{
    require_auth(reacter);
    validate_metadata(metadata);

    // check if poll exists
    polls_index polls(_self, poll_creator);
    auto poll = polls.find(poll_name);
    eosio_assert(poll != polls.end(), "poll doesn't exist");
    eosio::print(
        "success: action=react",
        ", poll_creator=", eosio::name{poll_creator},
        ", poll_name=", eosio::name{poll_name},
        ", reacter=", eosio::name{reacter},
        ", reaction=", eosio::name{reaction});
}

// @abi action
void eosstrawpoll::settings(
    const account_name account,
    const vector<account_name> default_whitelist,
    const vector<account_name> default_blacklist,
    const string &metadata)
{
    require_auth(account);
    validate_metadata(metadata);
    validate_account_list(default_whitelist);
    validate_account_list(default_blacklist);
    eosio::print(
        "success: action=settings",
        ", account=", eosio::name{account});
}

EOSIO_ABI(eosstrawpoll, (create)(close)(vote)(comment)(react)(settings))
