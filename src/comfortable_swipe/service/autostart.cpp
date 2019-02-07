#ifndef __COMFORTABLE_SWIPE__service_autostart__
#define __COMFORTABLE_SWIPE__service_autostart__

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
