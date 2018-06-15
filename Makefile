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
		'`npm bin`/webpack-dev-server --hot --inline --host 0.0.0.0 --progress'
	
clean-docker:
	$(DOCKER_COMPOSE) down
	docker volume prune

create-accounts:
	$(CLEOS) create account eosio twitteos EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
	$(CLEOS) create account eosio alice EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
	$(CLEOS) create account eosio bob EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
#PW5KXc42E2KDFrGw3YRzL2YVfkCBFFnrvtySxhP1Ywg3y5k89RMJt
redeploy:
	$(EOSIOCPP) --outname /dist/twitteos.wast /src/twitteos/twitteos.cpp
	$(EOSIOCPP) --genabi /dist/twitteos.abi /src/twitteos/twitteos.cpp
	$(CLEOS) set contract twitteos /dist /dist/twitteos.wast /dist/twitteos.abi
	$(CLEOS) push action twitteos create '["alice","Hello world"]' -p alice@active
	$(CLEOS) get table twitteos alice posts
