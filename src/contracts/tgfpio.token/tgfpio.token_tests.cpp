#include <boost/algorithm/string/predicate.hpp>
#include <boost/test/unit_test.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include <eosio/testing/tester.hpp>

#include <tgfpio.token/tgfpio.token.abi.hpp>
#include <tgfpio.token/tgfpio.token.wast.hpp>

#include <Runtime/Runtime.h>

#include <fc/io/json.hpp>
#include <fc/variant_object.hpp>

using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

using mvo = fc::mutable_variant_object;

typedef uint64_t id_type;
typedef string uri_type;

class tgfpio_tester : public tester
{
  public:
    tgfpio_tester()
    {

        create_accounts({N(alice), N(bob), N(carol), N(tgfpio.token)});
        set_code(N(tgfpio.token), tgfpio_token_wast);
        set_abi(N(tgfpio.token), tgfpio_token_abi);
        const auto &accnt = control->db().get<account_object, by_name>(N(tgfpio.token));
        abi_def abi;
        BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
        abi_ser.set_abi(abi);
    }
    abi_serializer abi_ser;
};

BOOST_AUTO_TEST_SUITE(tgfpio_token_tests)

BOOST_FIXTURE_TEST_CASE(can_say_hello, tgfpio_tester)
try
{
    auto trace = push_action(N(tgfpio.token), N(hi), N(bob), mvo()("user", "alice"));
    auto msg = trace->action_traces.front().console;
    BOOST_REQUIRE_EQUAL(msg, "Hello, alice");
}
FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()
