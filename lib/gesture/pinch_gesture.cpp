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
#include <regex> // std::regex, std::cmatch, std::regex_match
#include "xdo_gesture.h"
#include "pinch_gesture.h"

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
        threshold(threshold),
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
    inline void pinch_gesture::begin()
    {
        this->previous_gesture = pinch_gesture::FRESH;
        this->previous_radius = this->radius;
    }

    /**
     * Hook on update of swipe gesture.
     */
    inline void pinch_gesture::update()
    {
        float delta_radius = this->radius - this->previous_radius;
        this->previous_radius = this->radius;

        // TODO: use a different epsilon threshold
        const float EPSILON = this->threshold;
        if (delta_radius > EPSILON)
        {
            if (this->previous_gesture != 0)
            {
                // TODO
                std::cout << "PINCH OUT" << std::endl;
                this->previous_gesture = 0;
            }
        }
        else if (delta_radius < -EPSILON)
        {
            if (this->previous_gesture != 1)
            {
                // TODO
                std::cout << "PINCH IN" << std::endl;
                this->previous_gesture = 1;
            }
        }
    }

    /**
     * Hook on end of swipe gesture.
     */
    inline void pinch_gesture::end()
    { }

    /**
     * Parses an output line and dispatches pinch begin/update/end upon match.
     * Uses GESTURE_BEGIN_REGEX_PATTERN for begin,
     *      GESTURE_UPDATE_REGEX_PATTERN for update,
     *      GESTURE_END_REGEX_PATTERN for end.
     *
     * @param  line the output line from libinput debug-events
     * @return      true if line matches this gesture
     */
    inline bool pinch_gesture::parse_line(const char * line)
    {
        // pre-compile regex patterns
        static const std::regex gesture_swipe_begin(pinch_gesture::GESTURE_BEGIN_REGEX_PATTERN);
        static const std::regex gesture_swipe_update(pinch_gesture::GESTURE_UPDATE_REGEX_PATTERN);
        static const std::regex gesture_swipe_end(pinch_gesture::GESTURE_END_REGEX_PATTERN);
        std::cmatch matches;
        if (this->flag_pinching)
        {
            // currently pinching
            if (std::regex_match(line, matches, gesture_swipe_update) != 0)
            {
                // update pinch
                this->fingers = std::stoi(matches[1]);
                this->radius = std::stof(matches[2]);
                this->update();
                return true;
            }
            else if (std::regex_match(line, matches, gesture_swipe_end) != 0)
            {
                // end pinch
                this->flag_pinching = false;
                this->fingers = std::stoi(matches[1]);
                this->end();
                return true;
            }
        }
        else /* if (!this->flag_pinching) */
        {
            // not swiping, check if swipe will begin
            if (std::regex_match(line, matches, gesture_swipe_begin) != 0)
            {
                // begin swipe
                this->flag_pinching = true;
                this->fingers = std::stoi(matches[1]);
                this->begin();
                return true;
            }
        }
        return false;
    }

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
