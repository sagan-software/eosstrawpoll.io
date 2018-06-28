DOCKER_COMPOSE := docker-compose --file src/docker/docker-compose.yml
DOCKER_EXEC := $(DOCKER_COMPOSE) exec keosd
CLEOS := $(DOCKER_EXEC) cleos -u http://nodeosd:8888 --wallet-url http://localhost:8888
EOSIOCPP := $(DOCKER_EXEC) eosiocpp

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
	`npm bin`/concurrently --raw \
		'`npm bin`/bsb -make-world -w' \
		'TARGET=web `npm bin`/webpack-dev-server --hot --inline --progress' \
		'TARGET=node `npm bin`/webpack -w'
	
clean-docker:
	$(DOCKER_COMPOSE) down
	docker volume prune

create-accounts:
	$(CLEOS) wallet import 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3 || exit 0
	$(CLEOS) create account eosio eosio.token EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
	$(CLEOS) create account eosio eosio.msig EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
	$(CLEOS) create account eosio eosio.ram EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
	$(CLEOS) create account eosio eosio.ramfee EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
	$(CLEOS) create account eosio eosio.stake EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
	$(CLEOS) create account eosio eosio.bpay EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
	$(CLEOS) create account eosio eosio.vpay EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
	$(CLEOS) create account eosio eosio.saving EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
	$(CLEOS) create account eosio eosio.names EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
	$(CLEOS) create account eosio eosstrawpoll EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
	$(CLEOS) create account eosio alice EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
	$(CLEOS) create account eosio bob EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
	$(CLEOS) create account eosio carol EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV

deploy-system-contracts:
	$(CLEOS) set contract eosio.token /eos/build/contracts/eosio.token || exit 0
	$(CLEOS) set contract eosio.msig /eos/build/contracts/eosio.token || exit 0
	$(CLEOS) push action eosio.token create '[ "eosio", "10000000000.0000 SYS" ]' -p eosio.token
	$(CLEOS) set contract eosio /eos/build/contracts/eosio.system || exit 0

#PW5JVMECmBvYyedmQgMa149MxnHTTdBY1cDW7WxD1R2DzdsUQcVoW
redeploy:
	$(EOSIOCPP) --outname /dist/eosstrawpoll.wast /src/eosstrawpoll/eosstrawpoll.cpp
	$(EOSIOCPP) --genabi /dist/eosstrawpoll.abi /src/eosstrawpoll/eosstrawpoll.cpp
	$(CLEOS) set contract eosstrawpoll /dist /dist/eosstrawpoll.wast /dist/eosstrawpoll.abi
	$(CLEOS) get table eosstrawpoll alice polls

create-polls:
	$(CLEOS) push action eosstrawpoll create '["alice","Nice poll title 1","Description A",["Option A","Option B","Option C"],[],[],0,0,0,0]' -p alice@active
	$(CLEOS) push action eosstrawpoll create '["alice","Nice poll title 2","Description B",["Option A","Option B","Option C"],[],[],0,0,0,0]' -p alice@active
	$(CLEOS) push action eosstrawpoll create '["bob","Nice poll title 2","Description C",["Option A","Option B","Option C"],[],[],0,0,0,0]' -p bob@active
	$(CLEOS) push action eosstrawpoll create '["carol","Nice poll title 2","Description D",["Option A","Option B","Option C"],[],[],0,0,0,0]' -p carol@active

create-votes:
	$(CLEOS) push action eosstrawpoll vote '["alice",0,"bob",[1]]' -p bob@active
