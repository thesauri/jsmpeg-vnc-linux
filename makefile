SRC=src/jsmpeg-vnc.c
INC=-Isrc/ffmpeg/include/
LIB=src/ffmpeg/lib/libavutil.a src/ffmpeg/lib/libavcodec.a src/ffmpeg/lib/libswscale.a
OUT=-o bin/jsmpeg-vnc
VER=-std=c11

jsmpeg-vnc-linux: src/jsmpeg-vnc.c
	gcc ${OUT} ${SRC} ${INC} ${LIB} ${VER}
