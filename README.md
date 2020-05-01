# Comfortable Swipe (Ubuntu)

[![comfortable-swipe version](https://img.shields.io/github/release/Hikari9/comfortable-swipe.svg?label=comfortable-swipe&color=orange)](https://github.com/Hikari9/comfortable-swipe/releases)
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

Comfortable, seamless, and fast 3-finger (and 4-finger) touchpad swipe gestures for Ubuntu 14.04 LTS and beyond. May work for other Linux distros that support `libinput`.

> **_New in Version 1.1.0_**: Added mouse gestures, see [#mouse-gestures-experimental](#mouse-gestures-experimental)

> **_New in Version 1.2.0_**: Autostart now switched ON by default

## Installation

1. Install git and g++

   ```bash
   sudo apt install git g++
   ```

1. Install libinput-tools and C libraries

   ```bash
   sudo apt install libinput-tools libconfuse-dev libxdo-dev
   ```

1. Clone this repository

   ```bash
   git clone https://github.com/Hikari9/comfortable-swipe.git --depth 1
   cd comfortable-swipe
   ```

1. Install

   ```bash
   bash install
   ```

1. You may delete the downloaded `comfortable-swipe` folder after installation.

## How to Run

1. You'll need some group permissions to read touchpad input data. Run

   ```bash
   sudo gpasswd -a "$USER" "$(ls -l /dev/input/event* | awk '{print $4}' | head --line=1)"
   ```

1. **_Important_**: After inputing your `sudo` password, log out then log back in

1. Run

   ```bash
   comfortable-swipe start
   ```

1. (Optional) Automatically run on startup

   ```bash
   comfortable-swipe autostart on
   ```

1. You can check general program status

   ```basha
   $> comfortable-swipe status
   Autostart is ON
   Program is RUNNING
   ```

## List of Commands

1. Program

   ```
   comfortable-swipe start
   comfortable-swipe stop
   comfortable-swipe status
   ```

1. Help / version

   ```
   comfortable-swipe --help
   comfortable-swipe --version
   ```

1. Autostart

   ```bash
   comfortable-swipe autostart [on|off|toggle|status|path]
   ```

1. Configurations

   ```bash
   comfortable-swipe config list
   comfortable-swipe config get <KEY>
   comfortable-swipe config set <KEY> [=] <VALUE>
   comfortable-swipe config delete <KEY>
   ```

   Get config:
   ```bash
   $> comfortable-swipe config get left3
   ctrl+alt+Right
   ```

   Set config (whitespace ignored):
   ```bash
   $> comfortable-swipe config set up4 super+Up
   up4 = super+Up

   $> comfortable-swipe config set left3 = super+Right
   left3 = super+Right

   $> comfortable-swipe config set right3 = super + Left + alt
   right3 = super+Left+alt
   ```

   Delete config:
   ```bash
   $> comfortable-swipe config delete mouse3
   ```

   List all cofigurations
   ```bash
   $> comfortable-swipe config list
   threshold = 1.0
   left4 = ctrl+super+shift+Right
   right3 = ctrl+super+Left
   right4 = ctrl+super+shift+Left
   up3 = ctrl+F12
   up4 = super+d
   down3 = ctrl+F12
   down4 = super+d
   mouse4 = button1
   left3 = ctrl+super+Right
   ```

   Show all possible keys:
   ```bash
   $> comfortable-swipe config keys
   left3
   left4
   right3
   right4
   up3
   up4
   down3
   down4
   threshold
   mouse3
   mouse4
   ```

   Show path to config file:
   ```bash
   $> comfortable-swipe config path
   /home/hikari9/.config/comfortable-swipe.conf
   ```

1. (Advanced) Invoke program buffer with `comfortable-swipe buffer`

   ```bash
   cat <<"EOF" | comfortable-swipe buffer
   -event7   GESTURE_SWIPE_BEGIN  +0.45s   3
   event7   GESTURE_SWIPE_UPDATE  +0.45s  3  8.81/-2.34 (32.48/-8.62 unaccelerated)
   event7   GESTURE_SWIPE_UPDATE  +0.46s  3 15.54/-3.88 (41.99/-10.50 unaccelerated)
   event7   GESTURE_SWIPE_UPDATE  +0.46s  3 18.09/-4.16 (48.88/-11.25 unaccelerated)
   event7   GESTURE_SWIPE_UPDATE  +0.47s  3 19.67/-3.61 (53.15/-9.75 unaccelerated)
   event7   GESTURE_SWIPE_UPDATE  +0.48s  3 19.79/-3.19 (53.48/-8.62 unaccelerated)
   event7   GESTURE_SWIPE_UPDATE  +0.49s  3 17.72/-2.36 (47.90/-6.37 unaccelerated)
   event7   GESTURE_SWIPE_UPDATE  +0.49s  3 15.66/-2.36 (42.32/-6.37 unaccelerated)
   event7   GESTURE_SWIPE_UPDATE  +0.50s  3 13.35/-2.08 (36.09/-5.62 unaccelerated)
   event7   GESTURE_SWIPE_UPDATE  +0.51s  3 10.80/-1.94 (29.20/-5.25 unaccelerated)
   event7   GESTURE_SWIPE_UPDATE  +0.52s  3  8.38/-1.53 (22.64/-4.12 unaccelerated)
   event7   GESTURE_SWIPE_UPDATE  +0.53s  3  6.43/-1.25 (17.39/-3.37 unaccelerated)
   event7   GESTURE_SWIPE_UPDATE  +0.53s  3  4.86/-0.83 (13.12/-2.25 unaccelerated)
   event7   GESTURE_SWIPE_UPDATE  +0.54s  3  3.76/-0.55 (10.17/-1.50 unaccelerated)
   event7   GESTURE_SWIPE_UPDATE  +0.55s  3  2.67/-0.28 ( 7.22/-0.75 unaccelerated)
   event7   GESTURE_SWIPE_UPDATE  +0.56s  3  1.70/ 0.28 ( 4.59/ 0.75 unaccelerated)
   event7   GESTURE_SWIPE_UPDATE  +0.56s  3  1.09/ 0.14 ( 2.95/ 0.37 unaccelerated)
   event7   GESTURE_SWIPE_END  +0.59s     3
   EOF
   ```

## Configuring Swipe Gestures

The default configuration file is located at `~/.config/comfortable-swipe.conf`.
Comfortable swipe makes use of keyboard shortcuts to perform swipes through `xdotool`.


Edit configurations by running:

```
gedit ~/.config/comfortable-swipe.conf
```

After making changes, make sure to restart the program:

```
comfortable-swipe restart
```

> **Note**: For v1.1.0 below, the configuration file is located at
> `/usr/local/share/comfortable-swipe/comfortable-swipe.conf`

> **Note**: You can locate your configuration by running `comfortable-swipe config path`

## Configuration Reference

| Key       |                                 Value                                  | Example                                                      |
| --------- | :--------------------------------------------------------------------: | ------------------------------------------------------------ |
| left3     |                          3-finger swipe left                           | ctrl+alt+Right                                               |
| left4     |                          4-finger swipe left                           | ctrl+alt+shift+Right                                         |
| right3    |                          3-finger swipe right                          | ctrl+alt+Left                                                |
| right4    |                          4-finger swipe right                          | ctrl+alt+shift+Left                                          |
| up3       |                           3-finger swipe up                            | ctrl+alt+Down                                                |
| up4       |                           4-finger swipe up                            | ctrl+alt+shift+Down                                          |
| down3     |                          3-finger swipe down                           | ctrl+alt+Up                                                  |
| down4     |                          4-finger swipe down                           | ctrl+alt+shift+Up                                            |
| thresmouse | mouse movement pixels that trigger a swipe (can be as large as 1000.0) | 0.0, 240.0, 1000.0                                           |
| mouse3    |              mouses a mouse button when 3 fingers are down              | button1 (see [Mouse Gestures](#mouse-gestures-experimental)) |  |
| mouse4    |              mouses a mouse button when 4 fingers are down              | button1 (see [Mouse Gestures](#mouse-gestures-experimental)  |

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

## Keyboard shortcuts

- [Unity Keyboard Shortcuts](https://cheatography.com/sapemeg/cheat-sheets/ubuntu-unity-16-04/)
- [GNOME Keyboard Shortcuts](https://wiki.gnome.org/Design/OS/KeyboardShortcuts)
- [KDE Keyboard Shortcuts](https://community.linuxmint.com/tutorial/view/47)

> **Note**: You can check which desktop you are using with `echo $DESKTOP_SESSION`.

## Example Configurations

This section includes some example configurations which you can use for your swipe experience.

1. Switch workspace (horizontal)

   ```bash
   comfortable-swipe config set left3 = ctrl+alt+Right
   comfortable-swipe config set right3 = ctrl+alt+Left
   ```

1. Switch workspace (vertical)

   ```
   up3 = ctrl+alt+Down
   down3 = ctrl+alt+Up
   ```

   ```bash
   up3 = super+PgDown
   down3 = super+PgUp
   ```

1. Move window to workspace (horizontal)

   ```bash
   left4 = ctrl+alt+shift+Right
   right4 = ctrl+alt+shift+Left
   ```

1. Move window to workspace (vertical)

   ```bash
   up4 = ctrl+alt+shift+Down
   down4 = ctrl+alt+shift+Up
   ```

   ```bash
   up4 = super+shift+PgDown
   down4 = super+shift+PgUp
   ```

1. Move window to other monitor

   ```bash
   left4 = super+shift+Right
   right4 = super+shift+Left
   ```

1. Toggle workspace overview

   ```bash
   up3 = super+s
   ```

1. Show desktop

   ```bash
   down3 = super+d
   ```

   ```bash
   down3 = ctrl+super+d
   ```

   ```bash
   down3 = ctrl+alt+d
   ```

1. Snap windows to the left/right

   ```bash
   left3 = super+Left
   right3 = super+Right
   ```

1. Toggle maximize

   ```bash
   up3 = super+Up
   ```

1. Toggle minimize

   ```bash
   down3 = super+Down
   ```

1. Alt+Tab switch application (experimental)

   ```bash
   left3 = alt+Tab
   right3 = alt+shift+Tab
   ```

## Mouse Gestures (Experimental)

You can also play around with mouse gestures during swipe.
This enables certain mouse behaviour to trigger along with a 3/4-finger swipe.

Keys:

- mouse3 - for 3-finger mouse gestures
- mouse4 - for 4-finger mosue gestures
- hold3 (deprecated) - old equivalent of mouse3
- hold4 (deprecated) - old equivalent of mouse4

Possible Values:

- button1 - left click
- button2 - middle click
- button3 - right click
- button4 - wheel up (experimental)
- button5 - wheel down (experimental)
- move - just move the mouse cursor while fingers are down
- scroll - 3/4 finger natural scroll (no acceleration, very experimental)
- scroll_reverse - 3/4 finger reverse scroll (no acceleration, very experimental)

Examples:

- 3/4-finger drag
  ```bash
  mouse3 = button1
  ```
  ```bash
  mouse4 = button1
  ```
- 3/4-finger natural scroll

  ```bash
  mouse3 = scroll
  ```

  ```bash
  mouse4 = scroll
  ```

- 3/4-finger reverse scroll

  ```bash
  mouse3 = scroll_reverse
  ```

  ```bash
  mouse4 = scroll_reverse
  ```

- Move 3/4-fingers with the cursor

  ```bash
  mouse3 = move
  ```
  ```bash
  mouse4 = move
  ```

**Note**: Applying any mouse-mouse configuration may disable up/left/right/down behavior to avoid gesture conflicts. The logic of this will be improved in the future.

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

Run the following script:

```bash
wget -qO - https://raw.githubusercontent.com/Hikari9/comfortable-swipe/master/uninstall | bash
```

## Bug Reports

Search in [Issues](https://github.com/Hikari9/comfortable-swipe/issues?utf8=%E2%9C%93&q=is%3Aissue) if the problem has already been solved.

Otherwise, [create a new issue](https://github.com/Hikari9/comfortable-swipe/issues/new) to report your bug.

Please include the output of the following:

1. `lsb_release -a`
2. `g++ --version`
3. `ls -l /dev/input/event*`
4. `xinput list | grep touchpad -i`
5. `lsmod | grep hid`
6. `comfortable-swipe status`
7. `comfortable-swipe start` (if you can run it)
8. `comfortable-swipe debug` (try swiping if you can see `GESTURE_SWIPE_XXX`)
9. `cat $(comfortable-swipe config)`
