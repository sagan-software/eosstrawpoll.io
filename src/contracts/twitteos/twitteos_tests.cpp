#include <boost/algorithm/string/predicate.hpp>
#include <boost/test/unit_test.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include <eosio/testing/tester.hpp>
#include <regex>

#include <twitteos/twitteos.abi.hpp>
#include <twitteos/twitteos.wast.hpp>

#include <Runtime/Runtime.h>

#include <fc/io/json.hpp>
#include <fc/variant_object.hpp>

using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

using mvo = fc::mutable_variant_object;

typedef uint64_t uuid;
typedef uint32_t timestamp;

struct post
{
    uuid id;
    string text;
    timestamp created;

    uuid parent_id;
    account_name parent_author;
};
FC_REFLECT(post, (id)(text)(created)(parent_id)(parent_author));

struct profile_t
{
    string username = "";
    string display_name = "";
    string biography = "";
    string location = "";
    string profile_photo_hash = "";
    string header_photo_hash = "";
    uint64_t num_posts = 0;
    uint64_t num_following = 0;
    uint64_t num_followers = 0;
    uint64_t num_liked = 0;
    timestamp created;
    uuid last_post_id;
};
FC_REFLECT(profile_t, (username)(display_name)(biography)(location)(profile_photo_hash)(header_photo_hash)(num_posts)(num_following)(num_followers)(num_liked)(created)(last_post_id));

class twitteos_tester : public tester
{
  public:
    const action_result too_short_msg = wasm_assert_msg("post text is too short, must be greater than or equal to 1 character(s) long");
    const action_result too_long_msg = wasm_assert_msg("post text is too long, must be less than or equal to 280 character(s) long");

    action_result push_action(
        const account_name &signer,
        const action_name &name,
        const variant_object &data)
    {
        string action_type_name = abi_ser.get_action_type(name);

        action act;
        act.account = N(twitteos);
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

    auto create_post(
        const account_name author,
        const string &text)
    {
        return push_action(
            author,
            N(create),
            mvo()("author", author)("text", text));
    }

    auto reply_to_post(
        const account_name author,
        const string &text,
        const uuid parent_id,
        const account_name parent_author)
    {
        return push_action(
            author,
            N(reply),
            mvo()("author", author)("text", text)("parent_id", parent_id)("parent_author", parent_author));
    }

    auto update_post(
        const account_name author,
        const string &text,
        const uuid post_id)
    {
        return push_action(
            author,
            N(update),
            mvo()("author", author)("text", text)("post_id", post_id));
    }

    auto destroy_post(
        const account_name author,
        const uuid post_id)
    {
        return push_action(
            author,
            N(destroy),
            mvo()("author", author)("post_id", post_id));
    }

    action_result get_action_result(transaction_trace_ptr trace)
    {
        // TODO
        return success();
    }

    uuid extract_uuid(string console)
    {
        const regex re("id=(\\d+)");
        smatch match;

        regex_search(console, match, re);

        BOOST_REQUIRE_EQUAL(match.size(), 2);

        const string id_str = match.str(1);
        const uuid id = std::stoull(id_str);
        return id;
    }

    post get_post(const account_name author, const uuid id)
    {
        post current;
        get_table_entry(current, N(twitteos), author, N(posts), id);
        return current;
    }

    profile_t get_profile(const account_name author)
    {
        profile_row_t row;
        get_table_entry(row, N(twitteos), author, N(profile), N(profile));
        return row.value;
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

    twitteos_tester()
    {
        create_accounts({N(alice), N(bob), N(carol), N(twitteos)});
        set_code(N(twitteos), twitteos_wast);
        set_abi(N(twitteos), twitteos_abi);
        const auto &accnt = control->db().get<account_object, by_name>(N(twitteos));
        abi_def abi;
        BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
        abi_ser.set_abi(abi);
        produce_block();
    }

    abi_serializer abi_ser;
};

BOOST_AUTO_TEST_SUITE(twitteos_tests)

BOOST_FIXTURE_TEST_CASE(can_create_post, twitteos_tester)
try
{
    const action_result result = create_post(N(alice), "Hello world");
    require_success(result);
    const uuid id = extract_uuid(result);
    const post current = get_post(N(alice), id);
    BOOST_REQUIRE_EQUAL(current.id, id);
    BOOST_REQUIRE_EQUAL(current.text, "Hello world");
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(can_update_post, twitteos_tester)
try
{
    const action_result create_result = create_post(N(alice), "Hello world");
    require_success(create_result);
    const uuid id = extract_uuid(create_result);

    const action_result update_result = update_post(N(alice), "Hey Earth", id);
    require_success(update_result);

    const post current = get_post(N(alice), id);
    BOOST_REQUIRE_EQUAL(current.id, id);
    BOOST_REQUIRE_EQUAL(current.text, "Hey Earth");
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(cannot_update_invalid_post, twitteos_tester)
try
{
    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("post doesn't exist"),
        update_post(N(alice), "Hey Earth", 999));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(can_delete_post, twitteos_tester)
try
{
    const action_result create_result = create_post(N(alice), "Hello world1");
    require_success(create_result);
    const uuid id = extract_uuid(create_result);

    require_success(destroy_post(N(alice), id));

    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("post doesn't exist"),
        destroy_post(N(alice), id));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(cannot_delete_invalid_post, twitteos_tester)
try
{
    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("post doesn't exist"),
        update_post(N(alice), "Hey Earth", 999));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(can_reply_to_posts, twitteos_tester)
try
{
    const action_result result = create_post(N(alice), "Hello world");
    require_success(result);
    const uuid id = extract_uuid(result);
    const post current = get_post(N(alice), id);
    BOOST_REQUIRE_EQUAL(current.id, id);
    BOOST_REQUIRE_EQUAL(current.text, "Hello world");
    require_success(reply_to_post(N(bob), "Hey alice", current.id, N(alice)));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(cannot_reply_to_invalid_posts, twitteos_tester)
try
{
    const action_result expected = wasm_assert_msg("parent post doesn't exist");
    BOOST_REQUIRE_EQUAL(expected, reply_to_post(N(bob), "Hey", 0, N(charlie)));
    BOOST_REQUIRE_EQUAL(expected, reply_to_post(N(bob), "Hey", 9999, N(alice)));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(create_with_short_text, twitteos_tester)
try
{
    BOOST_REQUIRE_EQUAL(too_short_msg, create_post(N(alice), ""));
    require_success(create_post(N(alice), "A"));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(reply_with_short_text, twitteos_tester)
try
{
    const action_result parent_result = create_post(N(alice), "reply_with_short_text");
    require_success(parent_result);

    const uuid parent_id = extract_uuid(parent_result);
    BOOST_REQUIRE_EQUAL(too_short_msg, reply_to_post(N(bob), "", parent_id, N(alice)));

    require_success(reply_to_post(N(bob), "A", parent_id, N(alice)));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(profile_num_posts, twitteos_tester)
try
{
    profile_t profile = get_profile(N(alice));
    const auto initial_num_posts = profile.num_posts;

    const action_result parent_result = create_post(N(alice), "reply_with_short_text");
    require_success(parent_result);
    BOOST_REQUIRE_EQUAL(get_profile(N(alice)).num_posts, initial_num_posts + 1);

    // const uuid parent_id = extract_uuid(parent_result);
    // BOOST_REQUIRE_EQUAL(too_short_msg, reply_to_post(N(bob), "", parent_id, N(alice)));
}
FC_LOG_AND_RETHROW()

// BOOST_FIXTURE_TEST_CASE(create_with_long_text, twitteos_tester)
// try
// {
//     BOOST_REQUIRE_EQUAL(
//         too_long_msg,
//         create_post(N(alice), "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789011234567890123456789012345678901234567890"));
//     BOOST_REQUIRE_EQUAL(
//         "Created",
//         create_post(N(alice), "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789011234567890123456789012345678901234567890").substr(0, 7));
// }
// FC_LOG_AND_RETHROW()

/*
BOOST_FIXTURE_TEST_CASE(too_long_error, twitteos_tester)
try
{
    BOOST_REQUIRE_EQUAL(
        wasm_assert_msg("post is too long, must be less than or equal to 240 (got 241aa)"),
        create_post(N(alice), "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789011234567890123456789012345678901234567890"));

    BOOST_REQUIRE_EQUAL(
        success(),
        create_post(N(alice), "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901123456789012345678901234567890123456789"));
}
FC_LOG_AND_RETHROW()
*/

BOOST_AUTO_TEST_SUITE_END()
