SRC=src/jsmpeg-vnc.c

INC=-Isrc/ffmpeg/include/ -Isrc/libwebsockets/

LIB=src/ffmpeg/lib/libavutil.a src/ffmpeg/lib/libavcodec.a \
	src/ffmpeg/lib/libswscale.a \
	src/libwebsockets/libwebsockets.a

X11 := $(shell pkg-config --cflags --libs x11)

OUT=-o bin/jsmpeg-vnc
VER=-std=c11

jsmpeg-vnc-linux: src/jsmpeg-vnc.c
	gcc ${OUT} ${SRC} ${INC} ${LIB} ${X11} ${VER}
