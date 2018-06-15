FROM eosio/builder
ARG branch=master
ARG symbol=SYS

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get -y install openssl vim psmisc python3-pip && rm -rf /var/lib/apt/lists/*
RUN pip3 install numpy

RUN git clone -b $branch https://github.com/EOSIO/eos.git --recursive \
    && cd eos \
    && echo "$branch:$(git rev-parse HEAD)" > /etc/eosio-version

ENV EOSIO_ROOT=/opt/eosio

ADD ./config.ini /config.ini

ADD ./build.sh /build.sh
RUN chmod +x /build.sh
RUN /build.sh

ADD ./start_nodeosd.sh /start_nodeosd.sh
RUN chmod +x /start_nodeosd.sh

ENV LD_LIBRARY_PATH /usr/local/lib

VOLUME /opt/eosio/bin/data-dir
VOLUME /opt/eosio/include

ENV PATH /opt/eosio/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
