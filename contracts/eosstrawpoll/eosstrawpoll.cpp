#include "eosstrawpoll.hpp"

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

void validate_account_list(const vector<account_name> &account_list)
{
    eosio_assert(!has_duplicates(account_list), "account lists must not contain duplicates");
    eosio_assert(account_list.size() <= MAX_ACCOUNT_LIST_SIZE, "account lists must have <= 500 entries");
}

void validate_app_label(const string &app_label)
{
    eosio_assert(app_label.length() <= MAX_APP_LABEL_LENGTH, "app label must be 50 characters or less");
}

// @abi action
void eosstrawpoll::create(
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
    const string &app_label)
{
    require_auth(poll_creator);

    validate_app_label(app_label);

    {
        const string poll_id_str = eosio::name{poll_id}.to_string();
        const auto poll_id_length = poll_id_str.length();
        eosio_assert(poll_id_length >= MIN_ID_LENGTH, "poll_id must be at least 1 character long");
        eosio_assert(poll_id_length <= MAX_ID_LENGTH, "poll_id must be 12 characters or less");
    }

    eosio_assert(title.length() <= MAX_TITLE_LENGTH, "title must be 100 characters or less");
    eosio_assert(description.length() <= MAX_DESCRIPTION_LENGTH, "descriptions must be 2000 characters or less");
    eosio_assert(options.size() >= 2, "must have at least 2 options");
    eosio_assert(options.size() <= MAX_OPTIONS_SIZE, "must have 100 options or less");

    for (auto &option : options)
    {
        eosio_assert(!option.empty(), "empty options are not allowed");
        eosio_assert(option.length() <= MAX_OPTION_LENGTH, "options must be less than 280 characters long");
    }

    // check that there are no duplicate options
    eosio_assert(!has_duplicates(options), "duplicate options are not allowed");
    validate_account_list(whitelist);
    validate_account_list(blacklist);

    const auto actual_open_time = std::max(open_time, now());

    // check that close time is not before open time
    if (close_time > 0)
    {
        eosio_assert(close_time > open_time, "close time must be after open time");
        eosio_assert(close_time > now(), "close time must not be in the past");
        eosio_assert(close_time - actual_open_time >= MIN_POLL_AGE_SECONDS, "polls must be open for at least 60 seconds");
    }

    // create the poll
    polls_index polls(_self, poll_creator);

    // check if poll exists
    auto existing_poll = polls.find(poll_id);
    eosio_assert(existing_poll == polls.end(), "poll already exists with this id");

    const uint16_t num_options = options.size();
    auto poll = polls.emplace(poll_creator, [&](auto &p) {
        p.id = poll_id;
        p.num_options = options.size();
        p.min_choices = clamp<uint16_t>(min_choices, 1, num_options);
        p.max_choices = clamp<uint16_t>(max_choices, p.min_choices, num_options);
        p.whitelist = whitelist;
        p.blacklist = blacklist;
        p.open_time = actual_open_time;
        p.close_time = close_time;
    });

    eosio::print(
        "success: action=create",
        ", poll_creator=", eosio::name{poll_creator},
        ", poll_id=", eosio::name{poll_id});
}

// @abi action
void eosstrawpoll::close(
    const account_name poll_creator,
    const uuid poll_id,
    const string &app_label)
{
    require_auth(poll_creator);

    validate_app_label(app_label);

    // check if poll exists
    polls_index polls(_self, poll_creator);
    auto poll = polls.find(poll_id);
    eosio_assert(poll != polls.end(), "poll doesn't exist");

    polls.erase(poll);

    eosio::print(
        "success: action=close",
        ", poll_creator=", eosio::name{poll_creator},
        ", poll_id=", eosio::name{poll_id});
}

// @abi action
void eosstrawpoll::vote(
    const account_name poll_creator,
    const uuid poll_id,
    const account_name voter,
    const vector<uint16_t> &choices,
    const string &app_label)
{
    require_auth(voter);

    validate_app_label(app_label);

    // check if poll exists
    polls_index polls(_self, poll_creator);
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
        ", poll_id=", eosio::name{poll_id},
        ", voter=", eosio::name{voter});
}

// // @abi action
void eosstrawpoll::comment(
    const account_name poll_creator,
    const uuid poll_id,
    const account_name commenter,
    const string &content,
    const string &app_label)
{
    require_auth(commenter);

    validate_app_label(app_label);
    eosio_assert(content.length() <= MAX_COMMENT_LENGTH, "comments must be <= 1000 characters");

    // check if poll exists
    polls_index polls(_self, poll_creator);
    auto poll = polls.find(poll_id);
    eosio_assert(poll != polls.end(), "poll doesn't exist");

    eosio::print(
        "success: action=comment",
        ", poll_creator=", eosio::name{poll_creator},
        ", poll_id=", eosio::name{poll_id},
        ", commenter=", eosio::name{commenter});
}

// @abi action
void eosstrawpoll::react(
    const account_name poll_creator,
    const uuid poll_id,
    const account_name reacter,
    const reaction_name reaction,
    const string &app_label)
{
    require_auth(reacter);
    validate_app_label(app_label);

    // check if poll exists
    polls_index polls(_self, poll_creator);
    auto poll = polls.find(poll_id);
    eosio_assert(poll != polls.end(), "poll doesn't exist");
    eosio_assert(reaction == N(like), "reaction must equal 'like' for now. more reactions may be added later");

    eosio::print(
        "success: action=react",
        ", poll_creator=", eosio::name{poll_creator},
        ", poll_id=", eosio::name{poll_id},
        ", reacter=", eosio::name{reacter},
        ", reaction=", eosio::name{reaction});
}

// @abi action
void eosstrawpoll::settings(
    const account_name account,
    const string &json_metadata,
    const vector<account_name> default_whitelist,
    const vector<account_name> default_blacklist,
    const string &app_label)
{
    require_auth(account);
    validate_app_label(app_label);
    eosio_assert(json_metadata.length() <= MAX_JSON_LENGTH, "JSON metadata must be 2500 characters or less");
    validate_account_list(default_whitelist);
    validate_account_list(default_blacklist);
    eosio::print(
        "success: action=settings",
        ", account=", eosio::name{account});
}

EOSIO_ABI(eosstrawpoll, (create)(close)(vote)(comment)(react)(settings))
