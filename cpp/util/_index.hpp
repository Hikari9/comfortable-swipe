#ifndef __COMFORTABLE_SWIPE__util_index_hpp__
#define __COMFORTABLE_SWIPE__util_index_hpp__

#include <map> // std::map
#include <string> // std::string

namespace comfortable_swipe
{
    namespace util
    {
        std::map<std::string, std::string> read_config_file(const char*);
    }
}

#endif /* __COMFORTABLE_SWIPE__util_index_hpp__ */
