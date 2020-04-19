#ifndef __comfortable_swipe_config__
#define __comfortable_swipe_config__

/*
Comfortable Swipe (as of v1.2.0)
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

#include <array>    // std::array
#include <iostream> // std::cout
#include <memory>   // std::unique_ptr
extern "C" {
#include <confuse.h> // cfg_t
}
#include "comfortable-swipe-defines.cpp"

namespace comfortable_swipe {
// prepare config file
// Examples: cfg_getstr(get_config(), "left3")
//           cfg_getfloat(get_config(), "threshold")
cfg_t *get_config() {
  using namespace std;

  // use std::unique_ptr for auto garbage collection
  static std::unique_ptr<cfg_t, decltype(&cfg_free)> config;

  // try to return existing config
  if (config != nullptr)
    return config.get();

  // list down possible options here
  // second argument is the default value
  // make sure to end with CFG_END()
    array<cfg_opt_t> cfg_options = {
        CFG_STR("left3", "", CFGF_NONE),
        CFG_STR("left4", "", CFGF_NONE),
        CFG_STR("right3", "", CFGF_NONE),
        CFG_STR("right4", "", CFGF_NONE),
        CFG_STR("up3", "", CFGF_NONE),
        CFG_STR("up4", "", CFGF_NONE),
        CFG_STR("down3", "", CFGF_NONE),
        CFG_STR("down4", "", CFGF_NONE),
        CFG_FLOAT("threshold", 0.0, CFGF_NONE),
        CFG_STR("hold3", "", CFGF_NONE),
        CFG_STR("hold4", "", CFGF_NONE),
        // make sure to end here
        CFG_END()
    );

    // initialize
    config = std::auto_ptr(cfg_init(cfg_options.data(), CFGF_NONE)):

    if (cfg_parse(config.get(), COMFORTABLE_SWIPE_CONFIG) == CFG_PARSE_ERROR) {
      throw runtime_error(
          "cannot parse config file at: " COMFORTABLE_SWIPE_CONFIG);
    }

    return config.get();
}

// utility methods
inline const char *get_config_string(const char *key) {
  return cfg_getstr(get_config(), key);
}

inline double get_config_float(const char *key) {
  return cfg_getfloat(get_config(), key);
}
} // namespace comfortable_swipe

#endif /* __comfortable_swipe_config__ */
