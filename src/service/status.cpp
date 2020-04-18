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

#include "../comfortable_swipe.h"
#include <array>     // std::array
#include <cstdio>    // FILE, std::feof, std::fgets, std::printf
#include <cstdlib>   // std::atoi
#include <memory>    // std::unique_ptr
#include <regex>     // std::cmatch, std::regex, std::regex_match
#include <stdexcept> // std::runtime_error
#include <unistd.h>  // popen, pclose, getpid, access, F_OK

namespace comfortable_swipe::service {
/**
 * Prints the status of comfortable-swipe.
 */
void status() {
  // check if comfortable-swipe is running
  bool running = false;
  std::array<char, 128> buffer;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(
      popen("pgrep -f comfortable-swipe", "r"), pclose);
  if (pipe && !std::feof(pipe.get()) &&
      std::fgets(buffer.data(), buffer.size(), pipe.get()) != NULL) {
    int pid = std::atoi(buffer.data());
    if (pid != getpid())
      running = true;
  }

  // check if autostart is on
  auto autostart_f = comfortable_swipe::util::autostart_filename();
  bool autostart_on = access(autostart_f, F_OK) != -1;

  std::puts(comfortable_swipe::util::conf_filename());

  // check status of configuration file
  try {
    auto config = comfortable_swipe::util::read_config_file(
        comfortable_swipe::util::conf_filename());

    // formatting
    const char *FORMAT_NO_ARGS = "    %9s is %9s\n";
    const char *FORMAT_ARGS = "    %9s is %9s (%s)\n";

    // print threshold
    if (config.count("threshold") > 0) {
      auto &threshold = config["threshold"];

      // check if regex pattern matches threshold
      std::cmatch matches;
      bool ok = (std::regex_match(threshold.data(), matches,
                                  std::regex("^\\d+(?:\\.\\d+)??$")) != 0);

      // print status of threshold
      std::printf(FORMAT_ARGS, "threshold", ok ? "VALID" : "INVALID",
                  threshold.data());
    } else
      std::printf(FORMAT_NO_ARGS, "threshold", "NOTSET");

    // print mouse hold commands
    const char *mouse_hold_commands[] = {"hold3", "hold4"};
    bool has_mouse_hold[] = {false, false};
    int index = 0;
    for (const auto *command : mouse_hold_commands) {
      if (config.count(command) > 0) {
        // check if command is valid
        const auto &input = config[command];
        int button =
            comfortable_swipe::gesture::mouse_hold_gesture::parse_mouse_button(
                input.c_str());
        if (button != comfortable_swipe::gesture::MOUSE_NONE) {
          std::printf(FORMAT_ARGS, command, "VALID", input.c_str());
          has_mouse_hold[index] = button;
        } else {
          std::printf(FORMAT_ARGS, command, "INVALID", input.c_str());
        }
      } else
        std::printf(FORMAT_NO_ARGS, command, "NOTSET");
      index += 1;
    }

    // print swipe commands
    for (auto &command :
         comfortable_swipe::gesture::keyboard_swipe_gesture::command_map) {
      if (config.count(command) > 0) {
        int fingers = int(command[strlen(command) - 1] - '0');
        if (has_mouse_hold[fingers - 3]) {
          // command is disabled because mouse hold exists
          std::printf(FORMAT_ARGS, command, "DISABLED", config[command].data());
        } else {
          // check if it's disabled by checking button
          std::printf(FORMAT_ARGS, command, "VALID", config[command].data());
        }
      } else
        std::printf(FORMAT_NO_ARGS, command, "NOTSET");
    }

  } catch (const std::runtime_error &e) {
    std::printf("config error: %s\n", e.what());
  }

  // print status
  std::printf("\nautostart is %s\n", autostart_on ? "ON" : "OFF");
  std::printf("comfortable-swipe program is %s\n",
              running ? "RUNNING" : "STOPPED");
}
} // namespace comfortable_swipe::service

#endif /* __COMFORTABLE_SWIPE__service_restart__ */
