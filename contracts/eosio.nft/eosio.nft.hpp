/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <string>

namespace eosiosystem {
    class system_contract;
}

namespace eosio {
    using std::string;
    typedef uint128_t uuid;
    typedef uint64_t id_type;
    typedef string uri_type;

    class nft : public contract {
    public:
        nft(account_name self) : contract(self), tokens(_self, _self) {}

        void create(account_name issuer, string symbol);

        void issue(account_name to,
                   asset quantity,
                   vector<string> uris,
                   string memo);

        void transfer(account_name from,
                      account_name to,
                      id_type id,
                      string memo);

        void burn(account_name owner,
                  id_type token_id);

    private:
        friend eosiosystem::system_contract;

        // @abi table accounts i64
        struct account {
            asset balance;

            uint64_t primary_key() const { return balance.symbol.name(); }
        };

        // @abi table stat i64
        struct stats {
            asset supply;
            account_name issuer;

            uint64_t primary_key() const { return supply.symbol.name(); }
            account_name get_issuer() const { return issuer; }
        };

        // @abi table token i64
        struct token {
            id_type id;          // Unique 64 bit identifier,
            uri_type uri;        // RFC 3986
            account_name owner;  // token owner
            asset value;         // token value (1 SYS)

            auto primary_key() const { return id; }
            auto get_account() const { return owner; }
            auto get_uri() const { return uri; }
            auto get_value() const { return value; }

	    uuid get_global_id() const
	    {
		uint128_t self_128 = static_cast<uint128_t>(N(_self));
		uint128_t id_128 = static_cast<uint128_t>(id);
		uint128_t res = (self_128 << 64) | (id_128);
		return res;
	    }
        };

        typedef eosio::multi_index<N(accounts), account> account_index;
        typedef eosio::multi_index<N(stat), stats> currency_index;
        typedef eosio::multi_index<N(token), token> token_index;
        token_index tokens;

        void mint(account_name owner, account_name ram_payer, asset value, string uri);

        void sub_balance(account_name owner, asset value);
        void add_balance(account_name owner, asset value, account_name ram_payer);
        void sub_supply(asset quantity);
        void add_supply(asset quantity);
    };
} /// namespace eosio
