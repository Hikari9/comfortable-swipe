/**
 * Add header files will be imported here.
 * You can import this as a shorthand:
 *
 *    #include "comfortable_swipe.h"
 */

#ifndef __COMFORTABLE_SWIPE__comfortable_swipe_h__
#define __COMFORTABLE_SWIPE__comfortable_swipe_h__

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

// global defines
#ifndef COMFORTABLE_SWIPE_PROGRAM
#define COMFORTABLE_SWIPE_PROGRAM "/usr/local/bin/comfortable-swipe"
#endif /* COMFORTABLE_SWIPE_PROGRAM */

#ifndef COMFORTABLE_SWIPE_CONFIG
#define COMFORTABLE_SWIPE_CONFIG                                               \
  "/usr/local/share/comfortable-swipe/comfortable-swipe.conf"
#endif /* COMFORTABLE_SWIPE_CONFIG */

#ifndef COMFORTABLE_SWIPE_VERSION
#warning COMFORTABLE_SWIPE_VERSION is not defined
#define COMFORTABLE_SWIPE_VERSION "v(UNKNOWN)"
#endif /* COMFORTABLE_SWIPE_VERSION */

#include <map>    // std::map
#include <string> // std::string

extern "C" {
namespace comfortable_swipe {
// this is found in the util/ folder
namespace util {
const char *autostart_filename();
constexpr const char *conf_filename();
std::map<std::string, std::string> read_config_file(const char *);
} // namespace util
// this is found in the service/ folder
namespace service {
void autostart();
void buffer();
void config();
void debug();
void help();
void restart();
void start();
void status();
void stop();
} // namespace service
} // namespace comfortable_swipe
}

// add headers for classes here so it can be imported during include
#include "gesture/keyboard_swipe_gesture.h"
#include "gesture/mouse_hold_gesture.h"
#include "gesture/swipe_gesture.h"
#include "gesture/xdo_gesture.h"
#include "start.h"

#endif /* __COMFORTABLE_SWIPE__comfortable_swipe_h__ */
