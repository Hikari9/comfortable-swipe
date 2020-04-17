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

#include "comfortable_swipe/lib.cpp"
#include <ios>      // std::ios
#include <iostream> // std::cin, std::cout, std::cerr
#include <string>   // std::string

/* Command-line function. */

int main(int argc, char **args) {
  // improve buffering by decoupling loggers from stdio
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  std::cerr.tie(0);

  if (argc > 1) {
    std::string arg = args[1];

    // select based on argument
    if (arg == "start")
      comfortable_swipe::service::start();

    else if (arg == "stop")
      comfortable_swipe::service::stop();

    else if (arg == "restart")
      comfortable_swipe::service::restart();

    else if (arg == "buffer")
      comfortable_swipe::service::buffer();

    else if (arg == "autostart")
      comfortable_swipe::service::autostart();

    else if (arg == "config")
      comfortable_swipe::service::config();

    else if (arg == "debug")
      comfortable_swipe::service::debug();

    else if (arg == "status")
      comfortable_swipe::service::status();

    else /* if (arg == "help") */
      comfortable_swipe::service::help();
  } else
    comfortable_swipe::service::help();

  return 0;
}
