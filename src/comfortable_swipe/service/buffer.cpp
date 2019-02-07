#ifndef __COMFORTABLE_SWIPE__service_buffer__
#define __COMFORTABLE_SWIPE__service_buffer__

#include <string> // std::stoi, std::stof
#include <cstdio> // std::fgets_unlocked, stdin
#include <regex> // std::regex, std::regex_match, std::cmatch
#include "../index.hpp"

/**
 * Starts the comfortable-swipe service by buffering libinput debug-events.
 */
void comfortable_swipe::service::buffer()
{

    // import utility methods
    using comfortable_swipe::util::read_config_file;
    using comfortable_swipe::util::conf_filename;
    using comfortable_swipe::gesture::swipe_gesture;

    // import regex patterns
    using comfortable_swipe::util::GESTURE_SWIPE_BEGIN_REGEX_PATTERN;
    using comfortable_swipe::util::GESTURE_SWIPE_UPDATE_REGEX_PATTERN;
    using comfortable_swipe::util::GESTURE_SWIPE_END_REGEX_PATTERN;

    // pre-compile regex patterns
    static const std::regex gesture_begin(GESTURE_SWIPE_BEGIN_REGEX_PATTERN);
    static const std::regex gesture_update(GESTURE_SWIPE_UPDATE_REGEX_PATTERN);
    static const std::regex gesture_end(GESTURE_SWIPE_END_REGEX_PATTERN);

    // read config file
    auto config = read_config_file(conf_filename());

    // initialize swipegesture handler
    swipe_gesture swipe
    (
        config.count("threshold") ? std::atof(config["threshold"].data()) : 0.0,
        config["left3"].c_str(),
        config["left4"].c_str(),
        config["right3"].c_str(),
        config["right4"].c_str(),
        config["up3"].c_str(),
        config["up4"].c_str(),
        config["down3"].c_str(),
        config["down4"].c_str()
    );

    // prepare data containers
    static const int MAX_LINE_LENGTH = 256;
    static char data[MAX_LINE_LENGTH];
    static std::cmatch matches;

    // optimization flag for checking if GESTURE_SWIPE_BEGIN was dispatched
    bool flag_begin = false;

    // start reading lines from input one by one
    while (fgets_unlocked(data, MAX_LINE_LENGTH, stdin) != NULL)
    {
        if (!flag_begin)
        {
            if (std::regex_match(data, matches, gesture_begin) != 0)
            {
               swipe.fingers = std::stoi(matches[1]);
               swipe.begin();
               flag_begin = true;
            }
        }
        else /* flag_begin == true */
        {
            if (std::regex_match(data, matches, gesture_update) != 0)
            {
               swipe.fingers = std::stoi(matches[1]);
               swipe.dx = std::stof(matches[2]);
               swipe.dy = std::stof(matches[3]);
               swipe.udx = std::stof(matches[4]);
               swipe.udy = std::stof(matches[5]);
               swipe.update();
            }
            else if (std::regex_match(data, matches, gesture_end) != 0)
            {
               swipe.fingers = std::stoi(matches[1]);
               swipe.end();
               flag_begin = false;
            }
        }
    }
}

#endif /* __COMFORTABLE_SWIPE__service_buffer__ */
