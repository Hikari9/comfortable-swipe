#ifndef __COMFORTABLE_SWIPE__driver__
#define __COMFORTABLE_SWIPE__driver__

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

#include "all_headers.hpp"
#include <cstdio>   // fgets_unlocked, stdin
#include <iostream> // std::ios, std::cout, std::cin

/**
 * The main driver program.
 */
namespace comfortable_swipe {
int driver() {
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
  comfortable_swipe::gesture::mouse_hold_gesture mouse_hold(
      config["hold3"].c_str(), config["hold4"].c_str());

  // initialize keyboard swipe gesture handler
  comfortable_swipe::gesture::keyboard_swipe_gesture keyboard_swipe(
      config.count("threshold") ? std::stof(config["threshold"]) : 0.0,
      config["left3"].c_str(), config["left4"].c_str(),
      config["right3"].c_str(), config["right4"].c_str(), config["up3"].c_str(),
      config["up4"].c_str(), config["down3"].c_str(), config["down4"].c_str());

  // prepare data containers
  std::array<char, 256> line;

  // start reading lines from input one by one
  while (fgets_unlocked(line.data(), line.size(), stdin) != NULL) {
    // prioritize mouse hold gesture first
    mouse_hold.parse_line(line.data());

    // if mouse hold fails, try keyboard hold
    if (!mouse_hold.is_mousedown()) {
      // attempt to parse keyboard gestures
      keyboard_swipe.parse_line(line.data());
    }
  }

  return 0;
}
} // namespace comfortable_swipe

#endif /* __COMFORTABLE_SWIPE__driver__ */
