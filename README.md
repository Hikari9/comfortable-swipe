# Comfortable Swipe (Ubuntu)

[![comfortable-swipe version](https://img.shields.io/github/release/Hikari9/comfortable-swipe.svg?label=comfortable-swipe&color=orange)](https://github.com/Hikari9/comfortable-swipe/releases)
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

> **_New in Version 1.1.0!_** Added mouse gestures, see [#mouse-gestures-experimental](#mouse-gestures-experimental)

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
2. **_Important_**: After inputing your `sudo` password, log out then log back in
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

## Swipe Configurations

Comfortable swipe makes use of keyboard shortcuts for configurations. Edit by running:

```
gedit $(comfortable-swipe config)
```

| Property  |                 Description                  | Default Value        | Default Behavior                                                                                                           |
| --------- | :------------------------------------------: | -------------------- | -------------------------------------------------------------------------------------------------------------------------- |
| left3     |             3-finger swipe left              | ctrl+alt+Right       | switch to right workspace                                                                                                  |
| left4     |             4-finger swipe left              | ctrl+alt+shift+Right | move window to right workspace                                                                                             |
| right3    |             3-finger swipe right             | ctrl+alt+Left        | switch to left workspace                                                                                                   |
| right4    |             4-finger swipe right             | ctrl+alt+shift+Left  | move window to left workspace                                                                                              |
| up3       |              3-finger swipe up               | ctrl+alt+Down        | switch to bottom workspace                                                                                                 |
| up4       |              4-finger swipe up               | ctrl+alt+shift+Down  | move window to bottom workspace                                                                                            |
| down3     |             3-finger swipe down              | ctrl+alt+Up          | switch to above workspace                                                                                                  |
| down4     |             4-finger swipe down              | ctrl+alt+shift+Up    | move window to above workpace                                                                                              |
| threshold |        mouse pixels to activate swipe        | 0.0                  | tweak this if you're having troubles with touchpad sensitivity (higher = less sensitive, values can be as large as 1000.0) |
| hold3     | holds a mouse button when 3 fingers are down | (none)               | See [Mouse Gestures (Experimental)](#mouse-gestures-experimental)                                                                         |
| hold4     | holds a mouse button when 4 fingers are down | (none)               | See [Mouse Gestures (Experimental)](#mouse-gestures-experimental)                                                                         |

After making changes, make sure to restart the program:

```
comfortable-swipe restart
```

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

**Keyboard Shortcuts**:

- Unity: https://cheatography.com/sapemeg/cheat-sheets/ubuntu-unity-16-04/
- GNOME: https://wiki.gnome.org/Design/OS/KeyboardShortcuts
- KDE: https://community.linuxmint.com/tutorial/view/47

## Swipe Gesture Templates

1. Switching workspaces

   ```bash
   # Unity, KDE
   left3 = ctrl+alt+Right
   right3 = ctrl+alt+Left
   up3 = ctrl+alt+Down
   down3 = ctrl+alt+Up
   ```

   ```bash
   # GNOME
   up3 = super+PgDown
   down3 = super+PgUp
   ```

1. Move window to workspace

   ```bash
   # Unity, KDE
   left4 = ctrl+alt+shift+Right
   right4 = ctrl+alt+shift+Left
   up4 = ctrl+alt+shift+Down
   down4 = ctrl+alt+shift+Up
   ```

   ```bash
   # GNOME
   up4 = super+shift+PgDown
   down4 = super+shift+PgUp
   ```

1. Move window to other monitor

   ```bash
   # GNOME
   left4 = super+shift+Right
   right4 = super+shift+Left
   ```

1. Toggle workspace overview

   ```bash
   up3 = super+s
   ```

1. Show desktop ([setup manually](https://www.itsupportguides.com/knowledge-base/ubuntu/ubuntu-how-to-make-windows-d-show-desktop/))

   ```bash
   # Ubuntu
   down3 = ctrl+super+d
   ```
   
   ```bash
   # GNOME
   down3 = super+d
   ```

   ```bash
   # KDE
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

We have included simple mouse gestures on swipe by setting `hold3` and `hold4`.

**Possible Values**:

- `move` - just move the mouse cursor (no mousedown)
- `button1` - hold left click on finger swipe
- `button2` - hold middle click on finger swipe
- `button3` - hold right click on finger swipe
- `button4` - wheel up on finger swipe (experimental)
- `button5` - wheel down on finger swipe (experimental)
- `scroll` - naive 3/4 finger natural scroll (no acceleration, very experimental)
- `scroll_reverse` - naive 3/4 finger reverse scroll (no acceleration, very experimental)

Any value not mentioned above disables the mouse-hold.

Examples:

1. 3-finger drag

   ```bash
   hold3 = button1
   ```

1. 4-finger drag (with middle click)

   ```bash
   hold4 = button2
   ```

1. 3-finger natural scroll

   ```bash
   hold3 = scroll
   ```

1. 4-finger reverse scroll

   ```bash
   hold4 = scroll_reverse
   ```

1. Just move the cursor

   ```bash
   hold3 = move
   hold4 = move
   ```

1. Any other command will disable the mouse hold

   ```bash
   hold3 = disabled
   hold4 = nothing
   ```

**Note**: Applying any mouse-hold configuration will disable up/left/right/down behavior to avoid gesture conflicts. The logic of this will be improved in the future.

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
