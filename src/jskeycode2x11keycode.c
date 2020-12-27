/* Transforms JavaScript KeyEvent.keyCodes to X11 keycodes

https://guacamole.incubator.apache.org/doc/0.9.5/guacamole-common-js/symbols/src/src_main_webapp_modules_Keyboard.js.html
http://www.cl.cam.ac.uk/~mgk25/ucs/keysym2ucs.c
https://api.kde.org/4.12-api/kdenetwork-apidocs/krfb/html/keysym_8h_source.html
https://rffr.de/wp-content/uploads/manuell/de-dvorak-keysym.xmodmap */

#include <X11/keysym.h>
#include "jskeycode2x11keycode.h"

KeyCode js_keycode_to_x11keycode(Display *display, unsigned short keycode) {
  /* a-z and 0-9 are the same */
  KeySym keysym;

  switch (keycode) {

    case (8): keysym = XK_BackSpace; break;
    case (13): keysym = XK_Return; break;
    case (16): keysym = XK_Shift_L; break;
    case (17): keysym = XK_Control_L; break;
    case (18): keysym = XK_Alt_L; break;
    case (20): keysym = XK_Caps_Lock; break;
    case (27): keysym = XK_Escape; break;
    case (37): keysym = XK_Left; break;
    case (38): keysym = XK_Up; break;
    case (39): keysym = XK_Right; break;
    case (40): keysym = XK_Down; break;
    default: keysym = keycode; break;

  }

  return XKeysymToKeycode(display, keysym);
}
