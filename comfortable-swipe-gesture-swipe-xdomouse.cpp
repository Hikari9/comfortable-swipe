#ifndef __comfortable_swipe_gesture_swipe_xdomouse__
#define __comfortable_swipe_gesture_swipe_xdomouse__
/**
 * File: comfortable-swipe-gesture-swipe-xdomouse.cpp
 *
 *
 */
/*
Comfortable Swipe
by Rico Tiongson

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <cstdio>   // std::sscanf
#include <cstring>  // strncmp
#include <iostream> // std::cout, std::endl

extern "C" {
#include <xdo.h> // xdo_mouse_down
                 // xdo_mouse_up
                 // xdo_move_mouse_relative
                 // CURRENTWINDOW
}

#include "comfortable-swipe-gesture-swipe.cpp"

namespace comfortable_swipe {
// enumerations for mouse hold gesture types
enum {
  MOUSE_NONE = -1,
  MOUSE_MOVE = 0,
  MOUSE_LEFT_CLICK = 1,
  MOUSE_MIDDLE_CLICK = 2,
  MOUSE_RIGHT_CLICK = 3,
  MOUSE_WHEEL_UP = 4,
  MOUSE_WHEEL_DOWN = 5,
  MOUSE_SCROLL = 6,
  MOUSE_SCROLL_REVERSE = 7
};
/**
 * Gesture Swipe mouse gestures class with xdo.
 *
 * If type is MOUSE_*_CLICK, we apply:
 *  - xdo_mouse_down on begin()
 *  - xdo_mouse_up on end()
 *
 * If type is MOUSE_MOVE, we apply:
 *  - xdo_mouse_move_relative on update().
 *
 * If type is MOUSE_WHEEL* or MOUSE_SCROLL*, we apply:
 *  - xdo_mouse_down on update()
 *  - xdo_mouse_up on update()
 */
class gesture_swipe_xdomouse : public gesture_swipe {
public:
  // the button number being clicked
  int button;
  // constructor
  gesture_swipe_xdomouse(const char *mouse3, // 3 finger mouse gesture
                         const char *mouse4  // 4 finger mouse gesture
  );
  // destructor
  virtual ~gesture_swipe_xdomouse();
  // override begin and end for mousedown
  virtual void begin() override;
  virtual void update() override;
  virtual void end() override;
  // provide our own mouse dispatch functions
  virtual void do_mousedown(int button, int fingers);
  virtual void do_mouseup(int button, int fingers);
  // utility method to parse mouse input given config characters
  static int parse_mouse_button(const char *);

protected:
  // command holders
  const char *mouse3;
  const char *mouse4;
};
/**
 * Constructs a new mouse gesture, given "mouse3" and "mouse4" configurations.
 */
gesture_swipe_xdomouse::gesture_swipe_xdomouse(const char *mouse3,
                                               const char *mouse4)
    : gesture_swipe(), button(MOUSE_NONE), mouse3(mouse3), mouse4(mouse4) {}
/**
 * Destructs this mouse swipe gesture.
 */
gesture_swipe_xdomouse::~gesture_swipe_xdomouse() {}
/**
 * Utility method to parse mouse number from input.
 * Returns MOUSE_NONE on failure.
 */
int gesture_swipe_xdomouse::parse_mouse_button(const char *input) {
  // just move without holding button down
  if (std::strcmp(input, "move") == 0)
    return MOUSE_MOVE;
  if (std::strcmp(input, "scroll") == 0)
    return MOUSE_SCROLL;
  if (std::strcmp(input, "scroll_reverse") == 0)
    return MOUSE_SCROLL_REVERSE;
  // get button number
  int button;
  if (std::sscanf(input, "button%d", &button) == 1) {
    if (1 <= button && button <= 6) {
      return button;
    }
  }
  return MOUSE_NONE;
}
/**
 * Run mousedown command on a mouse button input.
 */
void gesture_swipe_xdomouse::do_mousedown(int button, int fingers) {
  if (MOUSE_LEFT_CLICK <= button && button <= MOUSE_RIGHT_CLICK) {
    // send mouse down on associated button
    xdo_mouse_down(xdo, CURRENTWINDOW, button);
  }
}
/**
 * Run mouseup command on a mouse button output.
 */
void gesture_swipe_xdomouse::do_mouseup(int button, int fingers) {
  if (MOUSE_LEFT_CLICK <= button && button <= MOUSE_RIGHT_CLICK) {
    // send mouse up on associated button
    xdo_mouse_up(xdo, CURRENTWINDOW, button);
  }
}
/**
 * Hook on begin of mouse swipe gesture.
 */
void gesture_swipe_xdomouse::begin() {
  // call superclass method
  gesture_swipe::begin();
  // map fingers to gesture command
  auto command = fingers == 3 ? mouse3 : (fingers == 4 ? mouse4 : NULL);
  if (command != NULL) {
    // get button int from the command
    button = parse_mouse_button(command);
    // perform mousedown on the button and print to console
    if (button != MOUSE_NONE) {
      do_mousedown(button, fingers);
      std::printf("MOUSE DOWN mouse%d %s\n", this->fingers, command);
    }
  }
}
/**
 * Hook on end of mouse swipe gesture.
 */
void gesture_swipe_xdomouse::update() {
  // call superclass method
  gesture_swipe::update();
  if (button != MOUSE_NONE) {
    // if MOUSE_MOVE or MOUSE_CLICK*
    if (0 <= button && button <= 3) {
      // drag mouse with pointer during update
      xdo_move_mouse_relative(xdo, udx, udy);
    } else if (button == MOUSE_SCROLL || button == MOUSE_SCROLL_REVERSE) {
      // perform naive scroll depending on vertical direction
      int wheel = MOUSE_WHEEL_DOWN;
      if ((udy > 0) == (button == MOUSE_SCROLL))
        wheel = MOUSE_WHEEL_UP;
      // click wheel on update (note: this is not precise)
      xdo_mouse_down(xdo, CURRENTWINDOW, wheel);
      xdo_mouse_up(xdo, CURRENTWINDOW, wheel);
    } else if (button == MOUSE_WHEEL_UP || button == MOUSE_WHEEL_DOWN) {
      // click wheel button on 4 or 5
      xdo_mouse_down(xdo, CURRENTWINDOW, button);
      xdo_mouse_up(xdo, CURRENTWINDOW, button);
    }
  }
}
/**
 * Hook on end of swipe gesture.
 */
void gesture_swipe_xdomouse::end() {
  // optimization: only perform mouseup when flag is set
  if (button != MOUSE_NONE) {
    // map fingers to gesture command
    // perform mouseup on the button and print to console
    do_mouseup(button, fingers);
    std::printf("MOUSE UP mouse%d %s\n", fingers,
                fingers == 3 ? mouse3 : mouse4);
  }
  // reset button
  button = MOUSE_NONE;
  // call superclass method
  gesture_swipe::end();
}
} // namespace comfortable_swipe

#endif /* __comfortable_swipe_gesture_swipe_xdomouse__ */
