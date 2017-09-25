// you may tweak these before calling `build`
#define THRESHOLD                           20

#define CMD_THREE_FINGERS_RIGHT    "ctrl+alt+Left"
#define CMD_THREE_FINGERS_LEFT     "ctrl+alt+Right"
#define CMD_THREE_FINGERS_UP       "super+w"
#define CMD_THREE_FINGERS_DOWN     "super+w"

#define CMD_FOUR_FINGERS_RIGHT     "ctrl+shift+alt+Left"
#define CMD_FOUR_FINGERS_LEFT      "ctrl+shift+alt+Right"
#define CMD_FOUR_FINGERS_UP        "super+d"
#define CMD_FOUR_FINGERS_DOWN      "super+d"

#define MSK_THREE_FINGERS 0
#define MSK_FOUR_FINGERS 1
#define MSK_NEGATIVE 0
#define MSK_POSITIVE 2
#define MSK_HORIZONTAL 0
#define MSK_VERTICAL 4

const char* commands[] = {
    CMD_THREE_FINGERS_LEFT /* 000 */, CMD_FOUR_FINGERS_LEFT /* 001 */,
    CMD_THREE_FINGERS_RIGHT /* 010 */ , CMD_FOUR_FINGERS_RIGHT /* 011 */,
    CMD_THREE_FINGERS_UP /* 100 */ , CMD_FOUR_FINGERS_UP /* 101 */,
    CMD_THREE_FINGERS_DOWN /* 110 */, CMD_FOUR_FINGERS_DOWN /* 111 */
};

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdarg>
#include <cassert>
#include <regex>
#include <chrono>
#include <ctime>
#include <unistd.h>
extern "C" {
    // sudo apt install libxdo-dev
    #include <xdo.h>
}
using namespace std;
#define cstr const string&

/* FORWARD DECLARATIONS */

namespace util {
    string join(cstr, string[], int);
    string build_gesture_begin();
    string build_gesture_update();
    string build_gesture_end();
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

struct swipe_gesture_impl : swipe_gesture {
    int screen_num, ix, iy;
    double x, y;
    bool gesture_done;
    swipe_gesture_impl(): swipe_gesture() {}
    ~swipe_gesture_impl() {}
    void key(const char* cmd) const {
        xdo_send_keysequence_window(xdo, CURRENTWINDOW, cmd, 0);
    }
    void on_begin() override {
        // cout << "BEGIN" << endl;
        xdo_get_mouse_location(xdo, &ix, &iy, &screen_num);
        gesture_done = false;
        x = 0;
        y = 0;
    }
    void on_update() override {
        if (gesture_done) return;
        // cout << "UPDATE " << x << ' ' << y << " [" << dx << ", " << dy << "]" << endl;
        x += stod(dx);
        y += stod(dy);
        if (x*x + y*y > THRESHOLD*THRESHOLD) {
            gesture_done = true;
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
            // cout << "FLICK " << mask << ' ' << commands[mask] << endl;
            key(commands[mask]);
        }
    }
    void on_end() override {
        // pass
    }
};


/* MAIN DRIVER FUNCTION */

int main(int argc, char** args) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    const regex gesture_begin(util::build_gesture_begin());
    const regex gesture_update(util::build_gesture_update());
    const regex gesture_end(util::build_gesture_end());
    string sentence;
    swipe_gesture_impl swipe;
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

}
