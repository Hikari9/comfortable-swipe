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

// Compile: g++ main.cpp -std=c++11 -lxdo 

#include <string> // std::string
#include "lib/comfortable_swipe"

/* MAIN DRIVER FUNCTION */

int main(int argc, char** args)
{
    if (argc > 1)
    {
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

        else /* if (arg == "help") */
            comfortable_swipe::service::help();
    }
    else
        comfortable_swipe::service::help();

    return 0;
}
