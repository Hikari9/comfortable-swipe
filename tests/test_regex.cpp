#include "../comfortable_swipe/gesture/swipe_gesture.h"
#include "../comfortable_swipe/gesture/swipe_gesture.regex.cpp"
#include <cassert>
#include <iostream>
#include <regex>
#include <string>

/*
Comfortable Swipe
by Rico Tiongson

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

namespace test {
void gesture_begin_should_match_regex();
void gesture_update_should_match_regex();
void gesture_end_should_match_regex();
} // namespace test

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
void gesture_begin_test(const std::regex &matcher, const char *data,
                        const char *expected_fingers) {
  std::cout << "    testing against \"" << data << "\"...";
  std::cmatch matches;
  int result = std::regex_match(data, matches, matcher);
  assert(result != 0);
  assert((std::string)matches[1] == expected_fingers);
  std::cout << "PASSED" << std::endl;
}

void gesture_begin_should_match_regex() {
  std::regex matcher(
      comfortable_swipe::gesture::swipe_gesture::GESTURE_BEGIN_REGEX_PATTERN);
  test::gesture_begin_test(matcher, " event15  GESTURE_SWIPE_BEGIN +34.33s 3\n",
                           "3");
  test::gesture_begin_test(matcher, "-event4  GESTURE_SWIPE_BEGIN +3.12s 4\n",
                           "4");
  test::gesture_begin_test(matcher, "-event7  GESTURE_SWIPE_BEGIN +4.72s 3\n",
                           "3");
  test::gesture_begin_test(matcher, " event9  GESTURE_SWIPE_BEGIN +45.80s 4\n",
                           "4");
}

void gesture_update_should_match_regex() {
  const char *data = " event15  GESTURE_SWIPE_UPDATE +34.70s    3 -0.12/ 4.99 "
                     "(-0.33/13.50 unaccelerated)\n";
  std::regex matcher(
      comfortable_swipe::gesture::swipe_gesture::GESTURE_UPDATE_REGEX_PATTERN);
  std::cmatch matches;
  auto result = std::regex_match(data, matches, matcher);
  assert(result != 0);
  assert((std::string)matches[1] == "3");
  assert((std::string)matches[2] == "-0.12");
  assert((std::string)matches[3] == "4.99");
  assert((std::string)matches[4] == "-0.33");
  assert((std::string)matches[5] == "13.50");
}

void gesture_end_should_match_regex() {
  const char *data = " event15  GESTURE_SWIPE_END +35.03s   3\n";
  std::regex matcher(
      comfortable_swipe::gesture::swipe_gesture::GESTURE_END_REGEX_PATTERN);
  std::cmatch matches;
  auto result = std::regex_match(data, matches, matcher);
  assert(result != 0);
  assert((std::string)matches[1] == "3");
}
} // namespace test
