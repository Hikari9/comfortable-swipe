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
  gesture_swipe_xdomouse(const char *hold3, // 3 finger mouse down
                    const char *hold4  // 4 finger mouse down
  );
  // destructor
  virtual ~gesture_swipe_xdomouse();
  // override begin and end for mousedown
  virtual void begin() override;
  virtual void update() override;
  virtual void end() override;
  // provide our own mouse dispatch functions
  virtual void do_mousedown(const char *);
  virtual void do_mouseup(const char *);
  // utility method to check if mouse is being held
  virtual bool is_holding() const;
  // utility method to parse mouse input given config characters
  static int parse_mouse_button(const char *);
protected:
  // command holders
  const char *hold3;
  const char *hold4;
private:
  // flag we can use to check if mouse is down
  bool flag_is_holding;
};
/**
 * Constructs a new mouse gesture, given "hold3" and "hold4" configurations.
 */
gesture_swipe_xdomouse::gesture_swipe_xdomouse(const char *hold3, const char *hold4)
    : gesture_swipe(), button(MOUSE_NONE), hold3(hold3), hold4(hold4),
      flag_is_holding(false) {}
/**
 * Destructs this mouse swipe gesture.
 */
gesture_swipe_xdomouse::~gesture_swipe_xdomouse() {}
/**
 * Determines if some mousehold command is being run.
 */
bool gesture_swipe_xdomouse::is_holding() const {
  return this->flag_is_holding;
}
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
 * Perform mousedown command on hold input.
 */
void gesture_swipe_xdomouse::do_mousedown(const char *input) {
  const int button = this->button = this->parse_mouse_button(input);
  if (button != MOUSE_NONE) {
    // eg. MOUSE DOWN hold3 mouse1
    std::printf("MOUSE DOWN hold%d %s\n", this->fingers, input);
    if (MOUSE_LEFT_CLICK <= button && button <= MOUSE_RIGHT_CLICK) {
      // send mouse down on associated button
      xdo_mouse_down(this->xdo, CURRENTWINDOW, button);
    }
    this->flag_is_holding = true;
  }
}
/**
 * Run mouseup command on hold output.
 */
void gesture_swipe_xdomouse::do_mouseup(const char *input) {
  const int button = this->button = this->parse_mouse_button(input);
  if (button != MOUSE_NONE) {
    std::printf("MOUSE UP hold%d %s\n", this->fingers, input);
    if (MOUSE_LEFT_CLICK <= button && button <= MOUSE_RIGHT_CLICK) {
      // send mouse up on associated button
      xdo_mouse_up(this->xdo, CURRENTWINDOW, button);
    }
    this->flag_is_holding = false;
  }
}
/**
 * Hook on begin of mouse swipe gesture.
 */
void gesture_swipe_xdomouse::begin() {
  // call superclass method
  gesture_swipe::begin();
  // dispatch mouse down event
  if (this->fingers == 3) {
    this->do_mousedown(this->hold3);
  } else if (this->fingers == 4) {
    this->do_mousedown(this->hold4);
  }
}
/**
 * Hook on end of mouse swipe gesture.
 */
void gesture_swipe_xdomouse::update() {
  // call superclass method
  gesture_swipe::update();
  if (this->is_holding()) {
    // if MOUSE_MOVE or MOUSE_CLICK*
    if (0 <= this->button && this->button <= 3) {
      // drag mouse with pointer during update
      xdo_move_mouse_relative(this->xdo, this->udx, this->udy);
    } else if (this->button == MOUSE_SCROLL ||
               this->button == MOUSE_SCROLL_REVERSE) {
      // perform naive scroll depending on vertical direction
      int wheel = MOUSE_WHEEL_DOWN;
      if ((this->udy > 0) == (this->button == MOUSE_SCROLL))
        wheel = MOUSE_WHEEL_UP;

      // click wheel on update (note: this is not precise)
      xdo_mouse_down(this->xdo, CURRENTWINDOW, wheel);
      xdo_mouse_up(this->xdo, CURRENTWINDOW, wheel);
    } else if (this->button == MOUSE_WHEEL_UP ||
               this->button == MOUSE_WHEEL_DOWN) {
      // click wheel button on 4 or 5
      xdo_mouse_down(this->xdo, CURRENTWINDOW, this->button);
      xdo_mouse_up(this->xdo, CURRENTWINDOW, this->button);
    }
  }
}
/**
 * Hook on end of swipe gesture.
 */
void gesture_swipe_xdomouse::end() {
  // optimization: only perform mouseup when flag is set
  if (this->is_holding()) {
    if (this->fingers == 3) {
      this->do_mouseup(this->hold3);
    } else if (this->fingers == 4) {
      this->do_mouseup(this->hold4);
    }
  }
  // call superclass method
  gesture_swipe::end();
}
}

#endif /* __comfortable_swipe_gesture_swipe_xdomouse__ */
