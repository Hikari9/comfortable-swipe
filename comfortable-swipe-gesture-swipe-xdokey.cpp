#ifndef __comfortable_swipe_gesture_swipe_xdokey__
#define __comfortable_swipe_gesture_swipe_xdokey__

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

#include <iostream> // std::cout, std::endl
#include <array> // std::array
#include <string> // std::string

extern "C" {
#include <xdo.h> // xdo_send_keysequence_window
                 // CURRENT_WINDOW
}

#include "comfortable-swipe-gesture-swipe.cpp"

namespace comfortable_swipe {
/**
 * Gesture Swipe keyboard-swipe gestures class with xdo.
 *
 * Performs a swipe in one of the four cardinal directions:
 * left, right, up, down. Applicable for 3 or 4 fingers.
 *
 * When constructing, please mind the order in the
 * `gesture_swipe_xdokey::command_name[]` static array.
 */
class gesture_swipe_xdokey : public gesture_swipe
{
public:
// stores the 8 command strings for xdo to execute
std::array<std::string, 8> commands;
// constructor
gesture_swipe_xdokey(const decltype(commands)& commands, float threshold=0);
// destructor
virtual ~gesture_swipe_xdokey();
// hooks that we override
virtual void begin() override;
virtual void update() override;
virtual void end() override;
// override this when keyboard gesture is to be performed
virtual void do_keyboard_gesture(int mask);
protected:
    // stores square of threshold so we can compute faster
    float threshold_squared;
    // stores previous gesture so we don't repeat action
    int previous_gesture;
public:
// static enums we will use for gesture matching
static const int FRESH = -1;
static const int MSK_THREE_FINGERS = 0;
static const int MSK_FOUR_FINGERS = 1;
static const int MSK_NEGATIVE = 0;
static const int MSK_POSITIVE = 2;
static const int MSK_HORIZONTAL = 0;
static const int MSK_VERTICAL = 4;
// mappings to our command string names
static const std::string command_name[];
};
/**
 * Our mapped directional command names. These will be
 * printed to the console during execution:
 *
 *      SWIPE <command_name>
 *
 * Refer to the order of this array for the "commands"
 * paramter in the constructor.
 */
decltype(gesture_swipe_xdokey::command_name)
gesture_swipe_xdokey::command_name = {
    // the order of variables is based on bitmasking
    // <VERTICAL?>  | <POSITIVE?>  | <FOUR FINGERS?>
    "left3",  // 000
    "left4",  // 001
    "right3", // 010
    "right4", // 011
    "up3",    // 100
    "up4",    // 101
    "down3",  // 110
    "down4"   // 111
};
/**
 * Constructs a new keyboard-based swipe gesture, given configurations
 * for certain swipe events. Here, we construct our definition based on
 * the four directions (left, up, right, down) for 3-finger and 4-finger
 * swipes. Note that the direction is based on the Australian natural
 * scrolling direction (ie. left3 is natural movement of 3 fingers left).
 */
gesture_swipe_xdokey::gesture_swipe_xdokey(
    const decltype(gesture_swipe_xdokey::commands)& commands,
    float threshold
): gesture_swipe(), commands(commands), threshold_squared(threshold * threshold) {}
/**
 * Destructs this keyboard swipe gesture.
 */
gesture_swipe_xdokey::~gesture_swipe_xdokey() { }
/**
 * Hook on begin of swipe gesture.
 */
void gesture_swipe_xdokey::begin() {
  // call superclass method
  gesture_swipe::begin();
  // assign previous gesture to FRESH
  this->previous_gesture = gesture_swipe_xdokey::FRESH;
}
/**
 * Hook on update of swipe gesture.
 */
void gesture_swipe_xdokey::update() {
  // call superclass method
  gesture_swipe::update();
  // scale threshold to 1/10 when gesture is not fresh
  float scale = 1;
  if (this->previous_gesture == gesture_swipe_xdokey::FRESH)
    scale = 0.01f; // square root of 1/10
  // we are working with floating points which are not exact
  // make sure we compare with a very small value (epsilon)
  static const float EPSILON = 1e-6f;
  const float distance_squared = this->x * this->x + this->y * this->y;
  const float beyond_threshold = this->threshold_squared * scale;
  // if distance goes out of threshold, perform our swipe
  if (distance_squared > beyond_threshold + EPSILON) {
    // we parse our mask based on the values obtained from the regex
    int mask = 0;
    if (this->fingers == 3)
      mask |= gesture_swipe_xdokey::MSK_THREE_FINGERS;
    else if (this->fingers == 4)
      mask |= gesture_swipe_xdokey::MSK_FOUR_FINGERS;
    const float absx = x >= 0 ? x : -x;
    const float absy = y >= 0 ? y : -y;
    if (absx > absy) {
      // gesture is horizontal
      mask |= gesture_swipe_xdokey::MSK_HORIZONTAL;
      if (x < 0)
        mask |= gesture_swipe_xdokey::MSK_NEGATIVE;
      else
        mask |= gesture_swipe_xdokey::MSK_POSITIVE;
    }
    else /* std::abs(x) <= std::abs(y) */
    {
      // gesture is vertical
      mask |= gesture_swipe_xdokey::MSK_VERTICAL;
      if (y < 0)
        mask |= gesture_swipe_xdokey::MSK_NEGATIVE;
      else
        mask |= gesture_swipe_xdokey::MSK_POSITIVE;
    }
    // send command on fresh OR opposite gesture
    if (this->previous_gesture == gesture_swipe_xdokey::FRESH ||
        this->previous_gesture ==
            (mask ^ gesture_swipe_xdokey::MSK_POSITIVE)) {
      // finally, perform keyboard gesture
      this->do_keyboard_gesture(mask);
    }
  }
}
/**
 * Perform our maske command to xdo.
 */
void gesture_swipe_xdokey::do_keyboard_gesture(int mask) {
  // perform our keyboard command with xdo_send_keysequence
  xdo_send_keysequence_window(this->xdo, CURRENTWINDOW, commands[mask].data(), 0);
  std::cout << "SWIPE " << command_name[mask] << std::endl;
  // reset our location variables
  this->x = this->y = 0;
  this->previous_gesture = mask;
}
/**
 * Hook on end of swipe gesture.
 */
void gesture_swipe_xdokey::end() {
  // just call superclass method
  gesture_swipe::end();
}
}
#endif /* __comfortable_swipe_gesture_swipe_xdokey__ */
