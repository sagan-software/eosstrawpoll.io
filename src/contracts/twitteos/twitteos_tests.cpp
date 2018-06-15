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

class twitteos_tester : public tester
{
  public:
    auto push_action(
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
        return push_transaction(trx);
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

    auto trace = create_post(N(alice), "Hello world");
    std::string msg = trace->action_traces.front().console;
    std::regex re("Created post with ID (\\d+)");
    std::smatch match;

    std::regex_search(msg, match, re);

    BOOST_REQUIRE_EQUAL(match.size(), 2);

    std::string id_str = match.str(1);
    uuid id = std::stoull(id_str);
    BOOST_REQUIRE_EQUAL(id, 0);

    post current;
    get_table_entry(current, N(twitteos), N(alice), N(posts), id);
    BOOST_REQUIRE_EQUAL(current.text, "Hello world");
}
FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()
