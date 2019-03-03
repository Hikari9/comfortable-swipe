#ifndef __COMFORTABLE_SWIPE__util_index_hpp__
#define __COMFORTABLE_SWIPE__util_index_hpp__

#include <map> // std::map
#include <string> // std::string

extern "C"
{
    namespace comfortable_swipe
    {
        namespace util
        {
            const char* autostart_filename();
            constexpr const char* conf_filename();
            std::map<std::string, std::string> read_config_file(const char*);
        }
    }
}

#endif /* __COMFORTABLE_SWIPE__util_index_hpp__ */
