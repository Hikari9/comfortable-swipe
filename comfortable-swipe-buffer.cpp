#ifndef __comfortable_swipe_buffer__
#define __comfortable_swipe_buffer__

/*
Comfortable Swipe (as of v1.2.0)
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

#include <cstdio>    // fgets_unlocked, stdin
#include <iostream>  // ios, cout, cin
#include <confuse.h> // cfg_t

#include "comfortable-swipe-config.cpp"
#include "comfortable-swipe-defines.cpp"
#include "comfortable-swipe-gesture-mousehold.cpp"
#include "comfortable-swipe-gesture-swipe.cpp"

/**
 * The main driver program.
 */
int main() {
  using namespace std;
  using namespace comfortable_swipe;

  // unsync with for faster IO
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout.flush();

  // prepare config file

  cfg_ auto config =
      comfortable_swipe::read_config_file(COMFORTABLE_SWIPE_CONFIG);

  // initialize mouse hold gesture handler
  // for now, this supports 3-finger and 4-finger hold
  // Examples:
  //   hold3=move     move mouse on 3 fingers
  //   hold3=button1  hold button 1 on 3 fingers
  //   hold4=button3  hold button 3 (right click) on 3 fingers
  //   hold3=ignore   <do nothing>
  gesture_mousehold mouse_hold(config_get_string("hold3"), config_get_string("hold4"));

  // initialize keyboard swipe gesture handler
  gesture_swipe = keyboard_swipe(
      config_get_float("threshold"),
      config_get_string("left3"),
      config_get_string("left4"),
      config_get_string("right3"),
      config_get_string("right4"),
      config_get_string("up3"),
      config_get_string("up4"),
      config_get_string("down3"),
      config_get_string("down4"),
  );

  // prepare data containers
  array<char, 256> line;

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

#endif
