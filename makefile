jsmpeg-vnc-linux: src/jsmpeg-vnc.c
	gcc -o bin/jsmpeg-vnc src/jsmpeg-vnc.c src/ffmpeg/libavutil/libavutil.a
