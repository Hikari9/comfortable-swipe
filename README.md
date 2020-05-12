# Comfortable Swipe (Ubuntu)

[![comfortable-swipe version](https://img.shields.io/github/release/Hikari9/comfortable-swipe.svg?label=comfortable-swipe&color=orange)](https://github.com/Hikari9/comfortable-swipe/releases)
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

Comfortable, seamless, and fast 3-finger (and 4-finger) touchpad swipe gestures for Ubuntu 14.04 LTS and beyond. May work for other Linux distros that support `libinput`.

> **_New in Version 1.1.0_**: Added mouse gestures, see [#mouse-gestures-experimental](#mouse-gestures-experimental)

> **_New in Version 1.2.0_**: Autostart now switched ON by default

## Installation

1. Install git and g++ &geq; 7.5

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

1. Start the Program

   ```
   comfortable-swipe start
   ```

   You will see this output:

   ```
   $ comfortable-swipe start
   Comfortable swipe is RUNNING in the background
   ```

1. (Optional) Toggle autostart

   ```bash
   comfortable-swipe autostart on
   ```

1. (Optional) Stop the Program

   ```
   comfortable-swipe stop
   ```

1. (Optional) See program status

   ```bash
   comfortable-swipe status
   ```

   Example:

   ```
   $ comfortable-swipe status

   Autostart is ON
   Program is RUNNING
   --------------------
   Configuration: /home/user/.config/comfortable-swipe.conf
       left3 is   VALID (ctrl+super+Right)
       left4 is   VALID (ctrl+super+shift+Right)
      right3 is   VALID (ctrl+super+Left)
      right4 is   VALID (ctrl+super+shift+Left)
         up3 is   VALID (ctrl+F12)
         up4 is   VALID (super+d)
       down3 is   VALID (ctrl+F12)
       down4 is   VALID (super+d)
   threshold is   VALID (1.0)
      mouse3 is  NOTSET
      mouse4 is  NOTSET
   ```

1. (Optional) Get config

   ```
   comfortable-swipe <PROPERTY>
   ```

   ```bash
   comfortable-swipe left3
   comfortable-swipe left4
   comfortable-swipe right3
   comfortable-swipe right4
   comfortable-swipe up3
   comfortable-swipe up4
   comfortable-swipe down3
   comfortable-swipe down4
   comfortable-swipe threshold
   comfortable-swipe mouse3
   comfortable-swipe mouse4
   ```

1. (Optional) Set config

   ```bash
   comfortable-swipe <PROPERTY> [=] <VALUES>
   ```

   ```bash
   comfortable-swipe left3 = super+Right
   comfortable-swipe right3 = super+Left
   comfortable-swipe right4 = ctrl+alt+Left
   comfortable-swipe down4 = super+d
   comfortable-swipe up3 = ctrl+shift+Up
   ```

<details>
<summary><b>Other Commands</b></summary>

1. All Configuration commands

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

1. Autostart commands

   ```bash
   comfortable-swipe autostart on
   comfortable-swipe autostart off
   comfortable-swipe autostart toggle
   comfortable-swipe autostart status
   comfortable-swipe autostart path
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

1. Test output with `--bare` to attach without actually swiping

   ```bash
   $ comfortable-swipe start --bare
   SWIPE left3
   SWIPE left4
   SWIPE right3
   SWIPE up3
   ...
   ```

1. Debug

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

</details>

## Gesture Configurations

The default configuration file is located at `~/.config/comfortable-swipe.conf`.
Comfortable swipe makes use of **keyboard shortcuts** to perform swipes, through `xdotool`.

Set a property directly with:

```
comfortable-swipe <PROPERTY> [=] <VALUE>
```

Or edit the configuration file manually:

```
gedit ~/.config/comfortable-swipe.conf
```

After editing, make sure to restart with `comfortable-swipe start`.

> **Warning**: For v1.1.0 below, the configuration file is located at
> `/usr/local/share/comfortable-swipe/comfortable-swipe.conf`

> **Note**: You can locate the absolute path to your configuration by running: `comfortable-swipe config path`

## Configuration Reference

| Property  |                                 Value                                  | Examples                                                                           |
| --------- | :--------------------------------------------------------------------: | ---------------------------------------------------------------------------------- |
| left3     |                          3-finger swipe left                           | ctrl+alt+Right                                                                     |
| left4     |                          4-finger swipe left                           | ctrl+alt+shift+Right                                                               |
| right3    |                          3-finger swipe right                          | ctrl+alt+Left                                                                      |
| right4    |                          4-finger swipe right                          | ctrl+alt+shift+Left                                                                |
| up3       |                           3-finger swipe up                            | ctrl+alt+Down                                                                      |
| up4       |                           4-finger swipe up                            | ctrl+alt+shift+Down                                                                |
| down3     |                          3-finger swipe down                           | ctrl+alt+Up                                                                        |
| down4     |                          4-finger swipe down                           | ctrl+alt+shift+Up                                                                  |
| threshold | mouse movement pixels that trigger a swipe (can be as large as 1000.0) | 0.0 / 240.0 / 1000.0                                                               |
| mouse3    |             mouses a mouse button when 3 fingers are down              | button1 / move / scroll<br> _(see [Mouse Gestures](#mouse-gestures-experimental))_ |  |
| mouse4    |             mouses a mouse button when 4 fingers are down              | button1 / move / scroll <br> _(see [Mouse Gestures](#mouse-gestures-experimental)_ |

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

- [DEFKEY - All Linux keyboard shortcuts](https://defkey.com/)
- [Unity Keyboard Shortcuts](https://cheatography.com/sapemeg/cheat-sheets/ubuntu-unity-16-04/)
- [GNOME Keyboard Shortcuts](https://wiki.gnome.org/Design/OS/KeyboardShortcuts)
- [KDE Keyboard Shortcuts](https://community.linuxmint.com/tutorial/view/47)
- [PopOS Keyboard Shortcuts](https://support.system76.com/articles/pop-keyboard-shortcuts/)

## Known Issues: Pop!_OS 20.04+

Pop!_OS 20.04+ may be sensitive to capitalization  (#76, #82). Make sure to capitalize every first letter:

```bash
# Pop!_OS
comfortable-swipe up3 = Super+Ctrl+Down
comfortable-swipe down3 = Super+Ctrl+Up
```

## Example Configurations

This section includes some example configurations which you can use for your swipe experience.

1. Switch workspace (horizontal)

   ```bash
   # Ubuntu flavors + GNOME
   comfortable-swipe left3 = ctrl+alt+Right
   comfortable-swipe right3 = ctrl+alt+Left
   ```

1. Switch workspace (vertical)

   ```bash
   # Ubuntu flavors + GNOME
   comfortable-swipe up3 = ctrl+alt+Down
   comfortable-swipe down3 = ctrl+alt+Up
   ```

   ```bash
   # GNOME alt.
   comfortable-swipe up3 = super+PgDown
   comfortable-swipe down3 = super+PgUp
   ```

   ```bash
   # Pop OS
   comfortable-swipe up3 = Super+Ctrl+Down
   comfortable-swipe down3 = Super+Ctrl+Up
   ```

1. Move window to workspace (horizontal)

   ```bash
   # Ubuntu flavors + GNOME + Kali
   comfortable-swipe left4 = ctrl+alt+shift+Right
   comfortable-swipe right4 = ctrl+alt+shift+Left
   ```

   ```bash
   # Elementary OS
   comfortable-swipe left4 = super+alt+Right
   comfortable-swipe right4 = super+alt+Left
   ```

1. Move window to workspace (vertical)

   ```bash
   # Ubuntu flavors + GNOME + Kali
   comfortable-swipe up4 = ctrl+alt+shift+Down
   comfortable-swipe down4 = ctrl+alt+shift+Up
   ```

   ```bash
   # GNOME alt.
   comfortable-swipe up4 = super+shift+PgDown
   comfortable-swipe down4 = super+shift+PgUp
   ```

1. Move window to other monitor

   ```bash
   # Ubuntu flavors + GNOME
   comfortable-swipe left4 = super+shift+Right
   comfortable-swipe right4 = super+shift+Left
   ```

1. Toggle workspace overview

   ```bash
   # Ubuntu flavors + Elementary OS
   comfortable-swipe up3 = super+s
   ```

   ```bash
   # Elementary OS (all workspaces)
   comfortable-swipe up4 = super+a
   ```

1. Show desktop

   ```bash
   # Ubuntu flavors
   comfortable-swipe down3 = ctrl+super+d
   ```

   ```bash
   # Linux Mint
   comfortable-swipe down3 = super+d
   ```

   ```bash
   # Kali
   comfortable-swipe down3 = ctrl+alt+d
   ```

   ```bash
   # KDE
   comfortable-swipe down3 = ctrl+F12
   ```

1. Snap windows to the left/right

   ```bash
   comfortable-swipe left3 = super+Left
   comfortable-swipe right3 = super+Right
   ```

1. Toggle maximize

   ```bash
   comfortable-swipe up3 = super+Up
   ```

1. Toggle minimize

   ```bash
   comfortable-swipe down3 = super+Down
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

> **Tip**: You can clear mouse gestures by setting them blank
>
> ```
> comfortable-swipe mouse3 =
> comfortable-swipe mouse4 =
> ```

Examples:

✔️ swipes OK
⭕ swipes DISABLED

- 3/4-finger drag ⭕

  ```bash
  comfortable-swipe mouse3 = button1
  comfortable-swipe mouse4 = button1
  ```

  You can also use `button2` for middle click and `button3` for right click.

- 3/4-finger natural scroll ⭕

  ```bash
  comfortable-swipe mouse3 = scroll
  comfortable-swipe mouse4 = scroll
  ```

- 3/4-finger reverse scroll ⭕

  ```bash
  comfortable-swipe mouse3 = scroll_reverse
  comfortable-swipe mouse4 = scroll_reverse
  ```

- Move 3/4-fingers with the cursor ✔️

  ```bash
  comfortable-swipe mouse3 = move
  comfortable-swipe mouse4 = move
  ```

> **Warning**: Some mouse configuration will **disable up/left/right/down behavior** to avoid gesture conflicts. The logic of this will be improved in the future.

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

1.  We want prioritize "comfort" over functionality, which we deliver through performance in our negligible-overhead implementation (that's why C++)
1.  There are other gesture libraries that already do this properly (eg. [libinput gestures](https://github.com/bulletmark/libinput-gestures), [Fusuma](https://github.com/iberianpig/fusuma)), we don't want to be a clone of them
1.  Running a new shell command with unpredictable process time will break our unthreaded optimizations (unlike native keystrokes)

That's why it's not possible... or not?

**Answer 2**: _... but actually **IT'S POSSIBLE**!_

Although we don't provide this out of the box in our config, this can definitely be
done with the default bash tools.

## Hack: Shell command on swipe

Running shell commands our **NOT** part of the core features of comfortable-swipe,
but through the default bash tools you can _mimic_ this functionality via our program output.

<details>
<summary> <b>Use Case</b>: <i>"I want to run <code>gnome-terminal</code> if I swipe up with 3 fingers."</i>
</summary>

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

</details>

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
