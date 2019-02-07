#ifndef __COMFORTABLE_SWIPE__gesture_swipe_gesture__
#define __COMFORTABLE_SWIPE__gesture_swipe_gesture__

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

#include <iostream> // std::cout, std::endl
#include "../index.hpp"
#include "xdo_gesture.h"

extern "C"
{
    #include <xdo.h> // xdo, xdo_new, xdo_free,
                     // xdo_get_mouse_location
                     // CURRENT_WINDOW
}

namespace comfortable_swipe::gesture
{
    /**
     * Constructs a new swipe gesture, given configurations for certain swipe events.
     */
    swipe_gesture::swipe_gesture
    (
        const float threshold,
        const char* left3   /* 000 */,
        const char* left4   /* 001 */,
        const char* right3  /* 010 */,
        const char* right4  /* 011 */,
        const char* up3     /* 100 */,
        const char* up4     /* 101 */,
        const char* down3   /* 110 */,
        const char* down4   /* 111 */
    ):
        comfortable_swipe::gesture::xdo_gesture(),
        commands(new const char*[8]{left3, left4, right3, right4, up3, up4, down3, down4})
    { }

    /**
     * Destructs this swipe gesture.
     */
    swipe_gesture::~swipe_gesture()
    {
        delete[] commands;
    }

    /**
     * Hook on begin of swipe gesture.
     */
    void swipe_gesture::begin()
    {
        xdo_get_mouse_location(this->xdo, &this->ix, &this->iy, &this->screen_num);
        this->previous_gesture = swipe_gesture::FRESH;
        this->x = 0;
        this->y = 0;
    }

    /**
     * Hook on update of swipe gesture.
     */
    void swipe_gesture::update()
    {
        this->x += this->dx;
        this->y += this->dy;
        // scale threshold to 1/10 when gesture is not fresh
        float scale = this->previous_gesture == swipe_gesture::FRESH
            ? 1.00f
            : 0.01f; // square root of 1/10
        if (this->x * this->x + this->y * this->y > this->threshold_squared * scale)
        {
            int mask = 0;
            if (this->fingers == 3) mask |= swipe_gesture::MSK_THREE_FINGERS;
            else if (this->fingers == 4) mask |= swipe_gesture::MSK_FOUR_FINGERS;

            const float absx = x >= 0 ? x : -x;
            const float absy = y >= 0 ? y : -y;
            if (absx > absy)
            { // horizontal
                mask |= swipe_gesture::MSK_HORIZONTAL;
                if (x < 0)
                    mask |= swipe_gesture::MSK_NEGATIVE;
                else
                    mask |= swipe_gesture::MSK_POSITIVE;
            }
            else /* std::abs(x) <= std::abs(y) */
            { // vertical
                mask |= swipe_gesture::MSK_VERTICAL;
                if (y < 0)
                    mask |= swipe_gesture::MSK_NEGATIVE;
                else
                    mask |= swipe_gesture::MSK_POSITIVE;
            }

            // send command on fresh OR opposite gesture
            if (this->previous_gesture == swipe_gesture::FRESH
                || this->previous_gesture == (mask ^ swipe_gesture::MSK_POSITIVE))
            {
                this->x = this->y = 0;
                this->previous_gesture = mask;
                std::cout << "SWIPE " << swipe_gesture::command_map[mask] << std::endl;
                xdo_send_keysequence_window(xdo, CURRENTWINDOW, swipe_gesture::commands[mask], 0);
            }
        }
    }

    /**
     * Hook on end of swipe gesture.
     */
    void swipe_gesture::end()
    { }

    /* STATICS DEFINITIONS */
    const int swipe_gesture::MSK_THREE_FINGERS = 0;
    const int swipe_gesture::MSK_FOUR_FINGERS = 1;
    const int swipe_gesture::MSK_NEGATIVE = 0;
    const int swipe_gesture::MSK_POSITIVE = 2;
    const int swipe_gesture::MSK_HORIZONTAL = 0;
    const int swipe_gesture::MSK_VERTICAL = 4;
    const int swipe_gesture::FRESH = -1;
    const char * const swipe_gesture::command_map[8] = {
        "left 3",
        "left 4",
        "right 3",
        "right 4",
        "up 3",
        "up 4",
        "down 3",
        "down 4"
    };
}

#endif /* __COMFORTABLE_SWIPE__gesture_swipe_gesture__ */
