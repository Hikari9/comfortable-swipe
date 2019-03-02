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

#include "../util/__index__.hpp"
#include "../gesture/__index__.hpp"
#include <stdexcept> // std::runtime_error
#include <unistd.h> // popen, pclose, getpid, access, F_OK
#include <memory> // std::unique_ptr
#include <array> // std::array
#include <cstdlib> // std::atoi
#include <cstdio> // FILE, std::feof, std::fgets, std::printf
#include <regex> // std::cmatch, std::regex, std::regex_match

namespace comfortable_swipe::service
{
    /**
     * Prints the status of comfortable-swipe.
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
        std::printf("config file at %s\n", comfortable_swipe::util::conf_filename());

        // check status of configuration file
        try
        {
            auto config = comfortable_swipe::util::read_config_file(comfortable_swipe::util::conf_filename());

            // print keys and values of config file
            std::printf("\nConfigurations:\n");

            // print threshold
            if (config.count("threshold") > 0)
            {
                auto & threshold = config["threshold"];

                // check if regex pattern matches threshold
                std::cmatch matches;
                bool ok = (std::regex_match(threshold.data(), matches, std::regex("^\\d+(?:\\.\\d+)??$")) != 0);

                // print status of threshold
                std::printf("    %9s is %s  (%s)\n", "threshold", ok ? "OK" : "INVALID", threshold.data());
            }
            else
                std::printf("    %9s is OFF\n", "threshold");

            // print swipe commands
            for (auto &command : comfortable_swipe::gesture::swipe_gesture::command_map)
            {
                if (config.count(command) > 0)
                    std::printf("    %9s is OK  (%s)\n", command, config[command].data());
                else
                    std::printf("    %9s is OFF\n", command);
            }
        }
        catch (const std::runtime_error& e)
        {
            std::printf("config error: %s\n", e.what());
        }
    }
}

#endif /* __COMFORTABLE_SWIPE__service_restart__ */
