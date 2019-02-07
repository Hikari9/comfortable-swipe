#ifndef __COMFORTABLE_SWIPE__service_start__
#define __COMFORTABLE_SWIPE__service_start__

#include "../index.hpp"
#include <cstdlib> // std::system

namespace comfortable_swipe::service
{
    /**
     * Starts the comfortable-swipe service by buffering libinput debug-events.
     */
    void start()
    {
        std::system("stdbuf -oL -e0 libinput debug-events | " __COMFORTABLE_SWIPE__PROGRAM__ " buffer");
    }
}

#endif /* __COMFORTABLE_SWIPE__service_start__ */
