FROM ubuntu:18.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
      ca-certificates \
      build-essential \
      cmake \
      git \
      make && \
    rm -rf /var/lib/apt/lists/*

COPY . /print
WORKDIR /print

RUN cmake -S . -B _build \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/print/_install && \
    cmake --build _build --config Release && \
    cmake --build _build --config Release --target install

ENV LOG_PATH=/home/logs/log.txt
VOLUME ["/home/logs"]
WORKDIR /print/_install/bin
ENTRYPOINT ["./demo"]
