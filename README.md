# Comfortable Swipe (Ubuntu)
[![comfortable-swipe version](https://img.shields.io/github/release/Hikari9/comfortable-swipe.svg?label=comfortable-swipe)](https://github.com/Hikari9/comfortable-swipe/releases)
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

Comfortable, seamless, and fast 3-finger (and 4-finger) touchpad swipe gestures for Ubuntu 14.04 LTS and beyond. May work for other Linux distros that support `libinput`.

## Installation

1. Install git, libinput, and g++

    ```bash
    sudo apt-get install git libinput-tools libxdo-dev g++
    ```

2. Clone this repository

    ```bash
    git clone https://github.com/Hikari9/comfortable-swipe.git --depth 1
    cd comfortable-swipe
    ```

3. Install

    ```bash
    bash install
    ```

4. You may delete the downloaded `comfortable-swipe` folder after installation.

## How to Run

1. You'll need some group permissions to read touchpad input data. Run
    ```bash
    sudo gpasswd -a $USER $(ls -l /dev/input/event* | awk '{print $4}' | head --line=1)
    ```
2. ***Important***: After inputing your `sudo` password, log out then log back in
3. Run
    ```
    comfortable-swipe start
    ```
4. _Optional_: Automatically run on startup
    ```
    comfortable-swipe autostart
    ```
5. Check the status of your application by running
    ```
    comfortable-swipe status
    ```

## Configurations
Comfortable swipe makes use of keyboard shortcuts for configurations. Edit by running
```
nano $(comfortable-swipe config)
```

Make sure to run after making changes:
```
comfortable-swipe restart
```

Property  | Description | Default Value | Default Behavior
--------- | ----------- | -------------- | -----
threshold | mouse pixels to activate swipe; higher = less sensitive; floating-point (Note: Sky is the limit! Can be as large as 1000.0) | 0.0
left3     | 3-finger swipe left | ctrl+shift+Right | switch to right workspace
left4     | 4-finger swipe left | ctrl+alt+shift+Right | move window to right workspace
right3    | 3-finger swipe right | ctrl+shift+Left | switch to left workspace
right4    | 4-finger swipe right | ctrl+alt+shift+Left | move window to left workspace
up3       | 3-finger swipe up | ctrl+shift+Down | switch to bottom workspace
up4       | 4-finger swipe up | ctrl+alt+shift+Down | move window to bottom workspace
down3     | 3-finger swipe down | ctrl+shift+Down | switch to above workspace
down4     | 4-finger swipe down | ctrl+alt+shift+Up | move window to above workpace

Taken from `man xdotool`:

> Type a given keystroke. Examples being "alt+r", "Control_L+J",
> "ctrl+alt+n", "BackSpace".
>
> Generally, any valid X Keysym string will work. Multiple keys are
> separated by '+'. Aliases exist for "alt", "ctrl", "shift",
> "super", and "meta" which all map to Foo_L, such as Alt_L and
> Control_L, etc.
>
> In cases where your keyboard doesn't actually have the key you want
> to type, xdotool will automatically find an unused keycode and use
> that to type the key.

Refer to https://www.linux.org/threads/xdotool-keyboard.10528/ for a complete list of keycodes you can use.


## Debugging

You can check your touchpad driver by running

```bash
comfortable-swipe debug
```

This is an alias of `libinput debug-events`. This logs all gestures you make on your touchpad, along with other input-based events that can be captured by libinput.

A working swipe gesture will show the following:

```bash
$ comfortable-swipe debug
...
-event9   DEVICE_ADDED     TouchPad                     seat0 default group7  cap:pg  size 70x50mm tap(dl off) left scroll-nat scroll-2fg-edge click-buttonareas-clickfinger dwt-on
...
event9   GESTURE_SWIPE_BEGIN  +2.03s   3
 event9   GESTURE_SWIPE_UPDATE  +2.03s  3 -9.95/ 2.64 (-26.90/ 7.12 unaccelerated)
 event9   GESTURE_SWIPE_UPDATE  +2.03s  3 -10.44/ 3.19 (-28.22/ 8.62 unaccelerated)
 event9   GESTURE_SWIPE_UPDATE  +2.04s  3 -9.71/ 2.64 (-26.25/ 7.12 unaccelerated)
 event9   GESTURE_SWIPE_UPDATE  +2.05s  3 -8.98/ 2.64 (-24.28/ 7.12 unaccelerated)
 event9   GESTURE_SWIPE_UPDATE  +2.06s  3 -7.40/ 2.36 (-20.01/ 6.37 unaccelerated)
 event9   GESTURE_SWIPE_UPDATE  +2.06s  3 -6.31/ 2.50 (-17.06/ 6.75 unaccelerated)
 event9   GESTURE_SWIPE_UPDATE  +2.07s  3 -5.34/ 1.80 (-14.44/ 4.87 unaccelerated)
 event9   GESTURE_SWIPE_UPDATE  +2.08s  3 -4.61/ 2.08 (-12.47/ 5.62 unaccelerated)
 event9   GESTURE_SWIPE_UPDATE  +2.09s  3 -4.49/ 1.53 (-12.14/ 4.12 unaccelerated)
 event9   GESTURE_SWIPE_UPDATE  +2.09s  3 -4.01/ 1.25 (-10.83/ 3.37 unaccelerated)
 event9   GESTURE_SWIPE_UPDATE  +2.10s  3 -4.13/ 0.42 (-11.15/ 1.12 unaccelerated)
 event9   GESTURE_SWIPE_END  +2.11s     3
 ...
```

If you can see `GESTURE_SWIPE_XXX` in your output, that means your touchpad supports multi-touch swipe gestures.

## Uninstall
Download the `uninstall` script then run `bash uninstall`


## Bug Reports
Create an issue [here](https://github.com/Hikari9/comfortable-swipe/issues/new) to report a bug.

Please include the output of the following:
```
lsb_release -a
g++ --version
xinput list | grep touchpad -i
lsmod | grep hid
comfortable-swipe start  # if you can run it
comfortable-swipe debug  # screenshot / first few lines
cat $(comfortable-swipe config)
```
