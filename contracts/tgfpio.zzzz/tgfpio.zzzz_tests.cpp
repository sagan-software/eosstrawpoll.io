#include <Runtime/Runtime.h>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/test/unit_test.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include <eosio/testing/tester.hpp>
#include <fc/io/json.hpp>
#include <fc/variant_object.hpp>
#include <tgfpio.zzzz/tgfpio.zzzz.abi.hpp>
#include <tgfpio.zzzz/tgfpio.zzzz.wast.hpp>

using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

using mvo = fc::mutable_variant_object;

typedef uint64_t id_type;

typedef string uri_type;

class tgfpio_zzzz_tester : public tester
{
  public:
    tgfpio_zzzz_tester()
    {
        create_accounts({N(alice), N(bob), N(carol), N(tgfpio.zzzz)});
        set_code(N(tgfpio.zzzz), tgfpio_zzzz_wast);
        set_abi(N(tgfpio.zzzz), tgfpio_zzzz_abi);

        const auto &accnt = control->db().get<account_object, by_name>(N(tgfpio.zzzz));
        abi_def abi;
        BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
        abi_ser.set_abi(abi);
    }
    abi_serializer abi_ser;
};

BOOST_AUTO_TEST_SUITE(tgfpio_zzzz_tests)

BOOST_FIXTURE_TEST_CASE(can_say_hello, tgfpio_zzzz_tester)
try
{
    auto trace = push_action(N(tgfpio.zzzz), N(hi), N(bob), mvo()("user", "alice"));
    auto msg = trace->action_traces.front().console;
    BOOST_REQUIRE_EQUAL(msg, "Hello, alice");
}
FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()
