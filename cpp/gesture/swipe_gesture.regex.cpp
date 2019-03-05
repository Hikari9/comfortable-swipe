#ifndef __COMFORTABLE_SWIPE__gesture_swipe_gesture_regex__
#define __COMFORTABLE_SWIPE__gesture_swipe_gesture_regex__

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

#include "swipe_gesture.h"

namespace comfortable_swipe
{
    namespace gesture
    {
        /**
         * Regex pattern for the libinput entry for start of swipe.
         * Extracts one match for the number of fingers used during the swipe.
         *
         * eg. event15  GESTURE_SWIPE_BEGIN +34.33s 3
         *                                          ^
         *                                        fingers
         */
        const char* swipe_gesture::GESTURE_BEGIN_REGEX_PATTERN =
            "^"                        // start of string
            "[ -]event\\d+"            // event
            "\\s+GESTURE_SWIPE_BEGIN"  // gesture
            "\\s+\\S+"                 // timestamp
            "\\s+(\\d+)"               // fingers
            "\\s*$"                        // end of string
        ;

        /**
         * Regex pattern for the libinput entry for the end of swipe.
         * Extracts one match for the number of fingers used during the swipe.
         *
         * eg. event15  GESTURE_SWIPE_END +35.03s   3
         *                                          ^
         *                                        fingers
         */
        const char* swipe_gesture::GESTURE_END_REGEX_PATTERN =
            "^"                        // start of string
            "[ -]event\\d+"            // event
            "\\s+GESTURE_SWIPE_END"    // gesture
            "\\s+\\S+"                 // timestamp
            "\\s+(\\d+)"               // fingers
            "\\s*$"                        // end of string
        ;

        // matches signed decimal numbers (eg. "6.02" "-1.1")
        #define CF_NUMBER_REGEX "-?\\d+(?:\\.\\d+)"

        // matches and extracts a space-prefixed signed fraction (eg. "-3.00/ 5.12")
        #define CF_NUMBER_DIVISION "\\s*(" CF_NUMBER_REGEX ")/\\s*(" CF_NUMBER_REGEX ")"

        /**
         * Regex pattern for the libinput entry for during a swipe.
         * Extracts number of fingers used and the speed (normal and accelerated) of the swipe.
         *
         * eg. event15  GESTURE_SWIPE_UPDATE +34.70s    3 -0.12/ 4.99 (-0.33/13.50 unaccelerated)
         *                                              ^    ^    ^      ^     ^
         *                                          fingers  dx   dy    udx   udy
         */
        const char* swipe_gesture::GESTURE_UPDATE_REGEX_PATTERN =
            "^"                                                 // start of string
            "[ -]event\\d+"                                     // event
            "\\s+GESTURE_SWIPE_UPDATE"                          // gesture
            "\\s+\\S+"                                          // timestamp
            "\\s+(\\d+)"                                        // fingers
            "\\s+" CF_NUMBER_DIVISION                           // speed (dx/dy)
            "\\s+\\(" CF_NUMBER_DIVISION "\\s+unaccelerated\\)" // unaccelerated speed (udx/udy)
            "\\s*$"                                                 // end of string
        ;

        // delete macros
        #undef CF_NUMBER_DIVISION
        #undef CF_NUMBER_EXTRACT
        #undef CF_NUMBER_REGEX
    }
}

#endif /* __COMFORTABLE_SWIPE__gesture_swipe_gesture_regex__ */
