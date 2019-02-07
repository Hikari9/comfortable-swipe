#ifndef __COMFORTABLE_SWIPE__service_help__
#define __COMFORTABLE_SWIPE__service_help__

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

#include <cstdio> // std::puts, std::printf
#include "../index.hpp"

namespace comfortable_swipe::service
{
    /**
     * Shows the help window.
     */
    void help()
    {
        using comfortable_swipe::util::conf_filename;
        std::puts("comfortable-swipe [start|stop|restart|autostart|buffer|help]");
        std::puts("");
        std::puts("start      - starts 3/4-finger gesture service");
        std::puts("stop       - stops 3/4-finger gesture service");
        std::puts("restart    - stops then starts 3/4-finger gesture service");
        std::puts("autostart  - automatically run on startup (toggleable)");
        std::puts("buffer     - parses output of libinput debug-events");
        std::puts("help       - shows the help dialog");
        std::puts("");
        std::printf("Configuration file can be found in %s\n", conf_filename());
    }
}

#endif /* __COMFORTABLE_SWIPE__service_help__ */
