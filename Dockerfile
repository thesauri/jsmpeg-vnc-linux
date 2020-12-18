FROM ubuntu:20.04
ENV TZ=Europe/Stockholm
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update
RUN apt-get install -y git
RUN apt-get install -y build-essential
RUN apt-get install -y cmake
RUN apt-get install -y libx11-dev
RUN apt-get install -y libavutil-dev
RUN apt-get install -y libavcodec-dev
RUN apt-get install -y libswscale-dev
RUN apt-get install -y libxtst-dev
RUN apt-get install -y libssl-dev
RUN apt-get install -y pkg-config
RUN apt-get install -y zlib1g-dev

RUN git clone --branch v4.1-stable --depth 1 https://github.com/warmcat/libwebsockets.git
RUN mkdir -p jsmpeg-vnc-linux/libwebsockets

WORKDIR jsmpeg-vnc-linux/libwebsockets

RUN cmake /libwebsockets/
RUN make
RUN make install
RUN ls -l bin/

WORKDIR /jsmpeg-vnc-linux/

COPY . ./
RUN cmake .
RUN make

ENV LD_LIBRARY_PATH /usr/local/lib

CMD ["/jsmpeg-vnc-linux/jsmpeg-vnc", "-b", "2000", "-s", "640x480", "-f", "39", "desktop"]

