#ifndef __COMFORTABLE_SWIPE__gesture_swipe_gesture_h__
#define __COMFORTABLE_SWIPE__gesture_swipe_gesture_h__

#include <cstdio>
#include <regex>

extern "C"
{
    #include <xdo.h> // xdo_t
}

#ifdef __cplusplus
extern "C" {
#endif

namespace comfortable_swipe
{
    namespace gesture
    {
        struct swipe_gesture
        {
            // constructor
            swipe_gesture(
                const float,
                const char*,
                const char*,
                const char*,
                const char*,
                const char*,
                const char*,
                const char*,
                const char*
            );

            ~swipe_gesture();

            // fields
            int fingers;
            float dx, dy, udx, udy;
            xdo_t * xdo;
            
            // location of mouse
            int screen_num, ix, iy;

            // current location
            float x, y, threshold_squared;
            int previous_gesture;
            const char ** commands;

            // methods
            void update();
            void begin();
            void end();

            // statics
            static const int MSK_THREE_FINGERS;
            static const int MSK_FOUR_FINGERS;
            static const int MSK_NEGATIVE;
            static const int MSK_POSITIVE;
            static const int MSK_HORIZONTAL;
            static const int MSK_VERTICAL;
            static const int FRESH;
            static const char * const command_map[8];
        };
    }
}

#ifdef __cplusplus
}
#endif

#endif /* __COMFORTABLE_SWIPE__gesture_swipe_gesture_h__ */