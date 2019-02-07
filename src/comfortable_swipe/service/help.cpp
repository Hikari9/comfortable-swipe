#ifndef __COMFORTABLE_SWIPE__service_help__
#define __COMFORTABLE_SWIPE__service_help__

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
