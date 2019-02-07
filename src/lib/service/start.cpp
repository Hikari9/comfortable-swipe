#ifndef __COMFORTABLE_SWIPE__service_start__
#define __COMFORTABLE_SWIPE__service_start__

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

#include "../index.hpp"
#include <cstdlib> // std::system

namespace comfortable_swipe::service
{
    /**
     * Starts the comfortable-swipe service by buffering libinput debug-events.
     * This method is deferred. Please refer to comfortable_swipe::service::buffer()
     * for the technical implementation.
     */
    void start()
    {
        (void) std::system("stdbuf -oL -e0 libinput debug-events | " __COMFORTABLE_SWIPE__PROGRAM__ " buffer");
    }
}

#endif /* __COMFORTABLE_SWIPE__service_start__ */
