#ifndef __COMFORTABLE_SWIPE__service_config__
#define __COMFORTABLE_SWIPE__service_config__

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

#include "../index.hpp"
#include <cstdio> // std::puts

namespace comfortable_swipe::service
{
    /**
     * Prints where the config file of comfortable swipe is located.
     *
     * Usage: nano $(comfortable-swipe config)
     */
    void config()
    {
        std::puts(comfortable_swipe::util::conf_filename());
    }
}

#endif /* __COMFORTABLE_SWIPE__service_config__ */
