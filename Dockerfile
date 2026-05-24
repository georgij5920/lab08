FROM ubuntu:18.04

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

RUN mkdir -p _build && \
    cd _build && \
    cmake .. \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/print/_install && \
    cmake --build . --config Release && \
    cmake --build . --config Release --target install

ENV LOG_PATH=/home/logs/log.txt

VOLUME /home/logs

ENTRYPOINT ["/print/_install/bin/demo"]
