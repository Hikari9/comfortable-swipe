#ifndef __COMFORTABLE_SWIPE__util_conf_filename__
#define __COMFORTABLE_SWIPE__util_conf_filename__

#include "../index.hpp"

namespace comfortable_swipe::util
{
    /**
     * The path where the configuration file is located.
     */
    constexpr const char* conf_filename()
    {
        return __COMFORTABLE_SWIPE__CONFIG__;
    }
}

#endif /* __COMFORTABLE_SWIPE__util_conf_filename__ */
