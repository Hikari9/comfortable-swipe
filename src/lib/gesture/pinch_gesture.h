/* WARNING: experimental */

#ifndef __COMFORTABLE_SWIPE__gesture_pinch_gesture_h__
#define __COMFORTABLE_SWIPE__gesture_pinch_gesture_h__

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

#include "xdo_gesture.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace comfortable_swipe::gesture
{
    class pinch_gesture : protected xdo_gesture
    {
    public:
        // constructor
        pinch_gesture(
            const float threshold,
            const char* pinch_in3,
            const char* pinch_in4,
            const char* pinch_out3,
            const char* pinch_out4
        );

        ~pinch_gesture();
        float radius, omega;

        void begin() override;
        void update() override;
        void end() override;
        
    protected:
        // current location
        float previous_radius; 
        float threshold_squared;
        int previous_gesture;
        const char ** commands;

    public:
        // static constants
        static const int MSK_THREE_FINGERS;
        static const int MSK_FOUR_FINGERS;
        static const int MSK_NEGATIVE;
        static const int MSK_POSITIVE;
        static const int FRESH;
        static const char * const command_map[4];
        // regex patterns
        static const char* GESTURE_BEGIN_REGEX_PATTERN;
        static const char* GESTURE_UPDATE_REGEX_PATTERN;
        static const char* GESTURE_END_REGEX_PATTERN;
    };
}

#ifdef __cplusplus
}
#endif

#endif /* __COMFORTABLE_SWIPE__gesture_pinch_gesture_h__ */
