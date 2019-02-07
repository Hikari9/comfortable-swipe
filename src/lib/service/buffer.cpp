#ifndef __COMFORTABLE_SWIPE__service_buffer__
#define __COMFORTABLE_SWIPE__service_buffer__

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

#include <string> // std::stoi, std::stof
#include <cstdio> // std::fgets_unlocked, stdin
#include <regex> // std::regex, std::regex_match, std::cmatch
#include "../index.hpp"

/**
 * Starts the comfortable-swipe service by buffering libinput debug-events.
 */
namespace comfortable_swipe::service
{
    void buffer()
    {
        // read config file
        auto config = comfortable_swipe::util::read_config_file(comfortable_swipe::util::conf_filename());

        // pre-compile regex patterns
        static const std::regex gesture_swipe_begin(comfortable_swipe::util::GESTURE_SWIPE_BEGIN_REGEX_PATTERN);
        static const std::regex gesture_swipe_update(comfortable_swipe::util::GESTURE_SWIPE_UPDATE_REGEX_PATTERN);
        static const std::regex gesture_swipe_end(comfortable_swipe::util::GESTURE_SWIPE_END_REGEX_PATTERN);

        // initialize swipe gesture handler
        comfortable_swipe::gesture::swipe_gesture swipe
        (
            config.count("threshold") ? std::atof(config["threshold"].data()) : 0.0,
            config["left3"].c_str(),
            config["left4"].c_str(),
            config["right3"].c_str(),
            config["right4"].c_str(),
            config["up3"].c_str(),
            config["up4"].c_str(),
            config["down3"].c_str(),
            config["down4"].c_str()
        );

        // prepare data containers
        static const int MAX_LINE_LENGTH = 256;
        static char data[MAX_LINE_LENGTH];
        static std::cmatch matches;

        // optimization flag for checking if GESTURE_SWIPE_BEGIN was dispatched
        bool flag_swiping = false;

        // start reading lines from input one by one
        while (fgets_unlocked(data, MAX_LINE_LENGTH, stdin) != NULL)
        {
            if (flag_swiping)
            {
                // currently swiping
                if (std::regex_match(data, matches, gesture_swipe_update) != 0)
                {
                    // update swipe
                    swipe.fingers = std::stoi(matches[1]);
                    swipe.dx = std::stof(matches[2]);
                    swipe.dy = std::stof(matches[3]);
                    swipe.udx = std::stof(matches[4]);
                    swipe.udy = std::stof(matches[5]);
                    swipe.update();
                }
                else if (std::regex_match(data, matches, gesture_swipe_end) != 0)
                {
                    // end swipe
                    flag_swiping = false;
                    swipe.fingers = std::stoi(matches[1]);
                    swipe.end();
                }
            }
            else /* !flag_swiping */
            {
                // not swiping, check if swipe will begin
                if (std::regex_match(data, matches, gesture_swipe_begin) != 0)
                {
                    // begin swipe
                    flag_swiping = true;
                    swipe.fingers = std::stoi(matches[1]);
                    swipe.begin();
                }
            }
            
        }
    }
}

#endif /* __COMFORTABLE_SWIPE__service_buffer__ */
