DOCKER_COMPOSE := docker-compose --file docker/docker-compose.yml
DOCKER_EXEC := $(DOCKER_COMPOSE) exec keosd
CLEOS := $(DOCKER_EXEC) $(EOS_DIR)/bin/cleos -u http://nodeosd:8888 --wallet-url http://localhost:8888

.PHONY: build
build:
	$(DOCKER_EXEC) /build.sh

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

