#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void exit_usage(char *self_name) {
    printf(
           "Usage: %s [options] <window name>\n\n"

           "Options:\n"
           "	-b bitrate in kilobit/s (default: estimated by output size)\n"
           "	-s output size as WxH. E.g: -s 640x480 (default: same as window size)\n"
           "	-f target framerate (default: 60)\n"
           "	-p port (default: 8080)\n\n"

           "Use \"desktop\" as the window name to capture the whole Desktop. Use \"cursor\"\n"
           "to capture the window at the current cursor position.\n\n"

           "To enable mouse lock in the browser (useful for games that require relative\n"
           "mouse movements, not absolute ones), append \"?mouselock\" at the target URL.\n"
           "i.e: http://<server-ip>:8080/?mouselock\n\n",
           self_name
           );
    exit(0);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        exit_usage(argv[0]);
    }

    int bit_rate = 0,
        fps = 60,
        port = 8080,
        width = 0,
        height = 0;

    char display[32] = ":0.1";

    // Parse command line options
    for (int i = 1; i < argc-1; i+=2) {
        if (strlen(argv[i]) < 2 || i >= argc-2 || argv[i][0] != '-') {
            exit_usage(argv[0]);
        }

        switch (argv[i][1]) {
            case 'b': bit_rate = atoi(argv[i+1]) * 1000; break;
            case 'p': port = atoi(argv[i+1]); break;
            case 's': sscanf(argv[i+1], "%dx%d", &width, &height); break;
            case 'f': fps = atoi(argv[i+1]); break;
            case 'i': strcpy(display, argv[i+1]); break;
            default: exit_usage(argv[0]);
        }
    }
}
