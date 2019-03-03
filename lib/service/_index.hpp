#ifndef __COMFORTABLE_SWIPE__service_index_hpp__
#define __COMFORTABLE_SWIPE__service_index_hpp__

#include <map> // std::map
#include <string> // std::string

extern "C"
{
    namespace comfortable_swipe
    {
        namespace service
        {
            void autostart();
            void buffer();
            void config();
            void debug();
            void help();
            void restart();
            void start();
            void stop();
            void status();
        }
    }
}

#endif /* __COMFORTABLE_SWIPE__service_index_hpp__ */
