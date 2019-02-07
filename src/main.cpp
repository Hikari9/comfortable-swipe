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

#include <string> // std::string
#include "comfortable_swipe/index.cpp"

/* MAIN DRIVER FUNCTION */

int main(int argc, char** args)
{
    using namespace comfortable_swipe::service;

    if (argc > 1)
    {
        std::string arg = args[1];
        // select based on argument
        if (arg == "start") start();
        else if (arg == "stop") stop();
        else if (arg == "restart") restart();
        else if (arg == "buffer") buffer();
        else if (arg == "autostart") autostart();
        else help();
    }

    else
        help();

    return 0;
}