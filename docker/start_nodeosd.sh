#!/bin/sh

echo "Waiting for MongoDB.."
# until mongo --host mongo-master:27017 --eval 'quit(db.runCommand({ ping: 1 }).ok ? 0 : 2)' &>/dev/null; do
#   printf '.'
#   sleep 1
# done

sleep 20

cd /eos/build

#/build.sh

if [ -f '/mnt/dev/config/config.ini' ]; then
    echo
  else
    cp /config.ini /mnt/dev/config
fi

exec nodeos \
    --data-dir /mnt/dev/data \
    --config-dir /mnt/dev/config \
    --replay-blockchain \
    --delete-all-blocks \
    --enable-stale-production \
    --mongodb-wipe \
    --unlock-timeout 999999 \
    "$@"

#nodeos -e -p eosio --plugin eosio::wallet_api_plugin --plugin eosio::wallet_plugin --plugin eosio::producer_plugin --plugin eosio::history_plugin --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --plugin eosio::http_plugin -d /mnt/dev/data --config-dir /mnt/dev/config --http-server-address=0.0.0.0:8888 --access-control-allow-origin=* --contracts-console
