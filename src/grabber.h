#include <X11/Xlib.h>

typedef struct {
	Window window;
  Display *display;

	int width;
	int height;

	void *pixels;
  int pixels_size;
} grabber_t;

grabber_t *grabber_create(Display *display, Window window);
void grabber_destroy(grabber_t *self);
void *grabber_grab(grabber_t *self);
