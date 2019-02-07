#include "comfortable-swipe.hpp"
/* MAIN DRIVER FUNCTION */

int main(int argc, char** args) {
    if (argc > 1) {
        string arg = args[1];
        // select based on argument
        if (arg == "start") service::start();
        else if (arg == "stop") service::stop();
        else if (arg == "restart") service::restart();
        else if (arg == "buffer") service::buffer();
        else if (arg == "autostart") service::autostart();
        else service::help();
    } else {
        service::help();
    }
}