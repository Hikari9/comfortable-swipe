#ifndef __comfortable_swipe_gesture_swipe__
#define __comfortable_swipe_gesture_swipe__

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

namespace comfortable_swipe {
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
  virtual bool parse_line(const char *);

protected:
  // xdo container
  xdo_t *xdo;

  // location of mouse
  int screen_num, ix, iy;

  // optimization flag for checking if GESTURE_SWIPE_BEGIN was dispatched
  bool flag_swiping;

public:
  // regex patterns
  static const std::regex *GESTURE_BEGIN_REGEX;
  static const std::regex *GESTURE_UPDATE_REGEX;
  static const std::regex *GESTURE_END_REGEX;
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
void gesture_swipe::end() {}

/**
 * Dispatches begin/update/end depending on the regex pattern provided by this
 * class.
 *
 * @param line  the line from libinput debug-events to parse
 * @return true if begin/update/end was dispatched
 */
bool gesture_swipe::parse_line(const char *line) {

  // prepare holder for regex matches
  static std::cmatch matches;

  if (this->flag_swiping) {
    // currently swiping
    if (std::regex_match(line, matches, GESTURE_UPDATE_REGEX) != 0) {
      // assign necessary variables for swipe update
      this->fingers = std::stoi(matches[1]);
      this->dx = std::stof(matches[2]);
      this->dy = std::stof(matches[3]);
      this->udx = std::stof(matches[4]);
      this->udy = std::stof(matches[5]);
      // dispatch update
      this->update();
      return true;
    } else if (std::regex_match(line, matches, GESTURE_END_REGEX) != 0) {
      // assign necessary variables for swipe end
      this->flag_swiping = false;
      this->fingers = std::stoi(matches[1]);
      // dispatch end
      this->end();
      return true;
    }
  } else {
    // not swiping, check if swipe will begin
    if (std::regex_match(line, matches, GESTURE_BEGIN_REGEX) != 0 ||
        std::regex_match(line, matches, GESTURE_UPDATE_REGEX) != 0) {
      // assign necessary variables for swipe begin
      this->flag_swiping = true;
      this->fingers = std::stoi(matches[1]);
      // dispatch begin
      this->begin();
      return true;
    }
  }

  return false;
}
} // namespace comfortable_swipe

#endif /* __comfortable_swipe_gesture_swipe__ */
