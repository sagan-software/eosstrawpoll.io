FROM ubuntu:18.04

RUN apt-get update \
    && apt-get install -y git sudo

RUN git clone -b release/1.1 https://github.com/EOSIO/eos.git

WORKDIR /eos

RUN git fetch --all --tags --prune \
    && git merge -m "merge" --commit origin/gh#3030-enable-mongodb

RUN git submodule update --init --recursive

RUN echo 1 | ./eosio_build.sh

RUN cmake --build /eos/build --target install
