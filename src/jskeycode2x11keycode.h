#ifndef JSKEYCODE2X11KEYCODE_H
#define JSKEYCODE2X11KEYCODE_H

#include <X11/Xlib.h>

KeyCode js_keycode_to_x11keycode(Display *display, unsigned short keycode);

#endif
