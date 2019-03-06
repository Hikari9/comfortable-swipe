# Comfortable Swipe (Ubuntu)
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

Comfortable, seamless, and fast 3-finger (and 4-finger) touchpad swipe gestures for Ubuntu 14.04 LTS and beyond. May work for other Linux distros that support `libinput`.

## Installation

1. Update and install essential tools and libraries

    ```bash
    sudo apt update && sudo apt install git g++-7 python3-pip libinput-tools libxdo-dev
    ```

2. Install `comfortable-swipe` for your user

    ```bash
    pip3 install --user git+https://github.com/Hikari9/comfortable-swipe
    ```

3. You can check status with `comfortable-swipe status`

    ```bash
    $ comfortable-swipe status
    usr/local/share/comfortable-swipe/comfortable-swipe.conf
        threshold = 0.0
            left3 = ctrl+alt+Right
            left4 = ctrl+alt+shift+Right
           right3 = ctrl+alt+Left
           right4 = ctrl+alt+shift+Left
              up3 = ctrl+alt+Down
              up4 = ctrl+alt+shift+Down
            down3 = ctrl+alt+Up
            down4 = ctrl+alt+shift+Up
    autostart is ON
    comfortable-swipe program is STOPPED
    ```

3. You can list down all commands with `comfortable-swipe` or `comfortable-swipe help`

    ```bash
    $ comfortable-swipe
    comfortable-swipe [start|stop|restart|autostart|buffer|help|config|debug|status]

    start      - starts 3/4-finger gesture service
    stop       - stops 3/4-finger gesture service
    restart    - stops then starts 3/4-finger gesture service
    autostart  - automatically run on startup (toggleable)
    buffer     - parses output of libinput debug-events
    help       - shows the help dialog
    config     - locates the config file
    debug      - logs raw output from input events taken from libinput
    status     - checks status of program and autostart
    ```

## How to Run

1. You'll need some group permissions to read touchpad input data. Run
    ```bash
    sudo gpasswd -a $USER $(ls -l /dev/input/event* | awk '{print $4}' | head --line=1)
    ```
2. ***Important***: After inputing your `sudo` password, log out then log back in
3. Start
    ```bash
    comfortable-swipe start
    ```

## How to Upgrade

```bash
pip3 install -U --user git+https://github.com/Hikari9/comfortable-swipe
```

## Uninstall

```bash
# Uncomment below to remove configurations (not recommended)
# rm $(comfortable-swipe config)
pip3 uninstall comfortable-swipe
```

## Other Commands

1. `comfortable-swipe config` - outputs location of configuration file

    ```bash
    $ comfortable-swipe config
    /usr/local/share/comfortable-swipe/comfortable-swipe.conf
    ```

2. `comfortable-swipe autostart` - Toggles autostart
    ```bash
    $ comfortable-swipe autostart
    Autostart switched off
    ```

3. `comfortable-swipe debug` - Debugs input (this is an unbuffered alias of `libinput debug-events`)

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

## Configurations

Comfortable swipe makes use of keyboard shortcuts for configurations. Edit by running

```
nano $(comfortable-swipe config)
```

Make sure to restart after making changes:
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

## Bug Reports

Create an issue [here](https://github.com/Hikari9/comfortable-swipe-ubuntu/issues/new) to report a bug.
