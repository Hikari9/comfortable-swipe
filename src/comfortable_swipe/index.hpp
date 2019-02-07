#ifndef __COMFORTABLE_SWIPE__index_hpp__
#define __COMFORTABLE_SWIPE__index_hpp__

// global definitions
#ifndef __COMFORTABLE_SWIPE__PROGRAM__
#define __COMFORTABLE_SWIPE__PROGRAM__ "/usr/local/bin/comfortable-swipe"
#endif /* __COMFORTABLE_SWIPE__PROGRAM__ */

#ifndef __COMFORTABLE_SWIPE__CONFIG__
#define __COMFORTABLE_SWIPE__CONFIG__ "/usr/local/share/comfortable-swipe/comfortable-swipe.conf"
#endif /* __COMFORTABLE_SWIPE__CONFIG__ */

#include <map> // std::map
#include <string> // std::string
#include "gesture/swipe_gesture.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

namespace comfortable_swipe
{
    namespace util
    {
        extern const char* GESTURE_SWIPE_BEGIN_REGEX_PATTERN;
        extern const char* GESTURE_SWIPE_UPDATE_REGEX_PATTERN;
        extern const char* GESTURE_SWIPE_END_REGEX_PATTERN;
        std::map<std::string, std::string> read_config_file(const char*);
        const char* autostart_filename();
        constexpr const char* conf_filename();
    }

    namespace service
    {
        void autostart();
        void buffer();
        void help();
        void restart();
        void start();
        void stop();
    }
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __COMFORTABLE_SWIPE__index_hpp__ */