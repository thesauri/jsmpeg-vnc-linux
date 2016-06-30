#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/X.h>

#include "app.h"
#include "grabber.h"

void exit_usage(char *self_name) {
    printf(
           "Usage: %s [options] <window name>\n\n"

           "Options:\n"
           "	-b bitrate in kilobit/s (default: estimated by output size)\n"
           "	-s output size as WxH. E.g: -s 640x480 (default: same as window size)\n"
           "	-f target framerate (default: 60)\n"
           "	-p port (default: 8080)\n"
           "  -d dump screen data to out.bin\n"
           "  -i target display as hostname:number.screen_number\n\n"

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
        height = 0,
        dump = 0;

    char *display_name;

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
            case 'i': display_name = argv[i+1]; break;
            case 'd': dump = 1; break;
            default: exit_usage(argv[0]);
        }
    }

    char *window_title = argv[argc-1];

    Display *display = XOpenDisplay(display_name);
    Window window;

    if (strcmp(window_title, "desktop") == 0) {
      window = DefaultRootWindow(display);
    } else if (strcmp(window_title, "cursor") == 0) {
      printf("Window at cursor not implemented yet..\n");
      return 0;
    } else {
      printf("Window from window title not implemented yet..\n");
      return 0;
    }

    if (dump) {
      grabber_t *grabber = grabber_create(display, window);

      FILE *file = fopen("out.bin", "w+");
      fwrite(grabber->pixels, 1, grabber->pixels_size, file);
      fclose(file);

      printf("Screen data dumped to out.bin\n");

      return 0;
    } else {
      app_t *app = app_create(display, window, port, bit_rate, width, height);

    	if( !app ) {
    		return 1;
    	}

      printf(
    		//"Window 0x%08x: \"%s\"\n"
    		"Window size: %dx%d, output size: %dx%d, bit rate: %d kb/s\n\n"
    		"Server started on: http://%s:%d/\n\n",
    		//window, real_window_title,
    		app->grabber->width, app->grabber->height,
    		app->encoder->out_width, app->encoder->out_height,
    		app->encoder->context->bit_rate / 1000,
    		server_get_host_address(app->server), app->server->port
      );

      app_run(app, fps);

	    app_destroy(app);

      return 0;
    }
}
