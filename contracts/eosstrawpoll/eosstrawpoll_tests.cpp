#include <boost/algorithm/string/predicate.hpp>
#include <boost/test/unit_test.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include <eosio/testing/tester.hpp>
#include <random>
#include <regex>

#include <eosstrawpoll/eosstrawpoll.abi.hpp>
#include <eosstrawpoll/eosstrawpoll.wast.hpp>

#include <Runtime/Runtime.h>

#include <fc/io/json.hpp>
#include <fc/variant_object.hpp>

using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

using mvo = fc::mutable_variant_object;

typedef account_name uuid;
typedef uint32_t timestamp;

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
};
FC_REFLECT(poll_t, (poll_name)(num_options)(min_choices)(max_choices)(whitelist)(blacklist)(open_time)(close_time));

class eosstrawpoll_tester : public tester
{
  public:
    action_result push_action(
        const account_name &signer,
        const action_name &name,
        const variant_object &data)
    {
        string action_type_name = abi_ser.get_action_type(name);

        action act;
        act.account = N(eosstrawpoll);
        act.name = name;
        act.authorization = vector<permission_level>{{signer, config::active_name}};
        act.data = abi_ser.variant_to_binary(action_type_name, data);

        signed_transaction trx;
        trx.actions.emplace_back(std::move(act));
        set_transaction_headers(trx);
        trx.sign(get_private_key(signer, "active"), control->get_chain_id());
        transaction_trace_ptr trace;
        try
        {
            trace = push_transaction(trx);

            produce_block();
            BOOST_REQUIRE_EQUAL(true, chain_has_transaction(trx.id()));
            return trace->action_traces.front().console;
        }
        catch (const fc::exception &ex)
        {
            //edump((ex.to_detail_string()));
            return error(ex.top_message()); // top_message() is assumed by many tests; otherwise they fail
                                            //return error(ex.to_detail_string());
        }
    }

    auto create_poll(
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
        const string &app_label)
    {
        return push_action(
            poll_creator,
            N(create),
            mvo()("poll_creator", poll_creator)("poll_name",  poll_name)("title", title)("description", description)("options", options)("whitelist", whitelist)("blacklist", blacklist)("min_choices", min_choices)("max_choices", max_choices)("open_time", open_time)("close_time", close_time)("app_label", app_label));
    }

    auto close_poll(
        const account_name poll_creator,
        const uuid poll_nameme,
        const string &app_label)
    {
        return push_action(
            poll_creator,
            N(close),
            mvo()("poll_creator", poll_creator)("poll_name"  poll_name)("app_label", app_label));
    }

    auto cast_vote(
        const account_name poll_creator,
        const uuid poll_name,
        const account_name voter,
        const vector<uint16_t> &choices,
        const string &app_label)
    {
        return push_action(
            voter,
            N(vote),
            mvo()("poll_creator", poll_creator)("poll_name"  poll_name)("voter", voter)("choices", choices)("app_label", app_label));
    }

    uuid extract_uuid(string console)
    {
        const regex re("poll_name=([\\.12345abcdefghijklmnopqrstuvwxyz]+)");
        smatch match;

        regex_search(console, match, re);

        BOOST_REQUIRE_EQUAL(match.size(), 2);

        const string id_str = match.str(1);
        // const uuid id = std::stoull(id_str);
        // const uuid id = N(balls);
        return eosio::chain::string_to_name(id_str.c_str());
    }

    poll_t get_poll(const account_name poll_creator, const uuid poll_name)
    {
        poll_t p;
        get_table_entry(p, N(eosstrawpoll), poll_creator, N(polls), poll_name);
        return p;
    }

    bool starts_with(const string &haystack, const string &needle)
    {
        return needle.length() <= haystack.length() && equal(needle.begin(), needle.end(), haystack.begin());
    }

    void require_success(action_result result)
    {
        BOOST_REQUIRE_MESSAGE(
            "success" == result.substr(0, 7),
            "action did not succeed: " << result);
    }

    uuid require_create_poll(
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
        const string &app_label)
    {
        const action_result result = create_poll(
            poll_creator,
            poll_name,
            title,
            description,
            options,
            whitelist,
            blacklist,
            min_choices,
            max_choices,
            open_time,
            close_time,
            app_label);
        require_success(result);
        return extract_uuid(result);
    }

    timestamp now()
    {
        return control->pending_block_time().time_since_epoch().count() / 1000000;
    }

    eosstrawpoll_tester()
    {
        create_accounts({N(alice), N(bob), N(carol), N(eosstrawpoll)});
        set_code(N(eosstrawpoll), eosstrawpoll_wast);
        set_abi(N(eosstrawpoll), eosstrawpoll_abi);
        const auto &accnt = control->db().get<account_object, by_name>(N(eosstrawpoll));
        abi_def abi;
        BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
        abi_ser.set_abi(abi);
        produce_block();
    }

    abi_serializer abi_ser;
};

uuid rand_uuid()
{
    auto randchar = []() -> char {
        const char charset[] =
            ".12345abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    const size_t length = 12;
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return eosio::chain::string_to_name(str.c_str());
}

BOOST_AUTO_TEST_SUITE(eosstrawpoll_tests)

BOOST_FIXTURE_TEST_CASE(can_create_polls, eosstrawpoll_tester)
try
{
    const account_name poll_creator = N(alice);
    const string title = "Test poll";
    const vector<string> options{"Option A", "Option B", "Option C"};
    const vector<account_name> blacklist{N(name1), N(name2)};
    const vector<account_name> whitelist{N(name3), N(name4)};
    const uint16_t min_choices = 1;
    const uint16_t max_choices = 3;
    const timestamp open_time = 0;
    const timestamp close_time = 0;

    const uuid poll_name = rand_uuid();
    require_create_poll(
        poll_creator,
        poll_name,
        title,
        "",
        options,
        whitelist,
        blacklist,
        min_choices,
        max_choices,
        open_time,
        close_time,
        "");

    const poll_t p = get_poll(poll_creator, poll_name);
    BOOST_REQUIRE_EQUAL(p.poll_name, poll_name);
    BOOST_REQUIRE_MESSAGE(p.blacklist == blacklist, "blacklist is different");
    BOOST_REQUIRE_MESSAGE(p.whitelist == whitelist, "whitelist is different");
    BOOST_REQUIRE_EQUAL(p.min_choices, min_choices);
    BOOST_REQUIRE_EQUAL(p.max_choices, max_choices);
    BOOST_REQUIRE_EQUAL(p.open_time, now());
    BOOST_REQUIRE_EQUAL(p.close_time, close_time);
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(can_close_polls, eosstrawpoll_tester)
try
{
    const uuid poll_name = rand_uuid();
    require_create_poll(
        N(alice),
        poll_name,
        "Test poll",
        "",
        vector<string>{"Option A", "Option B", "Option C"},
        vector<account_name>{N(name1), N(name2)},
        vector<account_name>{N(name3), N(name4)},
        0,
        0,
        0,
        0,
        "");

    require_success(close_poll(N(alice), poll_name, ""));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(can_cast_votes, eosstrawpoll_tester)
try
{
    const uuid poll_name = rand_uuid();
    require_create_poll(
        N(alice),
        poll_name,
        "Test poll",
        "",
        vector<string>{"Option A", "Option B", "Option C"},
        vector<account_name>{},
        vector<account_name>{},
        0,
        0,
        0,
        0,
        "");

    require_success(cast_vote(N(alice), poll_name, N(bob), vector<uint16_t>{1}, ""));
    require_success(cast_vote(N(alice), poll_name, N(carol), vector<uint16_t>{2}, ""));
    require_success(cast_vote(N(alice), poll_name, N(bob), vector<uint16_t>{0}, ""));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(choices_are_clamped, eosstrawpoll_tester)
try
{
    {
        const uuid poll_name = rand_uuid();
        require_create_poll(
            N(alice),
            poll_name,
            "Test poll",
            "",
            vector<string>{"Option A", "Option B", "Option C"},
            vector<account_name>{},
            vector<account_name>{},
            0,
            0,
            0,
            0,
            "");
        const poll_t p = get_poll(N(alice), poll_name);
        BOOST_REQUIRE_EQUAL(p.min_choices, 1);
        BOOST_REQUIRE_EQUAL(p.max_choices, 1);
    };
    {
        const uuid poll_name = rand_uuid();
        require_create_poll(
            N(alice),
            poll_name,
            "Test poll",
            "",
            vector<string>{"Option A", "Option B", "Option C"},
            vector<account_name>{},
            vector<account_name>{},
            5,
            4,
            0,
            0,
            "");
        const poll_t p = get_poll(N(alice), poll_name);
        BOOST_REQUIRE_EQUAL(p.min_choices, 3);
        BOOST_REQUIRE_EQUAL(p.max_choices, 3);
    };
    {
        const uuid poll_name = rand_uuid();
        require_create_poll(
            N(alice),
            poll_name,
            "Test poll",
            "",
            vector<string>{"Option A", "Option B", "Option C"},
            vector<account_name>{},
            vector<account_name>{},
            5,
            4,
            0,
            0,
            "");
        const poll_t p = get_poll(N(alice), poll_name);
        BOOST_REQUIRE_EQUAL(p.min_choices, 3);
        BOOST_REQUIRE_EQUAL(p.max_choices, 3);
    };
    {
        const uuid poll_name = rand_uuid();
        require_create_poll(
            N(alice),
            poll_name,
            "Test poll",
            "",
            vector<string>{"Option A", "Option B", "Option C"},
            vector<account_name>{},
            vector<account_name>{},
            2,
            0,
            0,
            0,
            "");
        const poll_t p = get_poll(N(alice), poll_name);
        BOOST_REQUIRE_EQUAL(p.min_choices, 2);
        BOOST_REQUIRE_EQUAL(p.max_choices, 2);
    };
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(cannot_create_polls_with_too_few_options, eosstrawpoll_tester)
try
{
    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("must have at least 2 options"),
        create_poll(
            N(alice),
            rand_uuid(),
            "Test poll",
            "",
            vector<string>{},
            vector<account_name>{},
            vector<account_name>{},
            0,
            0,
            0,
            0,
            ""));

    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("must have at least 2 options"),
        create_poll(
            N(alice),
            rand_uuid(),
            "Test poll",
            "",
            vector<string>{"Option A"},
            vector<account_name>{},
            vector<account_name>{},
            0,
            0,
            0,
            0,
            ""));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(cannot_create_polls_with_empty_options, eosstrawpoll_tester)
try
{
    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("empty options are not allowed"),
        create_poll(
            N(alice),
            rand_uuid(),
            "Test poll",
            "",
            vector<string>{"A", "B", ""},
            vector<account_name>{},
            vector<account_name>{},
            0,
            0,
            0,
            0,
            ""));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(cannot_create_polls_with_duplicate_options, eosstrawpoll_tester)
try
{
    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("duplicate options are not allowed"),
        create_poll(
            N(alice),
            rand_uuid(),
            "Test poll",
            "",
            vector<string>{"A", "B", "B"},
            vector<account_name>{},
            vector<account_name>{},
            0,
            0,
            0,
            0,
            ""));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(cannot_create_polls_with_invalid_open_time, eosstrawpoll_tester)
try
{
    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("close time must be after open time"),
        create_poll(
            N(alice),
            rand_uuid(),
            "Test poll",
            "",
            vector<string>{"Option A", "Option B"},
            vector<account_name>{},
            vector<account_name>{},
            0,
            0,
            2,
            1,
            ""));

    require_success(
        create_poll(
            N(alice),
            rand_uuid(),
            "Test poll",
            "",
            vector<string>{"Option A", "Option B"},
            vector<account_name>{},
            vector<account_name>{},
            0,
            0,
            2,
            0,
            ""));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(cannot_create_polls_already_closed, eosstrawpoll_tester)
try
{
    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("close time must not be in the past"),
        create_poll(
            N(alice),
            rand_uuid(),
            "Test poll",
            "",
            vector<string>{"Option A", "Option B"},
            vector<account_name>{},
            vector<account_name>{},
            0,
            0,
            0,
            1,
            ""));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(cannot_vote_on_nonexistant_polls, eosstrawpoll_tester)
try
{
    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("poll doesn't exist"),
        cast_vote(
            N(janice),
            N(notreal),
            N(bob),
            vector<uint16_t>{},
            ""));

    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("poll doesn't exist"),
        cast_vote(
            N(alice),
            N(balls),
            N(bob),
            vector<uint16_t>{},
            ""));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(cannot_vote_on_unopened_polls, eosstrawpoll_tester)
try
{
    const uuid poll_name = rand_uuid();
    require_create_poll(
        N(alice),
        poll_name,
        "Test poll",
        "",
        vector<string>{"Option A", "Option B"},
        vector<account_name>{},
        vector<account_name>{},
        0,
        0,
        now() + 10,
        0,
        "");

    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("poll has not opened yet"),
        cast_vote(
            N(alice),
            poll_name,
            N(bob),
            vector<uint16_t>{0},
            ""));

    produce_block(fc::seconds(9));

    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("poll has not opened yet"),
        cast_vote(
            N(alice),
            poll_name,
            N(bob),
            vector<uint16_t>{0},
            ""));

    produce_block(fc::seconds(1));

    require_success(
        cast_vote(
            N(alice),
            poll_name,
            N(bob),
            vector<uint16_t>{0},
            ""));

    const uuid poll_name2 = rand_uuid();
    require_create_poll(
        N(alice),
        poll_name2,
        "Test poll",
        "",
        vector<string>{"Option A", "Option B"},
        vector<account_name>{},
        vector<account_name>{},
        0,
        0,
        now() - 10,
        0,
        "");

    require_success(
        cast_vote(
            N(alice),
            poll_name2,
            N(bob),
            vector<uint16_t>{0},
            ""));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(cannot_vote_on_closed_polls, eosstrawpoll_tester)
try
{
    const uuid poll_name = require_create_poll(
        N(alice),
        rand_uuid(),
        "Test poll",
        "",
        vector<string>{"Option A", "Option B"},
        vector<account_name>{},
        vector<account_name>{},
        0,
        0,
        0,
        0,
        "");

    require_success(
        cast_vote(
            N(alice),
            poll_name,
            N(bob),
            vector<uint16_t>{0},
            ""));

    const poll_t p = get_poll(N(alice), poll_name);
    require_success(close_poll(N(alice), poll_name, ""));

    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("poll doesn't exist"),
        cast_vote(
            N(alice),
            poll_name,
            N(bob),
            vector<uint16_t>{0},
            ""));

    const uuid poll_name2 = require_create_poll(
        N(alice),
        rand_uuid(),
        "Test poll",
        "",
        vector<string>{"Option A", "Option B"},
        vector<account_name>{},
        vector<account_name>{},
        0,
        0,
        0,
        now() + 60,
        "");

    require_success(
        cast_vote(
            N(alice),
            poll_name2,
            N(bob),
            vector<uint16_t>{0},
            ""));

    produce_block(fc::seconds(30));

    require_success(
        cast_vote(
            N(alice),
            poll_name2,
            N(bob),
            vector<uint16_t>{0},
            ""));

    produce_block(fc::seconds(30));

    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("poll is closed"),
        cast_vote(
            N(alice),
            poll_name2,
            N(bob),
            vector<uint16_t>{0},
            ""));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(cannot_vote_with_too_few_choices, eosstrawpoll_tester)
try
{
    const uuid poll_name = require_create_poll(
        N(alice),
        rand_uuid(),
        "Test poll",
        "",
        vector<string>{"Option A", "Option B"},
        vector<account_name>{},
        vector<account_name>{},
        2,
        0,
        0,
        0,
        "");

    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("too few choices"),
        cast_vote(
            N(alice),
            poll_name,
            N(bob),
            vector<uint16_t>{},
            ""));

    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("too few choices"),
        cast_vote(
            N(alice),
            poll_name,
            N(bob),
            vector<uint16_t>{0},
            ""));

    require_success(
        cast_vote(
            N(alice),
            poll_name,
            N(bob),
            vector<uint16_t>{0, 1},
            ""));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(cannot_vote_with_too_many_choices, eosstrawpoll_tester)
try
{
    const uuid id = require_create_poll(
        N(alice),
        rand_uuid(),
        "Test poll",
        "",
        vector<string>{"Option A", "Option B"},
        vector<account_name>{},
        vector<account_name>{},
        0,
        2,
        0,
        0,
        "");

    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("too many choices"),
        cast_vote(
            N(alice),
            poll_name,
            N(bob),
            vector<uint16_t>{0, 1, 2, 3},
            ""));

    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("too many choices"),
        cast_vote(
            N(alice),
            poll_name,
            N(bob),
            vector<uint16_t>{0, 1, 2},
            ""));

    require_success(
        cast_vote(
            N(alice),
            poll_name,
            N(bob),
            vector<uint16_t>{0, 1},
            ""));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(cannot_vote_with_duplicate_choices, eosstrawpoll_tester)
try
{
    const uuid poll_name = require_create_poll(
        N(alice),
        rand_uuid(),
        "Test poll",
        "",
        vector<string>{"Option A", "Option B", "Option C"},
        vector<account_name>{},
        vector<account_name>{},
        0,
        3,
        0,
        0,
        "");

    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("duplicate choices are not allowed"),
        cast_vote(
            N(alice),
            poll_name,
            N(bob),
            vector<uint16_t>{1, 1, 0},
            ""));

    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("duplicate choices are not allowed"),
        cast_vote(
            N(alice),
            poll_name,
            N(bob),
            vector<uint16_t>{1, 0, 1},
            ""));

    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("duplicate choices are not allowed"),
        cast_vote(
            N(alice),
            poll_name,
            N(bob),
            vector<uint16_t>{0, 1, 0},
            ""));

    require_success(
        cast_vote(
            N(alice),
            poll_name,
            N(bob),
            vector<uint16_t>{0, 1, 2},
            ""));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(cannot_vote_with_invalid_choices, eosstrawpoll_tester)
try
{
    const uuid poll_name = require_create_poll(
        N(alice),
        rand_uuid(),
        "Test poll",
        "",
        vector<string>{"Option A", "Option B"},
        vector<account_name>{},
        vector<account_name>{},
        2,
        0,
        0,
        0,
        "");

    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("received invalid choice"),
        cast_vote(
            N(alice),
            poll_name,
            N(bob),
            vector<uint16_t>{2, 3},
            ""));

    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("received invalid choice"),
        cast_vote(
            N(alice),
            poll_name,
            N(bob),
            vector<uint16_t>{0, 3},
            ""));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(cannot_vote_if_not_whitelisted, eosstrawpoll_tester)
try
{
    const uuid poll_name = require_create_poll(
        N(alice),
        rand_uuid(),
        "Test poll",
        "",
        vector<string>{"Option A", "Option B"},
        vector<account_name>{N(carol)},
        vector<account_name>{},
        0,
        0,
        0,
        0,
        "");

    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("voter is not on whitelist"),
        cast_vote(
            N(alice),
            poll_name,
            N(bob),
            vector<uint16_t>{0},
            ""));

    require_success(
        cast_vote(
            N(alice),
            poll_name,
            N(carol),
            vector<uint16_t>{0},
            ""));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(cannot_vote_if_blacklisted, eosstrawpoll_tester)
try
{
    const uuid poll_name = require_create_poll(
        N(alice),
        rand_uuid(),
        "Test poll",
        "",
        vector<string>{"Option A", "Option B"},
        vector<account_name>{},
        vector<account_name>{N(bob), N(carol)},
        0,
        0,
        0,
        0,
        "");

    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("voter is blacklisted"),
        cast_vote(
            N(alice),
            poll_name,
            N(bob),
            vector<uint16_t>{0},
            ""));

    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("voter is blacklisted"),
        cast_vote(
            N(alice),
            poll_name,
            N(carol),
            vector<uint16_t>{0},
            ""));

    require_success(
        cast_vote(
            N(alice),
            poll_name,
            N(alice),
            vector<uint16_t>{0},
            ""));
}
FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()
