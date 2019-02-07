/* WARNING: pinch gestures are experimental */

#ifndef __COMFORTABLE_SWIPE__gesture_pinch_gesture__
#define __COMFORTABLE_SWIPE__gesture_pinch_gesture__

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
     * Constructs a new pinch gesture, given configurations for certain pinch events.
     */
    pinch_gesture::pinch_gesture
    (
        const float threshold,
        const char* pinch_in3,
        const char* pinch_in4,
        const char* pinch_out3,
        const char* pinch_out4
    ):
        comfortable_swipe::gesture::xdo_gesture(),
        threshold_squared(threshold),
        commands(new const char*[4]{pinch_in3, pinch_in4, pinch_out3, pinch_out4})
    { }

    /**
     * Destructs this pinch gesture.
     */
    pinch_gesture::~pinch_gesture()
    {
        delete[] commands;
    }

    /**
     * Hook on begin of pinch gesture.
     */
    void pinch_gesture::begin()
    {
        this->previous_gesture = swipe_gesture::FRESH;
        this->previous_radius = this->radius;
    }

    /**
     * Hook on update of swipe gesture.
     */
    void swipe_gesture::update()
    {
        float delta_radius = this->radius - this->previous_radius;
        this->previous_radius = this->radius;
        if (this->delta_radius > EPSILON)
        {
            // TODO: pinch out
        }
        else if (this->delta_radius < -EPSILON)
        {
            // TODO: pinch in
        }
    }

    /**
     * Hook on end of swipe gesture.
     */
    void pinch_gesture::end()
    { }

    /* STATICS DEFINITIONS */
    const int pinch_gesture::MSK_THREE_FINGERS = 0;
    const int pinch_gesture::MSK_FOUR_FINGERS = 1;
    const int pinch_gesture::MSK_NEGATIVE = 0;
    const int pinch_gesture::MSK_POSITIVE = 2;
    const int pinch_gesture::FRESH = -1;
    const char * const pinch_gesture::command_map[4] = {
        "pinch_in 3",
        "pinch_in 4",
        "pinch_out 3",
        "pinch_out 4"
    };
}

#endif /* __COMFORTABLE_SWIPE__gesture_pinch_gesture__ */
