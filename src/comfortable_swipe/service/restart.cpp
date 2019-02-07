#ifndef __COMFORTABLE_SWIPE__service_restart__
#define __COMFORTABLE_SWIPE__service_restart__

#include "../index.hpp"

namespace comfortable_swipe::service
{
    /**
     * Restarts the comfortable-swipe service.
     */
    void restart()
    {
        comfortable_swipe::service::start();
        comfortable_swipe::service::stop();
    }
}

#endif /* __COMFORTABLE_SWIPE__service_restart__ */
