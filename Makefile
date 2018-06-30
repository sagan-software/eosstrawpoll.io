DOCKER_COMPOSE := docker-compose --file src/docker/docker-compose.yml
DOCKER_EXEC := $(DOCKER_COMPOSE) exec keosd
CLEOS := $(DOCKER_EXEC) cleos -u http://nodeosd:8888 --wallet-url http://localhost:8888
EOSIOCPP := $(DOCKER_EXEC) eosiocpp
PUBKEY := EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV

.PHONY: build build-contracts build-website
build: build-contracts build-website

build-contracts:
	$(DOCKER_EXEC) /build.sh

build-website:
	`npm bin`/bsb -make-world
	NODE_ENV=production `npm bin`/webpack --progress

rm-all-containers:
	#docker stop $$(docker ps -a -q)
	docker rm $$(docker ps -a -q)

rm-all-images:
	docker rmi $$(docker images -q)

rm-all: rm-all-containers rm-all-images

.PHONY: start start-docker start-website

start:
	`npm bin`/concurrently --raw \
		'make start-docker' \
		'make start-website'

start-docker:
	docker volume create --name=nodeos-data-volume
	docker volume create --name=keosd-data-volume
	$(DOCKER_COMPOSE) up

start-website:
	`npm bin`/concurrently --raw --kill-others \
		'`npm bin`/bsb -make-world -w' \
		'TARGET=web `npm bin`/webpack-dev-server --hot --inline --progress' \
		'TARGET=node `npm bin`/webpack -w'
	
clean-docker:
	$(DOCKER_COMPOSE) down
	docker volume prune

setup-chain:
	$(CLEOS) wallet import $(PUBKEY) || exit 0
	$(CLEOS) create account eosio eosio.token $(PUBKEY) $(PUBKEY) || exit 0
	$(CLEOS) create account eosio eosio.msig $(PUBKEY) $(PUBKEY) || exit 0
	$(CLEOS) create account eosio eosio.ram $(PUBKEY) $(PUBKEY)
	$(CLEOS) create account eosio eosio.ramfee $(PUBKEY) $(PUBKEY)
	$(CLEOS) create account eosio eosio.stake $(PUBKEY) $(PUBKEY)
	$(CLEOS) create account eosio eosio.bpay $(PUBKEY) $(PUBKEY)
	$(CLEOS) create account eosio eosio.vpay $(PUBKEY) $(PUBKEY)
	$(CLEOS) create account eosio eosio.saving $(PUBKEY) $(PUBKEY)
	$(CLEOS) create account eosio eosio.names $(PUBKEY) $(PUBKEY)
	$(CLEOS) set contract eosio.token /eos/build/contracts/eosio.token || exit 0
	$(CLEOS) set contract eosio.msig /eos/build/contracts/eosio.token || exit 0
	$(CLEOS) push action eosio.token create '[ "eosio", "10000000000.0000 SYS" ]' -p eosio.token
	$(CLEOS) push action eosio.token issue '[ "eosio", "10000000000.0000 SYS", "memo" ]' -p eosio
	$(CLEOS) set contract eosio /eos/build/contracts/eosio.system || exit 0
	$(CLEOS) push action eosio setpriv '["eosio.msig", 1]' -p eosio@active
	$(CLEOS) system newaccount eosio --transfer eosstrawpoll $(PUBKEY) --stake-net "100000.0000 SYS" --stake-cpu "100000.0000 SYS" --buy-ram-kbytes 2000
	$(CLEOS) system newaccount eosio --transfer alice $(PUBKEY) --stake-net "100000.0000 SYS" --stake-cpu "100000.0000 SYS" --buy-ram-kbytes 512
	$(CLEOS) system newaccount eosio --transfer bob $(PUBKEY) --stake-net "100000.0000 SYS" --stake-cpu "100000.0000 SYS" --buy-ram-kbytes 512
	$(CLEOS) system newaccount eosio --transfer carol $(PUBKEY) --stake-net "100000.0000 SYS" --stake-cpu "100000.0000 SYS" --buy-ram-kbytes 512

#PW5JzF4wenHHG3rus4FYymhP6G4Q6kXe3wrP6gPsTFyp1oCUf6TJ3
redeploy:
	$(EOSIOCPP) --outname /dist/eosstrawpoll.wast /src/eosstrawpoll/eosstrawpoll.cpp
	$(EOSIOCPP) --genabi /dist/eosstrawpoll.abi /src/eosstrawpoll/eosstrawpoll.cpp
	$(CLEOS) set contract eosstrawpoll /dist /dist/eosstrawpoll.wast /dist/eosstrawpoll.abi
	$(CLEOS) get table eosstrawpoll alice polls

create-data:
	$(CLEOS) push action eosstrawpoll close '["alice", "fuckballs", "cleos"]' -p alice@active || exit 0
	$(CLEOS) push action eosstrawpoll create '["alice", "fuckballs", "BALLS","Description A",["Option A","Option B","Option C"],[],[],0,0,0,0,"cleos"]' -p alice@active
	$(CLEOS) push action eosstrawpoll close '["alice", "balls", "cleos"]' -p alice@active || exit 0
	$(CLEOS) push action eosstrawpoll create '["alice","balls", "Neato","Description B",["Option A","Option B","Option C"],[],[],0,0,0,0,"cleos"]' -p alice@active
	$(CLEOS) push action eosstrawpoll close '["bob", "hello", "cleos"]' -p bob@active || exit 0
	$(CLEOS) push action eosstrawpoll create '["bob","hello", "Nice poll title 2","Description C",["Option A","Option B","Option C"],[],[],0,0,0,0,"cleos"]' -p bob@active
	$(CLEOS) push action eosstrawpoll close '["carol", "asdf", "cleos"]' -p carol@active || exit 0
	$(CLEOS) push action eosstrawpoll create '["carol","asdf", "Nice poll title 2","Description D",["Option A","Option B","Option C"],[],[],0,0,0,0,"cleos"]' -p carol@active
	$(CLEOS) push action eosstrawpoll vote '["alice","fuckballs","bob",[1],"cleos"]' -p bob@active
