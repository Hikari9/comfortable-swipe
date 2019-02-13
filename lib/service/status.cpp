#ifndef __COMFORTABLE_SWIPE__service_status__
#define __COMFORTABLE_SWIPE__service_status__

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
#include <stdexcept> // std::runtime_error
#include <unistd.h> // popen, pclose, getpid, access, F_OK
#include <memory> // std::unique_ptr
#include <array> // std::array
#include <cstdlib> // std::atoi
#include <cstdio> // FILE, std::feof, std::fgets, std::printf

namespace comfortable_swipe::service
{
    /**
     * Restarts the comfortable-swipe service.
     */
    void status()
    {
        // check if comfortable-swipe is running
        bool running = false;
        std::array<char, 128> buffer;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("pgrep -f comfortable-swipe", "r"), pclose);
        if (pipe && !std::feof(pipe.get()) && std::fgets(buffer.data(), buffer.size(), pipe.get()) != NULL)
        {
            int pid = std::atoi(buffer.data());
            if (pid != getpid())
                running = true;
        }

        // check if autostart is on
        auto autostart_f = comfortable_swipe::util::autostart_filename();
        bool autostart_on = access(autostart_f, F_OK) != -1;

        // print status
        std::printf("program is %s\n", running ? "ON" : "OFF");
        std::printf("autostart is %s\n", autostart_on ? "ON" : "OFF");
    }
}

#endif /* __COMFORTABLE_SWIPE__service_restart__ */
