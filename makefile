INC=-Isrc/ffmpeg/include/

jsmpeg-vnc-linux: src/jsmpeg-vnc.c
	gcc -o bin/jsmpeg-vnc src/jsmpeg-vnc.c ${INC} src/ffmpeg/lib/libavutil.a -std=c11
