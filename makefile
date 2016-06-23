SRC = src/jsmpeg-vnc.c src/encoder.c src/grabber.c src/server.c

INC = -Isrc/ -Isrc/libwebsockets/

LIB_DIRS = -Lsrc/zlib/ -Lsrc/libwebsockets/

LWEBSOCKETS = -lz -lwebsockets

FFMPEG = $(shell pkg-config --cflags --libs libavcodec libavutil libswscale)

X11 = $(shell pkg-config --cflags --libs x11)

OUT = -o bin/jsmpeg-vnc
VER= -std=c11

jsmpeg-vnc-linux: src/jsmpeg-vnc.c
	gcc ${OUT} ${SRC} ${INC} ${LIB_DIRS} ${LWEBSOCKETS} ${FFMPEG} ${X11} ${VER}
