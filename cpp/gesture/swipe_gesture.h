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

#include "xdo_gesture.h"

namespace comfortable_swipe
{
    namespace gesture
    {
        class swipe_gesture : protected xdo_gesture
        {
        public:
            // constructor
            swipe_gesture(
                const float threshold,
                const char* left3   /* 000 */,
                const char* left4   /* 001 */,
                const char* right3  /* 010 */,
                const char* right4  /* 011 */,
                const char* up3     /* 100 */,
                const char* up4     /* 101 */,
                const char* down3   /* 110 */,
                const char* down4   /* 111 */
            );

            ~swipe_gesture();

            // fields for xdo
            int fingers;
            float dx, dy, udx, udy;

            void begin() override;
            void update() override;
            void end() override;
            bool parse_line(const char *) override;

        protected:
            // location of mouse
            int screen_num, ix, iy;

            // current location
            float x, y, threshold_squared;
            int previous_gesture;
            const char ** commands;

            // optimization flag for checking if GESTURE_SWIPE_BEGIN was dispatched
            bool flag_swiping;

        public:
            // static constants
            static const int MSK_THREE_FINGERS;
            static const int MSK_FOUR_FINGERS;
            static const int MSK_NEGATIVE;
            static const int MSK_POSITIVE;
            static const int MSK_HORIZONTAL;
            static const int MSK_VERTICAL;
            static const int FRESH;
            static const char * const command_map[8];
            // regex patterns
            static const char* GESTURE_BEGIN_REGEX_PATTERN;
            static const char* GESTURE_UPDATE_REGEX_PATTERN;
            static const char* GESTURE_END_REGEX_PATTERN;
        };
    }
}

#endif /* __COMFORTABLE_SWIPE__gesture_swipe_gesture_h__ */
