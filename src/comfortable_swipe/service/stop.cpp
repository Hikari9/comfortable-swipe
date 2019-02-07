#ifndef __COMFORTABLE_SWIPE__service_stop__
#define __COMFORTABLE_SWIPE__service_stop__

#include <cstdio> // std::FILE, std::feof, std::fgets
#include <cstdlib> // std::atoi, std::system
#include <string> // std::string, std::to_string
#include <stdexcept> // std::runtime_error
#include <unistd.h> // popen, pclose, getpid

namespace comfortable_swipe::service
{
    /**
     * Stops all comfortable-swipe instances.
     */
    void stop()
    {

        // read all service names from process (pgrep)
        char* buffer = new char[20];
        FILE* pipe = popen("pgrep -f comfortable-swipe", "r");
        
        // make sure pipe exists
        if (pipe == NULL)
        {
            throw std::runtime_error("stop command failed");
        }

        // buffer what to kill
        std::string kill = "kill";

        // read until end of line
        while (!std::feof(pipe))
        {
            if (std::fgets(buffer, 20, pipe) != NULL)
            {
                int pid = std::atoi(buffer);
                if (pid != getpid())
                {
                    kill += " ";
                    kill += std::to_string(pid);
                }
            }
        }

        // run "kill {pid1} {pid2}..."
        std::system(kill.data());
        delete[] buffer;

        // close the pipe 
        pclose(pipe);

    }
}

#endif /* __COMFORTABLE_SWIPE__service_stop__ */
