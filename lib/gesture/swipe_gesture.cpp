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
#include <string> // std::stoi, std::stof
#include <regex> // std::regex, std::regex_match, std::cmatch
#include "swipe_gesture.h"

extern "C"
{
    #include <xdo.h> // xdo, xdo_new, xdo_free,
                     // xdo_get_mouse_location
                     // CURRENT_WINDOW
}

namespace comfortable_swipe::gesture
{
    /**
     * Constructs a new fresh swipe gesture container.
     */
    swipe_gesture::swipe_gesture
    ():
        // construct our superclass
        comfortable_swipe::gesture::xdo_gesture(),
        flag_swiping(false)
    {
        // improve responsiveness of first gesture by pre-empting xdotool
        xdo_get_mouse_location(this->xdo, &this->ix, &this->iy,
            &this->screen_num);
    }

    /**
     * Destructs this swipe gesture.
     */
    swipe_gesture::~swipe_gesture()
    { }

    /**
     * Hook on begin of swipe gesture (you can override this).
     */
    void swipe_gesture::begin()
    {
        xdo_get_mouse_location(this->xdo, &this->ix, &this->iy,
            &this->screen_num);
        this->x = 0;
        this->y = 0;
    }

    /**
     * Hook on update of swipe gesture (you can override this).
     */
    void swipe_gesture::update()
    {
        this->x += this->dx;
        this->y += this->dy;
    }

    /**
     * Hook on end of swipe gesture (you can override this).
     */
    void swipe_gesture::end()
    { }

    /**
     * Dispatches begin/update/end depending on the regex pattern provided by this class.
     *
     * @param line  the line from libinput debug-events to parse
     * @return true if begin/update/end was dispatched
     */
    bool swipe_gesture::parse_line(const char * line)
    {

        // prepare regex matchers statically (will only load at most once)
        static const std::regex
            gesture_swipe_begin(swipe_gesture::GESTURE_BEGIN_REGEX_PATTERN),
            gesture_swipe_update(swipe_gesture::GESTURE_UPDATE_REGEX_PATTERN),
            gesture_swipe_end(swipe_gesture::GESTURE_END_REGEX_PATTERN);

        // prepare holder for regex matches
        static std::cmatch matches;

        if (this->flag_swiping)
        {
            // currently swiping
            if (std::regex_match(line, matches, gesture_swipe_update) != 0)
            {
                // assign necessary variables for swipe update
                this->fingers = std::stoi(matches[1]);
                this->dx = std::stof(matches[2]);
                this->dy = std::stof(matches[3]);
                this->udx = std::stof(matches[4]);
                this->udy = std::stof(matches[5]);
                // dispatch update
                this->update();
                return true;
            }
            else if (std::regex_match(line, matches, gesture_swipe_end) != 0)
            {
                // assign necessary variables for swipe end
                this->flag_swiping = false;
                this->fingers = std::stoi(matches[1]);
                // dispatch end
                this->end();
                return true;
            }
        }
        else
        {
            // not swiping, check if swipe will begin
            if (std::regex_match(line, matches, gesture_swipe_begin) != 0
                || std::regex_match(line, matches, gesture_swipe_update) != 0)
            {
                // assign necessary variables for swipe begin
                this->flag_swiping = true;
                this->fingers = std::stoi(matches[1]);
                // dispatch begin
                this->begin();
                return true;
            }
        }

        return false;
    }
}

#endif /* __COMFORTABLE_SWIPE__gesture_swipe_gesture__ */
