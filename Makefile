DOCKER_COMPOSE := docker-compose --file docker/docker-compose.yml
DOCKER_EXEC := $(DOCKER_COMPOSE) exec keosd
EOS_DIR := /opt/eosio
EOS_ROOT := /eos
CLEOS := $(DOCKER_EXEC) $(EOS_DIR)/bin/cleos -u http://nodeosd:8888 --wallet-url http://localhost:8888
EOSIOCPP := $(DOCKER_EXEC) $(EOS_DIR)/bin/eosiocpp
UNIT_TEST := $(DOCKER_EXEC) $(EOS_DIR)/unittests/unit_test --show_progress=yes
UNIT_TESTS := $(subst .,_,$(basename $(notdir $(shell find unittests -type f -name "*.cpp"))))

CONTRACT_DIRS := $(shell find contracts -mindepth 1 -maxdepth 1 -type d)
CONTRACT_ABIS := $(foreach dir,$(CONTRACT_DIRS),$(addsuffix /$(notdir $(dir)).abi,$(dir)))

tmp:
	@echo $(UNIT_TESTS)

help:
	@echo "Help"

rm-all-containers:
	#docker stop $$(docker ps -a -q)
	docker rm $$(docker ps -a -q)

rm-all-images:
	docker rmi $$(docker images -q)

rm-all: rm-all-containers rm-all-images

init-eos:
	docker volume create --name=nodeos-data-volume
	docker volume create --name=keosd-data-volume
	$(DOCKER_COMPOSE) up
	
clean-eos:
	$(DOCKER_COMPOSE) down
	docker volume prune

setup-account:
	#./cleos.sh wallet create
	./cleos.sh wallet import 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3
	./cleos.sh create account eosio tgfpio EOS81GrdAMzzb2FeXiZ1Jq1sKt1CWm9JpFw3RdHnYXmBv1mrQUnSK
	./cleos.sh get account tgfpio

unlock-wallet:
	./cleos.sh wallet unlock --password PW5HukHeyyji3cs5UA4wjeHWgDdEz6nYwHLzPQqy7j74U423nV1gk

deploy-contract: build-contract
	./cleos.sh set contract tgfpio /src/hello

# PW5HukHeyyji3cs5UA4wjeHWgDdEz6nYwHLzPQqy7j74U423nV1gk
# Private key: 5Ke8RjcEEeR8sCHbm44HTy7yhpz1xWx6CT8emt6CjhNVPngteik
# Public key: EOS81GrdAMzzb2FeXiZ1Jq1sKt1CWm9JpFw3RdHnYXmBv1mrQUnSK

.PHONY: all
all: build test

.PHONY: build-abis
build-abis: $(CONTRACT_ABIS)

.PHONY: build
build: build-abis
	$(DOCKER_EXEC) cmake -H"$(EOS_ROOT)" \
		-B"$(EOS_DIR)" \
		-GNinja \
		-DCMAKE_BUILD_TYPE=Release \
		-DWASM_ROOT=/opt/wasm \
		-DCMAKE_CXX_COMPILER=clang++ \
		-DCMAKE_C_COMPILER=clang \
		-DCMAKE_INSTALL_PREFIX=$(EOS_DIR) \
		-DSecp256k1_ROOT_DIR=/usr/local \
		-DBUILD_MONGO_DB_PLUGIN=true \
		-DCORE_SYMBOL_NAME=SYS
	$(DOCKER_EXEC) cmake --build $(EOS_DIR) --target install

%.abi: %.cpp %.hpp
	$(EOSIOCPP) -g $(EOS_ROOT)/$@ $(EOS_ROOT)/$<

.PHONY: test
test: $(UNIT_TESTS)

%_tests:
	$(UNIT_TEST) --run_test=$@
