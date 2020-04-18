#ifndef __COMFORTABLE_SWIPE__util_autostart_filename__
#define __COMFORTABLE_SWIPE__util_autostart_filename__

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

#include <string>   // std::string
#include <unistd.h> // getenv

namespace comfortable_swipe::util {
/**
 * The path where the autostart configuration is located.
 */
const char *autostart_filename() {
  static std::string filename;
  if (filename.empty()) {
    const char *xdg_config = getenv("XDG_CONFIG_HOME");
    std::string config(xdg_config == NULL
                           ? std::string(getenv("HOME")) + "/.config"
                           : xdg_config);
    filename = config + "/autostart/comfortable-swipe.desktop";
  }
  return filename.data();
}
} // namespace comfortable_swipe::util

#endif /* __COMFORTABLE_SWIPE__util_autostart_filename__ */
