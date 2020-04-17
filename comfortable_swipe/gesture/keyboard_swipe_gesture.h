#ifndef __COMFORTABLE_SWIPE__gesture_keyboard_swipe_gesture_h__
#define __COMFORTABLE_SWIPE__gesture_keyboard_swipe_gesture_h__

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

#ifdef __cplusplus
extern "C" {
#endif

namespace comfortable_swipe::gesture
{
    class keyboard_swipe_gesture : public swipe_gesture
    {
    public:
        // constructor
        keyboard_swipe_gesture(
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

        // destructor
        virtual ~keyboard_swipe_gesture();

        // hooks that we override
        virtual void begin() override;
        virtual void update() override;
        virtual void end() override;

        // override this when keyboard gesture is to be performed
        virtual void do_keyboard_gesture(int mask);

    protected:
        // stores square of threshold so we can compute faster
        float threshold_squared;

        // stores previous gesture so we don't repeat action
        int previous_gesture;

        // stores all command strings for xdo to execute
        const char ** commands;

    public:
        // static enums we will use for gesture matching
        static const int FRESH;
        static const int MSK_THREE_FINGERS;
        static const int MSK_FOUR_FINGERS;
        static const int MSK_NEGATIVE;
        static const int MSK_POSITIVE;
        static const int MSK_HORIZONTAL;
        static const int MSK_VERTICAL;
        static const char * const command_map[8];
    };
}

#ifdef __cplusplus
}
#endif

#endif /* __COMFORTABLE_SWIPE__gesture_keyboard_swipe_gesture_h__ */
