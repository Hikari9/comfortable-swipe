#include <iostream>
#include <cassert>
#include <regex>
#include "../src/comfortable-swipe.hpp"

namespace test {
    void gesture_begin_should_match_regex();
    void gesture_update_should_match_regex();
    void gesture_end_should_match_regex();
}

int main() {
    std::cout << "(1) Testing gesture_begin_should_match_regex()" << std::endl;
    test::gesture_begin_should_match_regex();

    std::cout << "(2) Testing gesture_begin_should_match_regex()" << std::endl;
    test::gesture_update_should_match_regex();

    std::cout << "(3) Testing gesture_begin_should_match_regex()" << std::endl;
    test::gesture_end_should_match_regex();
    std::cout << "ALL TEST PASSED" << std::endl;
}

namespace test {
    void gesture_begin_test(const char* data, const char* expected_fingers) {
        std::cout << "    testing against \"" << data << "\"...";
        std::cmatch matches;
        auto result = std::regex_match(data, matches, service::gesture_begin);
        assert(result != 0);
        assert((string) matches[1] == expected_fingers);
        std::cout << "PASSED" << std::endl;
    }
    void gesture_begin_should_match_regex() {
        test::gesture_begin_test(" event15  GESTURE_SWIPE_BEGIN +34.33s 3\n", "3");
        test::gesture_begin_test("-event4  GESTURE_SWIPE_BEGIN +3.12s 4\n", "4");
        test::gesture_begin_test("-event7  GESTURE_SWIPE_BEGIN +4.72s 3\n", "3");
        test::gesture_begin_test(" event9  GESTURE_SWIPE_BEGIN +45.80s 4\n", "4");
    }
    void gesture_update_should_match_regex() {
        const char* data = " event15  GESTURE_SWIPE_UPDATE +34.70s    3 -0.12/ 4.99 (-0.33/13.50 unaccelerated)\n";
        std::cmatch matches;
        auto result = std::regex_match(data, matches, service::gesture_update);
        assert(result != 0);
        assert((string) matches[1] == "3");
        assert((string) matches[2] == "-0.12");
        assert((string) matches[3] == "4.99");
        assert((string) matches[4] == "-0.33");
        assert((string) matches[5] == "13.50");
    }
    void gesture_end_should_match_regex() {
        const char* data = " event15  GESTURE_SWIPE_END +35.03s   3\n";
        std::cmatch matches;
        auto result = std::regex_match(data, matches, service::gesture_end);
        assert(result != 0);
        assert((string) matches[1] == "3");
    }
}