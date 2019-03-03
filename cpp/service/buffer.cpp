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

#include "../_macro.cpp"
#include "../util/_index.hpp"
#include "../gesture/_index.hpp"
#include <cstdio> // fgets_unlocked, stdin
#include <iostream> // std::ios, std::cout, std::cin

/**
 * Starts the comfortable-swipe service by buffering libinput debug-events.
 */
namespace comfortable_swipe::service
{
    void buffer()
    {
        std::ios::sync_with_stdio(false);
        std::cin.tie(0);
        std::cout.tie(0);
        std::cout.flush();

        // read config file
        auto config = comfortable_swipe::util::read_config_file(__COMFORTABLE_SWIPE__CONFIG__);

        // initialize swipe gesture handler
        comfortable_swipe::gesture::swipe_gesture swipe_gesture_handler
        (
            config.count("threshold") ? std::stof(config["threshold"]) : 0.0,
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
        std::array<char, 256> line;

        // start reading lines from input one by one
        while (fgets_unlocked(line.data(), line.size(), stdin) != NULL)
        {
            // attempt to parse swipe gestures
            swipe_gesture_handler.parse_line(line.data());
        }
    }
}

#endif /* __COMFORTABLE_SWIPE__service_buffer__ */
