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

#ifdef __cplusplus
extern "C" {
#endif

namespace comfortable_swipe::gesture
{
    class swipe_gesture : public xdo_gesture
    {
    public:
        // constructor
        swipe_gesture();

        // destructor
        ~swipe_gesture();

        // fields for xdo
        int fingers;
        float x, y, dx, dy, udx, udy;

        // hooks that we can override (mark as virtual)
        virtual void begin();
        virtual void update();
        virtual void end();
        virtual bool parse_line(const char *);

    protected:
        // location of mouse
        int screen_num, ix, iy;

        // optimization flag for checking if GESTURE_SWIPE_BEGIN was dispatched
        bool flag_swiping;

    public:
        // regex patterns
        static const char* GESTURE_BEGIN_REGEX_PATTERN;
        static const char* GESTURE_UPDATE_REGEX_PATTERN;
        static const char* GESTURE_END_REGEX_PATTERN;
    };
}

#ifdef __cplusplus
}
#endif

#endif /* __COMFORTABLE_SWIPE__gesture_swipe_gesture_h__ */
