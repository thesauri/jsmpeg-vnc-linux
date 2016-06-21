SRC=src/jsmpeg-vnc.c

INC=-Isrc/ffmpeg/include/ -Isrc/libwebsockets/

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	INC+=-I/opt/X11/include
endif

LIB=src/ffmpeg/lib/libavutil.a src/ffmpeg/lib/libavcodec.a src/ffmpeg/lib/libswscale.a src/libwebsockets/libwebsockets.a
OUT=-o bin/jsmpeg-vnc
VER=-std=c11

jsmpeg-vnc-linux: src/jsmpeg-vnc.c
	gcc ${OUT} ${SRC} ${INC} ${LIB} ${VER}
