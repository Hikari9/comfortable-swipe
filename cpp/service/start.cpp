#ifndef __COMFORTABLE_SWIPE__service_start__
#define __COMFORTABLE_SWIPE__service_start__

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

#include "_index.hpp"
#include <iostream> // std::cin, std::cout, std::ios
#include <cstdlib> // std::system
#include <unistd.h> // pipe, fork, perror, exit

namespace comfortable_swipe::service
{
    /**
     * Starts the comfortable-swipe service by buffering libinput debug-events.
     * This method is deferred. Please refer to comfortable_swipe::service::buffer()
     * for the technical implementation.
     */
    void start()
    {
        std::ios::sync_with_stdio(false);
        std::cin.tie(0);
        std::cout.tie(0);
        std::cout.flush();

        // redirect stdout to stdin
        int fd[2];
        pipe(fd); // create the pipes

        int child;
        if ((child = fork()) == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (child) {
            dup2(fd[1], STDOUT_FILENO);
            comfortable_swipe::service::debug();
            close(fd[0]);
        } else {
            dup2(fd[0], STDIN_FILENO);
            comfortable_swipe::service::buffer();
            close(fd[1]);
        }
        comfortable_swipe::service::stop();
    }
}

#endif /* __COMFORTABLE_SWIPE__service_start__ */
