#ifndef __comfortable_swipe_gesture_swipe__
#define __comfortable_swipe_gesture_swipe__
/**
 * File: comfortable-swipe-gesture-swipe.cpp
 *
 * This is the base class of all comfortable swipe gestures.
 *
 * The class `comfortable_swipe::gesture_swipe` handles dispatching
 * of swipe gestures. The method `gesture_swipe::run(const char*)`
 * parses a line from libinput debug-events and dispatches a begin(),
 * update(), or end() function based on a compiled regex pattern.
 *
 * We statically compile our swipe gesture regex patterns here.
 * This is for parsing `libinput debug-events` console output:
 *
 *   GESTURE_SWIPE_BEGIN   - libinput's begin wipe command
 *   GESTURE_SWIPE_UPDATE  - libinput's update swipe command
 *   GESTURE_SWIPE_END     - libinput's end swipe command
 *
 * We dispatch our events based on the regex patterns above, and
 * extract important information, such as number of fingers, in
 * an efficient way with Regular Expressions (regex).
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
#include <iostream> // std::cout, std::endl
#include <regex>    // std::regex, std::regex_match, std::cmatch
#include <string>   // std::stoi, std::stof
extern "C" {
#include <xdo.h> // xdo, xdo_new, xdo_free,
                 // xdo_get_mouse_location
                 // CURRENT_WINDOW
}
namespace comfortable_swipe {
/**
 * Handles swipe gesture input from libinput debug-events.
 * Dispatches keyboard commands on swipe using libxdo.
 */
class gesture_swipe {
public:
  // constructor
  gesture_swipe();
  // destructor
  virtual ~gesture_swipe();
  // fields for xdo
  int fingers;
  // normal values (for touchpad mapping)
  float x, y, dx, dy;
  // unaccelerated values (for screen mapping)
  float ux, uy, udx, udy;
  // hooks that we can override (mark as virtual)
  virtual void begin();
  virtual void update();
  virtual void end();
  virtual bool run(const char *);
  // public check if currently swiping
  virtual bool is_swiping() const { return this->flag_swiping; }

protected:
  // xdo container
  xdo_t *xdo;
  // location of mouse
  int screen_num, ix, iy;
  // optimization flag for checking if GESTURE_SWIPE_BEGIN was dispatched
  bool flag_swiping;

public:
  // defined in: comfortable-swipe-gesture-swipe.regex.cpp
  static const std::regex GESTURE_SWIPE_BEGIN;
  static const std::regex GESTURE_SWIPE_UPDATE;
  static const std::regex GESTURE_SWIPE_END;
};
/**
 * Constructs a new fresh swipe gesture container.
 */
gesture_swipe::gesture_swipe() : xdo(xdo_new(NULL)), flag_swiping(false) {
  // improve responsiveness of first gesture by pre-empting xdotool
  xdo_get_mouse_location(this->xdo, &this->ix, &this->iy, &this->screen_num);
}
/**
 * Destructs this swipe gesture.
 */
gesture_swipe::~gesture_swipe() { xdo_free(this->xdo); }
/**
 * Hook on begin of swipe gesture (you can override this).
 */
void gesture_swipe::begin() {
  // save current screen location for gestured mouse movement
  xdo_get_mouse_location(this->xdo, &this->ix, &this->iy, &this->screen_num);
  this->x = 0;
  this->y = 0;
  this->ux = 0;
  this->uy = 0;
}
/**
 * Hook on update of swipe gesture (you can override this).
 */
void gesture_swipe::update() {
  this->x += this->dx;
  this->y += this->dy;
  this->ux += this->udx;
  this->uy += this->udy;
}
/**
 * Hook on end of swipe gesture (you can override this).
 */
void gesture_swipe::end() {
  // do nothing
}
/**
 * Dispatches begin/update/end depending on the regex pattern provided by this
 * class. Returns true if a gesture begin/update/end was parsed.
 *
 * @param line  the line from libinput debug-events to parse
 * @return true if begin/update/end was dispatched
 */
bool gesture_swipe::run(const char *line) {
  // prepare holder for regex matches
  static std::cmatch matches;
  if (!this->flag_swiping) {
    // not swiping, check if swipe will begin
    if (std::regex_match(line, matches, GESTURE_SWIPE_BEGIN) != 0) {
      // assign necessary variables for swipe begin
      this->flag_swiping = true;
      this->fingers = std::stoi(matches[1]);
      // dispatch begin
      this->begin();
      return true;
    }
  } else {
    // currently swiping
    if (std::regex_match(line, matches, GESTURE_SWIPE_UPDATE) != 0) {
      // assign necessary variables for swipe update
      this->fingers = std::stoi(matches[1]);
      this->dx = std::stof(matches[2]);
      this->dy = std::stof(matches[3]);
      this->udx = std::stof(matches[4]);
      this->udy = std::stof(matches[5]);
      // dispatch update
      this->update();
      return true;
    } else if (std::regex_match(line, matches, GESTURE_SWIPE_END) != 0) {
      // assign necessary variables for swipe end
      this->flag_swiping = false;
      this->fingers = std::stoi(matches[1]);
      // dispatch end
      this->end();
      return true;
    }
  }
  return false;
}
/**
 * Regex pattern for the libinput entry for start of swipe.
 * Extracts one match for the number of fingers used during the swipe.
 *
 * eg. event15  GESTURE_SWIPE_BEGIN +34.33s 3
 *                                          ^
 *                                        fingers
 */
const std::regex
    gesture_swipe::GESTURE_SWIPE_BEGIN("^"             // start of string
                                       "[ -]event\\d+" // event
                                       "\\s+GESTURE_SWIPE_BEGIN" // gesture
                                       "\\s+\\S+"                // timestamp
                                       "\\s+(\\d+)"              // fingers
                                       "\\s*$" // end of string
    );
/**
 * Regex pattern for the libinput entry for the end of swipe.
 * Extracts one match for the number of fingers used during the swipe.
 *
 * eg. event15  GESTURE_SWIPE_END +35.03s   3
 *                                          ^
 *                                        fingers
 */
const std::regex
    gesture_swipe::GESTURE_SWIPE_END("^"                     // start of string
                                     "[ -]event\\d+"         // event
                                     "\\s+GESTURE_SWIPE_END" // gesture
                                     "\\s+\\S+"              // timestamp
                                     "\\s+(\\d+)"            // fingers
                                     "\\s*$"                 // end of string
    );
// matches signed decimal numbers (eg. "6.02" "-1.1")
#define _NUMBER_REGEX "-?\\d+(?:\\.\\d+)"
// matches and extracts a space-prefixed signed fraction (eg. "-3.00/ 5.12")
#define _NUMBER_DIVISION "\\s*(" _NUMBER_REGEX ")/\\s*(" _NUMBER_REGEX ")"
/**
 * Regex pattern for the libinput entry for during a swipe.
 * Extracts number of fingers used and the speed (normal and accelerated) of the
 * swipe.
 *
 * eg. event15  GESTURE_SWIPE_UPDATE  \
 *  +34.70s    3 -0.12/ 4.99 (-0.33/13.50 unaccelerated)
 *        ^    ^    ^      ^     ^
 *    fingers  dx   dy    udx   udy
 */
const std::regex gesture_swipe::GESTURE_SWIPE_UPDATE(
    "^"                        // start of string
    "[ -]event\\d+"            // event
    "\\s+GESTURE_SWIPE_UPDATE" // gesture
    "\\s+\\S+"                 // timestamp
    "\\s+(\\d+)"               // fingers
    "\\s+" _NUMBER_DIVISION    // speed (dx/dy)
    "\\s+\\(" _NUMBER_DIVISION
    "\\s+unaccelerated\\)" // unaccelerated speed (udx/udy)
    "\\s*$"                // end of string
);
// clean up temporary macros
#undef _NUMBER_DIVISION
#undef _NUMBER_REGEX
} // namespace comfortable_swipe
#endif /* __comfortable_swipe_gesture_swipe__ */
