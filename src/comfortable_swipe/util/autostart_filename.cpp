#ifndef __COMFORTABLE_SWIPE__util_conf_filename__
#define __COMFORTABLE_SWIPE__util_conf_filename__

#include <string> // std::string
#include <unistd.h> // getenv

namespace comfortable_swipe::util
{
    /**
     * The path where the autostart configuration is located.
     */
    const char* autostart_filename()
    {
        static std::string filename;
        if (filename.empty()) {
            const char* xdg_config = getenv("XDG_CONFIG_HOME");
            std::string config(
                xdg_config == NULL
                    ? std::string(getenv("HOME")) + "/.config"
                    : xdg_config
            );
            filename = config + "/autostart/comfortable-swipe.desktop";
        }
        return filename.data();
    }
}

#endif /* __COMFORTABLE_SWIPE__util_conf_filename__ */
