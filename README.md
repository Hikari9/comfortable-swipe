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
   sudo apt install libinput-tools libinih-dev libxdo-dev
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

## List of Commands

1. Start the Program

   ```
   comfortable-swipe start
   ```

   You will see this output:

   ```
   $ comfortable-swipe start
   Comfortable swipe is RUNNING in the background
   ```

1. List configurations

   ```bash
   comfortable-swipe config list
   ```

   Example:

   ```bash
   $ comfortable-swipe config list
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

1) Get config

   ```
   comfortable-swipe <PROPERTY>
   ```

   Examples:

   ```bash
   $ comfortable-swipe left3
   ctrl+alt+Right
   ```

   ```bash
   $ comfortable-swipe left4
   ctrl+alt+shift+Right
   ```

   ```bash
   $ comfortable-swipe threshold
   1.0
   ```

1) Set config

   ```bash
   comfortable-swipe <PROPERTY> [=] <VALUES>
   ```

   Examples:

   ```bash
   comfortable-swipe left3 super+Right
   comfortable-swipe right3 super+Left
   comfortable-swipe right4 ctrl   alt + Left
   comfortable-swipe down4 super+d
   comfortable-swipe up3 = ctrl+shift+Up
   ```

1) Show path to config file:

   ```bash
   $ comfortable-swipe config path
   /home/hikari9/.config/comfortable-swipe.conf
   ```

<details>
<summary>Other Commands</summary>

1. Autostart

   ```bash
   comfortable-swipe autostart
   comfortable-swipe autostart on
   comfortable-swipe autostart off
   comfortable-swipe autostart toggle
   comfortable-swipe autostart status
   comfortable-swipe autostart path
   ```

1. Configurations

   ```bash
   comfortable-swipe config list
   comfortable-swipe config get <PROPERTY>
   comfortable-swipe config set <PROPERTY> [=] <VALUE>
   comfortable-swipe config path
   comfortable-swipe config keys
   ```

1. Help and Version

   ```bash
   comfortable-swipe --version
   comfortable-swipe --help
   ```

1. Show output with `--attach`

   Example output of 3-finger left, 4-finger left, 3-finger right, 3-finger up:

   ```bash
   $ comfortable-swipe start --attach
   SWIPE left3
   SWIPE left4
   SWIPE right3
   SWIPE up3
   ...
   ```

   You can also pass `--bare` to attach without actually swiping.

</details>

## Swipe Gesture Configurations

The default configuration file is located at `~/.config/comfortable-swipe.conf`.
Comfortable swipe makes use of **keyboard shortcuts** to perform swipes, through `xdotool`.

Edit the configuration file by running:

```
gedit ~/.config/comfortable-swipe.conf
```

After making changes, make sure to restart the program:

```
comfortable-swipe start
```

> **Warning**: For v1.1.0 below, the configuration file is located at
> `/usr/local/share/comfortable-swipe/comfortable-swipe.conf`

> **Note**: You can locate the absolute path to your configuration by running: `comfortable-swipe config path`

## Configuration Reference

| Key       |                                 Value                                  | Defaults                                                          |
| --------- | :--------------------------------------------------------------------: | ----------------------------------------------------------------- |
| left3     |                          3-finger swipe left                           | ctrl+alt+Right                                                    |
| left4     |                          4-finger swipe left                           | ctrl+alt+shift+Right                                              |
| right3    |                          3-finger swipe right                          | ctrl+alt+Left                                                     |
| right4    |                          4-finger swipe right                          | ctrl+alt+shift+Left                                               |
| up3       |                           3-finger swipe up                            | ctrl+alt+Down                                                     |
| up4       |                           4-finger swipe up                            | ctrl+alt+shift+Down                                               |
| down3     |                          3-finger swipe down                           | ctrl+alt+Up                                                       |
| down4     |                          4-finger swipe down                           | ctrl+alt+shift+Up                                                 |
| threshold | mouse movement pixels that trigger a swipe (can be as large as 1000.0) | 0.0, 240.0, 1000.0                                                |
| mouse3    |             mouses a mouse button when 3 fingers are down              | button1 <br> (see [Mouse Gestures](#mouse-gestures-experimental)) |  |
| mouse4    |             mouses a mouse button when 4 fingers are down              | button1 <br> (see [Mouse Gestures](#mouse-gestures-experimental)  |

### Keystrokes

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

Keyboard shortcuts:

- [Unity Keyboard Shortcuts](https://cheatography.com/sapemeg/cheat-sheets/ubuntu-unity-16-04/)
- [GNOME Keyboard Shortcuts](https://wiki.gnome.org/Design/OS/KeyboardShortcuts)
- [KDE Keyboard Shortcuts](https://community.linuxmint.com/tutorial/view/47)

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

## FAQ: Can I run a _shell command_ instead of a keystroke?

**Answer 1**: _Unfortunately **NO**..._

For the following reasons:

1.  We want prioritize "comfort" over functionality, which we deliver through performance in our near-zero-overhead implementation (that's why C++)
2.  Running a new shell command with unpredictable process time will break our unthreaded optimizations (unlike native keystrokes)
3.  There are other gesture libraries that already do this properly (eg. [libinput gestures](https://github.com/bulletmark/libinput-gestures), [Fusuma](https://github.com/iberianpig/fusuma)), we don't want to be a clone of them

That's why it's not possible...

**Answer 2**: _... but actually **YES**!_

Although we don't provide this out of the box in our config, this can definitely be
done with the default bash tools.

## Hack: Shell command on swipe

Running shell commands our **NOT** part of the core features of comfortable-swipe,
but through the default bash tools you can _mimic_ this functionality via our program output.

**Use Case**: _"I want to run `gnome-terminal` if I swipe up with 3 fingers."_

1. Attach the program to the shell:

   ```bash
   comfortable-swipe start --attach
   ```

   Verify it outputs when you swipe left, left, up, right, up with 3 fingers:

   ```bash
   $ comfortable-swipe start --attach
   SWIPE left3
   SWIPE left3
   SWIPE up3
   SWIPE right3
   SWIPE up3
   ...
   ```

1. Filter out the wanted gesture with `grep`.

   In our case, we want 3-finger swipe up which is "SWIPE up3":

   ```bash
   $ comfortable-swipe start --attach | grep --line-buffered "SWIPE up3"
   SWIPE up3
   SWIPE up3
   ...
   ```

   > **Note**: The flag `--line-buffered` ensures the output prints line-by-line.

1. Now we can execute our shell command with `xargs`.

   So if we want "SWIPE up3" to open the terminal,

   ```bash
   comfortable-swipe start --attach | grep "SWIPE up3" --line-buffered | xargs -I@ gnome-terminal
   ```

   > **Note**: The flag `-I@` in xargs substitutes the line "SWIPE xxx" to the charatcter "@", which you can use for your program.

1. _Bonus_: Add to autostart

   Open our autostart file:

   ```bash
   gedit "$(comfortable-swipe autostart path)"
   ```

   Tweak the `Exec` section:

   ```ini
   [Desktop Entry]
   Type=Application
   Exec=comfortable-swipe start
   Name=Comfortable Swipe
   Comment=Comfortable 3/4-finger touchpad gestures
   Hidden=false
   NoDisplay=false
   X-GNOME-Autostart-enabled=true
   ```

   To:

   ```ini
   [Desktop Entry]
   Type=Application
   Exec=comfortable-swipe start --attach | grep "SWIPE up3" --line-buffered | xargs -I@ gnome-terminal
   Name=Comfortable Swipe
   Comment=Comfortable 3/4-finger touchpad gestures
   Hidden=false
   NoDisplay=false
   X-GNOME-Autostart-enabled=true
   ```

1. Log out and log back in.
   You should now be able to run your custom shell commands on startup.

1. _Bonus_: Use `--bare` instead of `--attach` to NOT run keystrokes while swiping

   ```bash
   comfortable-swipe start --bare | grep "SWIPE up3" --line-buffered | xargs -I@ gnome-terminal
   ```

1. _Bonus_: You can pipe multiple gestures with `tee`:

   ```bash
   comfortable-swipe start --attach | \
   tee >(grep "SWIPE left3"  --line-buffered | xargs -I@ <COMMAND>) | \
   tee >(grep "SWIPE left4"  --line-buffered | xargs -I@ <COMMAND>) | \
   tee >(grep "SWIPE right3" --line-buffered | xargs -I@ <COMMAND>) | \
   tee >(grep "SWIPE right4" --line-buffered | xargs -I@ <COMMAND>) | \
   tee >(grep "SWIPE up3"    --line-buffered | xargs -I@ <COMMAND>) | \
   tee >(grep "SWIPE up4"    --line-buffered | xargs -I@ <COMMAND>) | \
   tee >(grep "SWIPE down3"  --line-buffered | xargs -I@ <COMMAND>) | \
   tee >(grep "SWIPE down4"  --line-buffered | xargs -I@ <COMMAND>)
   ```

   Substitute `<COMMAND>` with the shell command of your choice.

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
