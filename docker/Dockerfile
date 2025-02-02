FROM ubuntu:24.04

ENV TZ="Europe/Berlin"

RUN apt-get update && apt-get install -y \
    automake \
    build-essential \
    cmake \
    ninja-build \
    gdb \
    git \
    python3 \
    wget \
    unzip \
    clang \
    > /dev/null

RUN wget https://github.com/openssl/openssl/archive/refs/tags/openssl-3.3.2.zip && \
    unzip openssl-3.3.2.zip && \
    cd openssl-openssl-3.3.2 && \
    ./Configure > /dev/null && make > /dev/null && make install > /dev/null \
