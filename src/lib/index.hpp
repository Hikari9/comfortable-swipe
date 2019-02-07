#ifndef __COMFORTABLE_SWIPE__index_hpp__
#define __COMFORTABLE_SWIPE__index_hpp__

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
#ifndef __COMFORTABLE_SWIPE__PROGRAM__
#define __COMFORTABLE_SWIPE__PROGRAM__ "/usr/local/bin/comfortable-swipe"
#endif /* __COMFORTABLE_SWIPE__PROGRAM__ */

#ifndef __COMFORTABLE_SWIPE__CONFIG__
#define __COMFORTABLE_SWIPE__CONFIG__ "/usr/local/share/comfortable-swipe/comfortable-swipe.conf"
#endif /* __COMFORTABLE_SWIPE__CONFIG__ */

#include <map> // std::map
#include <string> // std::string

/**
 * Make sure to include your header files here so that they can be imported by other modules.
 */
#include "gesture/xdo_gesture.h"
#include "gesture/swipe_gesture.h"
extern "C"
{
    namespace comfortable_swipe
    {
        namespace util
        {
            extern const char* GESTURE_SWIPE_BEGIN_REGEX_PATTERN;
            extern const char* GESTURE_SWIPE_UPDATE_REGEX_PATTERN;
            extern const char* GESTURE_SWIPE_END_REGEX_PATTERN;
            const char* autostart_filename();
            constexpr const char* conf_filename();
            std::map<std::string, std::string> read_config_file(const char*);
        }
        namespace service
        {
            void autostart();
            void buffer();
            void help();
            void restart();
            void start();
            void stop();
        }
    }
}

#endif /* __COMFORTABLE_SWIPE__index_hpp__ */
