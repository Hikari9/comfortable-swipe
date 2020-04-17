#ifndef __COMFORTABLE_SWIPE__service_restart__
#define __COMFORTABLE_SWIPE__service_restart__

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


#include <unistd.h> // popen, pclose
#include <memory> // std::unique_ptr
#include <cstdlib> // std::system
#include "../all_headers.hpp"

namespace comfortable_swipe::service
{
    /**
     * Restarts the comfortable-swipe service.
     */
    void restart()
    {
        // stop, while redirecting stdout to pipe
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(__COMFORTABLE_SWIPE__PROGRAM__ " stop", "r"), pclose);

        // restart service
        comfortable_swipe::service::start();
    }
}

#endif /* __COMFORTABLE_SWIPE__service_restart__ */
