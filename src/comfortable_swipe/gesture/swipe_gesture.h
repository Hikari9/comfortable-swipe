#ifndef __COMFORTABLE_SWIPE__gesture_swipe_gesture_h__
#define __COMFORTABLE_SWIPE__gesture_swipe_gesture_h__

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

extern "C"
{
    #include <xdo.h> // xdo_t
}

#ifdef __cplusplus
extern "C" {
#endif

namespace comfortable_swipe
{
    namespace gesture
    {
        struct swipe_gesture
        {
            // constructor
            swipe_gesture(
                const float,
                const char*,
                const char*,
                const char*,
                const char*,
                const char*,
                const char*,
                const char*,
                const char*
            );

            ~swipe_gesture();

            // fields for xdo
            int fingers;
            float dx, dy, udx, udy;
            xdo_t * xdo;
            
            // location of mouse
            int screen_num, ix, iy;

            // current location
            float x, y, threshold_squared;
            int previous_gesture;
            const char ** commands;

            // hooks
            void update();
            void begin();
            void end();

            // statics
            static const int MSK_THREE_FINGERS;
            static const int MSK_FOUR_FINGERS;
            static const int MSK_NEGATIVE;
            static const int MSK_POSITIVE;
            static const int MSK_HORIZONTAL;
            static const int MSK_VERTICAL;
            static const int FRESH;
            static const char * const command_map[8];
        };
    }
}

#ifdef __cplusplus
}
#endif

#endif /* __COMFORTABLE_SWIPE__gesture_swipe_gesture_h__ */
