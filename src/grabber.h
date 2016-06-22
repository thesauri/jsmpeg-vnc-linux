#include <X11/Xlib.h>

typedef struct {
	Window window;
  Display *display;

	int width;
	int height;

	void *pixels;
} grabber_t;

grabber_t *grabber_create(Display *display, Window window);
void grabber_destroy(grabber_t *self);
