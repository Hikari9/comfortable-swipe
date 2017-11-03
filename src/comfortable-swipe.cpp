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

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdarg>
#include <cassert>
#include <cmath>
#include <regex>
#include <chrono>
#include <ctime>
#include <unistd.h>
#define cstr const string&
using namespace std;

extern "C" {
    // sudo apt install libxdo-dev
    #include <xdo.h>
}

/* MASKS FOR GESTURES */

#define MSK_THREE_FINGERS 0
#define MSK_FOUR_FINGERS 1
#define MSK_NEGATIVE 0
#define MSK_POSITIVE 2
#define MSK_HORIZONTAL 0
#define MSK_VERTICAL 4

/* GESTURE MNEMONYMS */
#define FRESH -1
#define OPPOSITE (mask ^ MSK_POSITIVE)

/* FORWARD DECLARATIONS */

namespace util {
    string join(cstr, string[], int);
    string build_gesture_begin();
    string build_gesture_update();
    string build_gesture_end();
    map<string, string> read_config_file(const char*);
}

namespace service {
    void buffer();
    void start();
    void stop();
    void restart();
    void autostart();
    void help();
}

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

struct swipe_gesture {
    string device, stamp, fingers;
    string dx, dy, udx, udy;
    xdo_t* xdo;
    virtual void on_update() = 0;
    virtual void on_begin() = 0;
    virtual void on_end() = 0;
    swipe_gesture(): xdo(xdo_new(NULL)) {}
    ~swipe_gesture() {xdo_free(xdo);}
};

const char* const command_map[] = {
    "left 3",
    "left 4",
    "right 3",
    "right 4",
    "up 3",
    "up 4",
    "down 3",
    "down 4"
};

struct swipe_gesture_impl : swipe_gesture {
    int screen_num, ix, iy, threshold;
    float x, y;
    int previous_gesture;
    const char** commands;
    swipe_gesture_impl(
        const int threshold,
        const char* left3   /* 000 */,
        const char* left4   /* 001 */,
        const char* right3  /* 010 */,
        const char* right4  /* 011 */,
        const char* up3     /* 100 */,
        const char* up4     /* 101 */,
        const char* down3   /* 110 */,
        const char* down4   /* 111 */
    ): swipe_gesture(), threshold(threshold) {
        commands = new const char*[8];
        commands[0] = left3;
        commands[1] = left4;
        commands[2] = right3;
        commands[3] = right4;
        commands[4] = up3;
        commands[5] = up4;
        commands[6] = down3;
        commands[7] = down4;
    }
    ~swipe_gesture_impl() {
        delete[] commands;
    }
    void key(const char* cmd) const {
        xdo_send_keysequence_window(xdo, CURRENTWINDOW, cmd, 0);
    }
    void on_begin() override {
        xdo_get_mouse_location(xdo, &ix, &iy, &screen_num);
        previous_gesture = FRESH;
        x = 0;
        y = 0;
    }
    void on_update() override {
        x += stof(dx);
        y += stof(dy);
        // scale threshold to 1/10 when gesture is not fresh
        float scale = previous_gesture == FRESH ?
                1.0f :
                0.1f;
        if (x*x + y*y > threshold*threshold*(scale*scale)) {
            int mask = 0;
            if (fingers == "3") mask |= MSK_THREE_FINGERS; else
            if (fingers == "4") mask |= MSK_FOUR_FINGERS;
            if (abs(x) > abs(y)) {
                mask |= MSK_HORIZONTAL;
                if (x < 0) mask |= MSK_NEGATIVE;
                else mask |= MSK_POSITIVE;
            } else {
                mask |= MSK_VERTICAL;
                if (y < 0) mask |= MSK_NEGATIVE;
                else mask |= MSK_POSITIVE;
            }
            // send command on fresh OR opposite gesture
            if (previous_gesture == FRESH or previous_gesture == OPPOSITE) {
                x = y = 0;
                previous_gesture = mask;
                cout << "SWIPE " << command_map[mask] << endl;
                key(commands[mask]);
            }
        }
    }
    void on_end() override {
    }
};

// path services
namespace service {
    // get the full path of the .conf file
    string conf_filename() {
        static string *filename = NULL;
        if (filename == NULL) {
            const char* xdg_config = getenv("XDG_CONFIG_HOME");
            string config(
                xdg_config == NULL
                    ? string(getenv("HOME")) + "/.config"
                    : xdg_config
            );
            filename = new string(config + "/comfortable-swipe.conf");
        }
        return *filename;
    }
    // get the full path of the .desktop file associated
    // with the autostart feature
    string autostart_filename() {
        static string *filename = NULL;
        if (filename == NULL) {
            const char* xdg_config = getenv("XDG_CONFIG_HOME");
            string config(
                xdg_config == NULL
                    ? string(getenv("HOME")) + "/.config"
                    : xdg_config
            );
            filename = new string(config
                + "/autostart/comfortable-swipe.desktop");
        }
        return *filename;
    }
}

namespace service {    
    // parses output from libinput-debug-events
    void buffer() {
        // check first if $user
        ios::sync_with_stdio(false);
        cin.tie(0); cout.tie(0);
        const regex gesture_begin(util::build_gesture_begin());
        const regex gesture_update(util::build_gesture_update());
        const regex gesture_end(util::build_gesture_end());
        string sentence;
        // read config file
        auto config = util::read_config_file(conf_filename().data());
        // initialize gesture handler       
        swipe_gesture_impl swipe(
            config.count("threshold") ? stoi(config["threshold"]) : 20,
            config["left3"].c_str(),
            config["left4"].c_str(),
            config["right3"].c_str(),
            config["right4"].c_str(),
            config["up3"].c_str(),
            config["up4"].c_str(),
            config["down3"].c_str(),
            config["down4"].c_str()
        );
        while (getline(cin, sentence)) {
            auto data = sentence.data();
            cmatch matches;
            if (regex_match(data, matches, gesture_begin)) {
               swipe.device = matches[1];
               swipe.stamp = matches[2];
               swipe.fingers = matches[3];
               swipe.on_begin();
            }
            else if (regex_match(data, matches, gesture_end)) {
               swipe.device = matches[1];
               swipe.stamp = matches[2];
               swipe.fingers = matches[3];
               swipe.on_end();
            }
            else if (regex_match(data, matches, gesture_update)) {
               swipe.device = matches[1];
               swipe.stamp = matches[2];
               swipe.fingers = matches[3];
               swipe.dx = matches[4];
               swipe.dy = matches[5];
               swipe.udx = matches[6];
               swipe.udy = matches[7];
               swipe.on_update();
            }
        }
    }
    // starts service
    void start() {
        int x = system("stdbuf -oL -eL libinput-debug-events | $HOME/.local/bin/comfortable-swipe buffer");
    }
    // stops service
    void stop() {
        // kill all comfortable-swipe, except self
        char* buffer = new char[20];
        FILE* pipe = popen("pgrep -f comfortable-swipe", "r");
        if (!pipe) throw std::runtime_error("stop command failed");
        string kill = "kill";
        while (!feof(pipe)) {
            if (fgets(buffer, 20, pipe) != NULL) {
                int pid = atoi(buffer);
                if (pid != getpid()) {
                    kill += " " + to_string(pid);
                }
            }
        }
        int result = system(kill.data());
        delete[] buffer;
        pclose(pipe);
    }
    // stops then starts service
    void restart() {
        service::stop();
        service::start();
    }
    // toggle automatically start application on startup
    void autostart() {
        string path = autostart_filename();
        if (ifstream(path.data()).good()) {
            // file found, delete it
            if (remove(path.data()) != 0)
                cerr << "Error: failed to switch off autostart. "
                     << "Maybe the autostart file is in use?"
                     << endl;
            else
                cout << "Autostart switched off" << endl;
        } else {
            // file not found, create it
            int result = system(("mkdir -p $(dirname " + path + ")").data());
            ofstream fout(path.data());
            if (result != 0 || !fout.good())
                cerr << "Error: failed to switch on autostart. "
                     << "Are you sure you have the permissions?"
                     << endl;
            else {
                fout <<
                    "[Desktop Entry]\n"
                    "Type=Application\n"
                    "Exec=comfortable-swipe start\n"
                    "Hidden=false\n"
                    "NoDisplay=false\n"
                    "X-GNOME-Autostart-enabled=true\n"
                    "Name=Comfortable Swipe\n"
                    "Comment=3 or 4 touchpad gestures\n";
                cout << "Autostart switched on" << endl;
            }
        }
    }
    // shows help
    void help() {
        puts("comfortable-swipe [start|stop|restart|autostart|buffer|help]");
        puts("");
        puts("start      - starts 3/4-finger gesture service");
        puts("stop       - stops 3/4-finger gesture service");
        puts("restart    - stops then starts 3/4-finger gesture service");
        puts("autostart  - automatically run on startup (toggleable)");
        puts("buffer     - parses output of libinput-debug-events");
        puts("help       - shows the help dialog");
        puts("");
        puts((("Configuration file can be found in ") + conf_filename()).data());
    }
}

/* UTILITY FUNCTIONS */

namespace util {

    string number_regex() {
        return "-?\\d+(?:\\.\\d+)";
    }

    string join(cstr delim, string arr[], int n) {
        string ans = arr[0];
        for (int i = 1; i < n; ++i) {
            ans += delim;
            ans += arr[i];
        }
        return ans;
    }

    string build_gesture_begin() {
        string device = "\\s*(\\S+)\\s*";
        string gesture = "\\s*GESTURE_SWIPE_BEGIN\\s*";
        string seconds = "\\s*(\\S+)\\s*";
        string fingers = "\\s*(\\d+)\\s*";
        string arr[] = {device, gesture, seconds, fingers};
        return join("\\s+", arr, 4);
    }

    string build_gesture_update() {
        string device = "\\s*(\\S+)\\s*";
        string gesture = "\\s*GESTURE_SWIPE_UPDATE\\s*";
        string seconds = "\\s*(\\S+)\\s*";
        string fingers = "\\s*(\\d+)\\s*";
        string num_1 = "\\s*(" + number_regex() + ")\\s*";
        string num_2 = num_1;
        string num_div = num_1 + "/" + num_2;
        string num_accel = "\\s*\\(\\s*" + num_div + "\\s*unaccelerated\\s*\\)\\s*";
        string arr[] = {device, gesture, seconds, fingers, num_div, num_accel};
        return join("\\s+", arr, 6);
    }

    string build_gesture_end() {
        string device = "\\s*(\\S+)\\s*";
        string gesture = "\\s*GESTURE_SWIPE_END\\s*";
        string seconds = "\\s*(\\S+)\\s*";
        string fingers = "\\s*(\\d+)\\s*";
        string arr[] = {device, gesture, seconds, fingers};
        return join("\\s+", arr, 4);
    }
    
    map<string, string> read_config_file(const char* filename) {
        map<string, string> conf;
        ifstream fin(filename);
        if (!fin.is_open()) {
            cerr << "file \"" << filename << "\" does not exist!" << endl;
            exit(1);
        }
        string line, key, token, buffer, value;
        int line_number = 0;
        while (getline(fin, line)) {
            ++line_number;
            istringstream is(line);
            buffer.clear();
            while (is >> token) {
                if (token[0] == '#')
                    break;
                buffer += token;
            }
            if (buffer.empty())
                continue;
            auto id = buffer.find('=');
            if (id == string::npos) {
                cerr << "error in conf file: " << filename << endl;
                cerr << "equal sign expected in line " << line_number << endl;
                exit(1);
            }
            key = buffer.substr(0, id);
            value = buffer.substr(id + 1);
            conf[key] = value;
        }
        return conf;
    }

}
