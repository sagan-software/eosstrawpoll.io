#!/bin/bash
echo "STARTING!!!!!!"

for path in /src/contracts/*; do
    ln -f -s ${path} /eos/${path#/src/}
    echo "${path}"
    echo "/eos/${path#/src/}"
    echo "/opt/eosio/${path#/src/}"
done

for path in /src/unittests/*; do
    ln -f -s ${path} /eos/${path#/src/}
    echo "${path}"
    echo "/eos/${path#/src/}"
    echo "/opt/eosio/${path#/src/}"
done

/opt/eosio/bin/keosd
