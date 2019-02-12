/* WARNING: pinch gestures are experimental */

#ifndef __COMFORTABLE_SWIPE__gesture_pinch_gesture_regex__
#define __COMFORTABLE_SWIPE__gesture_pinch_gesture_regex__

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

namespace comfortable_swipe::gesture
{
    /**
     * Regex pattern for the libinput entry for start of pinch.
     * Extracts one match for the number of fingers used during the pionch.
     * 
     * eg. event15  GESTURE_PINCH_BEGIN +34.33s 3
     *                                          ^
     *                                        fingers
     */
    const char* pinch_gesture::GESTURE_BEGIN_REGEX_PATTERN =
        "^"                        // start of string
        "[ -]event\\d+"            // event
        "\\s+GESTURE_PINCH_BEGIN"  // gesture
        "\\s+\\S+"                 // timestamp
        "\\s+(\\d+)"               // fingers
        "\\s*$"                    // end of string
    ;

    /**
     * Regex pattern for the libinput entry for the end of swipe.
     * Extracts one match for the number of fingers used during the swipe.
     * 
     * eg. event15  GESTURE_PINCH_END +35.03s   3
     *                                          ^
     *                                        fingers
     */
    const char* pinch_gesture::GESTURE_END_REGEX_PATTERN =
        "^"                        // start of string
        "[ -]event\\d+"            // event
        "\\s+GESTURE_PINCH_END"    // gesture
        "\\s+\\S+"                 // timestamp
        "\\s+(\\d+)"               // fingers
        "\\s*$"                    // end of string
    ;

    // matches signed decimal numbers (eg. "6.02" "-1.1")
    #define CF_NUMBER_REGEX "-?\\d+(?:\\.\\d+)"

    // matches a space-prefixed signed fraction (eg. "-3.00/ 5.12")
    #define CF_NUMBER_DIVISION "\\s*" CF_NUMBER_REGEX "/\\s*" CF_NUMBER_REGEX

    /**
     * Regex pattern for the libinput entry for during a pinch.
     * Extracts number of fingers used and the speed (normal and accelerated) of the pinch.
     * Extracts radius and rotational velocity of the pinch motion as well.
     * 
     * eg.  event8   GESTURE_PINCH_UPDATE +128.15s  3 -1.64/ 2.08 (-4.43/ 5.62 unaccelerated)  1.40 @ -0.14
     *                                              ^    ^    ^      ^     ^                    ^       ^
     *                                          fingers  dx   dy    udx   udy                 radius  omega
     */
    const char* pinch_gesture::GESTURE_UPDATE_REGEX_PATTERN =
        "^"                                                 // start of string
        "[ -]event\\d+"                                     // event
        "\\s+GESTURE_PINCH_UPDATE"                          // gesture
        "\\s+\\S+"                                          // timestamp
        "\\s+(\\d+)"                                        // fingers
        "\\s+" CF_NUMBER_DIVISION                           // speed (dx/dy)
        "\\s+\\(" CF_NUMBER_DIVISION "\\s+unaccelerated\\)" // unaccelerated speed (udx/udy)
        "\\s+(" CF_NUMBER_REGEX ")"                         // radius
        " @\\s+" CF_NUMBER_REGEX ""                         // angular velocity (omega)
        "\\s*$"                                             // end of string
    ;

    // delete macros
    #undef CF_NUMBER_DIVISION
    #undef CF_NUMBER_EXTRACT
    #undef CF_NUMBER_REGEX
}

#endif /* __COMFORTABLE_SWIPE__gesture_pinch_gesture_regex__ */
