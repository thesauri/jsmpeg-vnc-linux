#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xutil.h>

#include "grabber.h"

grabber_t *grabber_create(Display *display, Window window) {
  grabber_t *self = (grabber_t *) malloc(sizeof(grabber_t));
  memset(self, 0, sizeof(grabber_t));

  XWindowAttributes gwa;
  XGetWindowAttributes(display, window, &gwa);

  self->width = gwa.width;
  self->height = gwa.height;
  self->display = display;
  self->window = window;

  self->pixels_size = self->width * self->height * 4;
  self->pixels = malloc(self->pixels_size);

  return self;
}

void grabber_destroy(grabber_t *self) {
  if (self != NULL) {
    free(self->pixels);
    free(self);
  }
}

void *grabber_grab(grabber_t *self) {
  XImage *image = XGetImage(self->display,
                            self->window,
                            0, 0,
                            self->width, self->height,
                            AllPlanes,
                            ZPixmap);

  memcpy(self->pixels, image->data, self->pixels_size);

  XDestroyImage(image);

  return self->pixels;
}
