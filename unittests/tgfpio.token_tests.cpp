#include <boost/test/unit_test.hpp>
#include <eosio/testing/tester.hpp>
#include <eosio/chain/abi_serializer.hpp>

#include <tgfpio.token/tgfpio.token.wast.hpp>
#include <tgfpio.token/tgfpio.token.abi.hpp>

#include <Runtime/Runtime.h>

#include <fc/variant_object.hpp>

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

using mvo = fc::mutable_variant_object;

typedef uint64_t id_type;
typedef string uri_type;

class tgfpio_tester : public tester {
public:

   tgfpio_tester() {
      produce_blocks( 2 );

      create_accounts( { N(alice), N(bob), N(carol), N(tgfpio.token) } );
      produce_blocks( 2 );

      set_code( N(tgfpio.token), tgfpio_token_wast );
      set_abi( N(tgfpio.token), tgfpio_token_abi );

      produce_blocks();

      const auto& accnt = control->db().get<account_object,by_name>( N(tgfpio.token) );
      abi_def abi;
      BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
      abi_ser.set_abi(abi);
   }

   action_result push_action( const account_name& signer, const action_name &name, const variant_object &data ) {
      string action_type_name = abi_ser.get_action_type(name);

      action act;
      act.account = N(tgfpio.token);
      act.name    = name;
      act.data    = abi_ser.variant_to_binary( action_type_name, data );

      return base_tester::push_action( std::move(act), uint64_t(signer));
   }

   action_result hi( account_name from, account_name to ) {
      return push_action( from, N(hi), mvo()
           ( "user", to)
      );
   }
   abi_serializer abi_ser;
};

BOOST_AUTO_TEST_SUITE(tgfpio_token_tests)

BOOST_FIXTURE_TEST_CASE( can_say_hello, tgfpio_tester ) try {

   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "Hello, alice" ),
                        hi( N(bob), N(alice) )
   );

} FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()
