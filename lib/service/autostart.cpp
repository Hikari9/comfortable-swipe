#ifndef __COMFORTABLE_SWIPE__service_autostart__
#define __COMFORTABLE_SWIPE__service_autostart__

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

#include <iostream> // std::cerr, std::cout, std::endl
#include <fstream> // std::ifstream, std::ofstream
#include <string> // std::string
#include <cstdio> // std::remove
#include <cstdlib> // std::system
#include "../index.hpp"

namespace comfortable_swipe::service
{
    /**
     * Toggles automatic startup of comfortable swipe.
     */
    void autostart()
    {
        using comfortable_swipe::util::autostart_filename;

        const std::string& path = autostart_filename();
        if (std::ifstream(path.data()).good())
        {
            // file found, delete it
            if (std::remove(path.data()) != 0)
                std::cerr << "Error: failed to switch off autostart. "
                    << "Maybe the autostart file is in use?"
                    << std::endl;
            else
                std::cout << "Autostart switched off" << std::endl;
        } 
        else {
            // file not found, create it
            int result = std::system(("mkdir -p $(dirname " + path + ")").data());
            std::ofstream fout(path.data());
            if (result != 0 || !fout.good())
                std::cerr << "Error: failed to switch on autostart. "
                    << "Are you sure you have the permissions?"
                    << std::endl;
            else {
                fout <<
                    "[Desktop Entry]\n"
                    "Type=Application\n"
                    "Exec=bash -c \""
                        __COMFORTABLE_SWIPE__PROGRAM__
                        " start\"\n"
                    "Hidden=false\n"
                    "NoDisplay=false\n"
                    "X-GNOME-Autostart-enabled=true\n"
                    "Name=Comfortable Swipe\n"
                    "Comment=3 or 4 touchpad gestures\n";
                std::cout << "Autostart switched on" << std::endl;
            }
        }
    }
}

#endif /* __COMFORTABLE_SWIPE__service_autostart__ */
