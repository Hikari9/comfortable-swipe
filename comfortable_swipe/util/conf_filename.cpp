#ifndef __COMFORTABLE_SWIPE__util_conf_filename__
#define __COMFORTABLE_SWIPE__util_conf_filename__

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

#include "../all_headers.hpp"

namespace comfortable_swipe::util {
/**
 * The path where the configuration file is located.
 */
constexpr const char *conf_filename() { return __COMFORTABLE_SWIPE__CONFIG__; }
} // namespace comfortable_swipe::util

#endif /* __COMFORTABLE_SWIPE__util_conf_filename__ */
