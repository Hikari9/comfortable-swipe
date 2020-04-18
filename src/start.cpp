#ifndef __COMFORTABLE_SWIPE__start__
#define __COMFORTABLE_SWIPE__start__

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

#include "comfortable_swipe.h"
#include <cstdio>   // fgets_unlocked, stdin
#include <iostream> // std::ios, std::cout, std::cin

/**
 * The main driver program.
 */
namespace comfortable_swipe {
void start() {
  // unsync for faster IO
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  std::cout.flush();

  // read config file
  auto config = comfortable_swipe::util::read_config_file(
      comfortable_swipe::util::conf_filename());

  // initialize mouse hold gesture handler
  // for now, this supports 3-finger and 4-finger hold
  // Examples:
  //   hold3=move     move mouse on 3 fingers
  //   hold3=button1  hold button 1 on 3 fingers
  //   hold4=button3  hold button 3 (right click) on 3 fingers
  //   hold3=ignore   <do nothing>
  const char * const hold3 = config["hold3"].c_str();
  const char * const hold4 = config["hold4"].c_str();
  comfortable_swipe::gesture::mouse_hold_gesture mouse_hold(hold3, hold4);

  // initialize keyboard swipe gesture handler
  const float threshold = config.count("threshold") ? std::stof(config["threshold"]) : 0.0;
  const char * const left3 = config["left3"].c_str();
  const char * const left4 = config["left4"].c_str();
  const char * const right3 = config["right3"].c_str();
  const char * const right4 = config["right4"].c_str();
  const char * const up3 = config["up3"].c_str();
  const char * const up4 = config["up4"].c_str();
  const char * const down3 = config["down3"].c_str();
  const char * const down4 = config["down4"].c_str();
  comfortable_swipe::gesture::keyboard_swipe_gesture keyboard_swipe(
      threshold,
      left3,
      left4,
      right3,
      right4,
      up3,
      up4,
      down3,
      down4
  );

  // prepare data containers
  std::array<char, 256> line;

  // start reading lines from input one by one
  while (fgets_unlocked(line.data(), line.size(), stdin) != NULL) {
    // prioritize mouse hold gesture first
    mouse_hold.parse_line(line.data());
    if (!mouse_hold.is_mousedown()) {
      // if mouse hold fails, try keyboard swipe
      // attempt to parse keyboard gestures with the same line data
      keyboard_swipe.parse_line(line.data());
    }
  }
}
} // namespace comfortable_swipe

#endif /* __COMFORTABLE_SWIPE__start__ */
