#ifndef __COMFORTABLE_SWIPE__gesture_mouse_hold_gesture_h__
#define __COMFORTABLE_SWIPE__gesture_mouse_hold_gesture_h__

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
    class mouse_hold_gesture : public swipe_gesture
    {
    public:
        // constructor
        mouse_hold_gesture(
            const char* hold3, // 3 finger mouse down
            const char* hold4  // 4 finger mouse down
        );

        // the button being clicked
        int button;

        virtual ~mouse_hold_gesture();

        // override begin and end for mousedown
        virtual void begin() override;
        virtual void update() override;
        virtual void end() override;

        // provide our own mouse functions
        virtual void do_mousedown(const char*);
        virtual void do_mouseup(const char*);
        virtual bool is_mousedown() const;

        // utility method to parse mouse input given config characters
        static int parse_mouse_button(const char*);

    protected:
        // command holders
        const char * hold3;
        const char * hold4;

        // flag we can use to check if mouse is down
        bool flag_mousedown;
    };
}

#ifdef __cplusplus
}
#endif

#endif /* __COMFORTABLE_SWIPE__gesture_mouse_hold_gesture_h__ */
