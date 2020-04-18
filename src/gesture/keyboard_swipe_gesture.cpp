#ifndef __COMFORTABLE_SWIPE__gesture_keyboard_swipe_gesture__
#define __COMFORTABLE_SWIPE__gesture_keyboard_swipe_gesture__

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

#include "keyboard_swipe_gesture.h"
#include <iostream> // std::cout, std::endl

extern "C" {
#include <xdo.h> // xdo, xdo_new, xdo_free,
                 // xdo_get_mouse_location
                 // CURRENT_WINDOW
}

namespace comfortable_swipe::gesture {

/* STATICS DEFINITIONS */
const int keyboard_swipe_gesture::MSK_THREE_FINGERS = 0;
const int keyboard_swipe_gesture::MSK_FOUR_FINGERS = 1;
const int keyboard_swipe_gesture::MSK_NEGATIVE = 0;
const int keyboard_swipe_gesture::MSK_POSITIVE = 2;
const int keyboard_swipe_gesture::MSK_HORIZONTAL = 0;
const int keyboard_swipe_gesture::MSK_VERTICAL = 4;
const int keyboard_swipe_gesture::FRESH = -1;
const char *const keyboard_swipe_gesture::command_map[8] = {
    "left3", "left4", "right3", "right4", "up3", "up4", "down3", "down4"};

/**
 * Constructs a new keyboard-based swipe gesture, given configurations
 * for certain swipe events. Here, we construct our definition based on
 * the four directions (left, up, right, down) for 3-finger and 4-finger
 * swipes. Note that the direction is based on the Australian natural
 * scrolling direction (ie. left3 is natural movement of 3 fingers left).
 */
keyboard_swipe_gesture::keyboard_swipe_gesture(
    const float threshold, const char *left3 /* 000 */,
    const char *left4 /* 001 */, const char *right3 /* 010 */,
    const char *right4 /* 011 */, const char *up3 /* 100 */,
    const char *up4 /* 101 */, const char *down3 /* 110 */,
    const char *down4 /* 111 */
    )
    : // construct superclass
      comfortable_swipe::gesture::swipe_gesture(),
      // compute square of threshold because we will use squared distances
      threshold_squared(threshold * threshold),
      // register our commands
      commands(new const char *[8] {
        left3, left4, right3, right4, up3, up4, down3, down4
      }) {}

/**
 * Destructs this keyboard swipe gesture.
 */
keyboard_swipe_gesture::~keyboard_swipe_gesture() { delete[] commands; }

/**
 * Hook on begin of swipe gesture.
 */
void keyboard_swipe_gesture::begin() {
  // call superclass method
  swipe_gesture::begin();

  // assign previous gesture to FRESH
  this->previous_gesture = keyboard_swipe_gesture::FRESH;
}

/**
 * Hook on update of swipe gesture.
 */
void keyboard_swipe_gesture::update() {
  // call superclass method
  swipe_gesture::update();

  // scale threshold to 1/10 when gesture is not fresh
  float scale = this->previous_gesture == keyboard_swipe_gesture::FRESH
                    ? 1.00f
                    : 0.01f; // square root of 1/10

  // we are working with floating points which are not exact
  // make sure we compare with a very small value (epsilon)
  static const float EPSILON = 1e-6f;
  const float distance_squared = this->x * this->x + this->y * this->y;
  const float beyond_threshold = this->threshold_squared * scale;

  // apply if strictly beyond threshold
  if (distance_squared > beyond_threshold + EPSILON) {
    // we parse our mask based on the values obtained from the regex
    int mask = 0;

    if (this->fingers == 3)
      mask |= keyboard_swipe_gesture::MSK_THREE_FINGERS;

    else if (this->fingers == 4)
      mask |= keyboard_swipe_gesture::MSK_FOUR_FINGERS;

    const float absx = x >= 0 ? x : -x;
    const float absy = y >= 0 ? y : -y;

    if (absx > absy) {
      // gesture is horizontal
      mask |= keyboard_swipe_gesture::MSK_HORIZONTAL;
      if (x < 0)
        mask |= keyboard_swipe_gesture::MSK_NEGATIVE;
      else
        mask |= keyboard_swipe_gesture::MSK_POSITIVE;
    } else /* std::abs(x) <= std::abs(y) */
    {
      // gesture is vertical
      mask |= keyboard_swipe_gesture::MSK_VERTICAL;
      if (y < 0)
        mask |= keyboard_swipe_gesture::MSK_NEGATIVE;
      else
        mask |= keyboard_swipe_gesture::MSK_POSITIVE;
    }

    // send command on fresh OR opposite gesture
    if (this->previous_gesture == keyboard_swipe_gesture::FRESH ||
        this->previous_gesture ==
            (mask ^ keyboard_swipe_gesture::MSK_POSITIVE)) {
      this->do_keyboard_gesture(mask);
    }
  }
}

/**
 * Apply the update given a mask.
 */
void keyboard_swipe_gesture::do_keyboard_gesture(int mask) {
  // perform our keyboard command with xdo_send_keysequence
  const char *command = keyboard_swipe_gesture::commands[mask];
  xdo_send_keysequence_window(this->xdo, CURRENTWINDOW, command, 0);

  // reset our location variables
  this->x = this->y = 0;
  this->previous_gesture = mask;

  // log our command name in stdout
  const char *command_name = keyboard_swipe_gesture::command_map[mask];
  std::cout << "SWIPE " << command_name << std::endl;
}

/**
 * Hook on end of swipe gesture.
 */
void keyboard_swipe_gesture::end() {
  // call superclass method
  swipe_gesture::end();
}

} // namespace comfortable_swipe::gesture

#endif /* __COMFORTABLE_SWIPE__gesture_keyboard_swipe_gesture__ */
