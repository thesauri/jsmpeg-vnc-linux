#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  return self;
}

void grabber_destroy(grabber_t *self) {
  if (self != NULL) {
    //free(self->pixels);
    free(self);
  }
}
