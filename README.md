# Comfortable Swipe (Ubuntu)
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)  

Comfortable, seamless, and fast 3-finger (and 4-finger) touchpad swipe gestures for Ubuntu 14.04 LTS and beyond. May work for other Linux distros that support `libinput`.

## Installation

1. Install `libinput-tools` and `libxdo-dev`
    
    ```bash
    sudo apt-get install libinput-tools libxdo-dev
    ```

2. Clone this repository
    
    ```bash
    git clone https://github.com/Hikari9/comfortable-swipe-ubuntu.git
    cd comfortable-swipe-ubuntu
    ```

3. Install

    ```bash
    bash install
    ```

4. You may delete the downloaded `comfortable-swipe-ubuntu` folder after installation.

## How to Run

Comfortable swipe should already be running as a service upon installation. Some notes:

- The program makes use of **keyboard gestures** for swiping (e.g. `ctrl+alt+Right`)
- By default, comfortable swipe uses Ubuntu workspace shortcuts (see [configurations](#configurations)).

Useful References:

- [Xdotool keycodes](https://www.linux.org/threads/xdotool-keyboard.10528/)
- [How to turn on Workspaces?](https://askubuntu.com/questions/260510/how-do-i-turn-on-workspaces-why-do-i-only-have-one-workspace)
- [How to set keyboard shortcuts in Ubuntu](https://help.ubuntu.com/stable/ubuntu-help/keyboard-shortcuts-set.html)

### Configurations
The configuration file is located at `/usr/local/share/comfortable-swipe.conf`.
Run `comfortable-swipe restart` after making changes.

Property  | Description | Default Value | Default Behavior
--------- | ----------- | -------------- | -----
threshold | mouse pixels to activate swipe; higher = less sensitive; floating-point | 0.0
left3     | 3-finger swipe left | ctrl+shift+Right | switch to right workspace
left4     | 4-finger swipe left | ctrl+alt+shift+Right | move window to right workspace
right3    | 3-finger swipe right | ctrl+shift+Left | switch to left workspace
right4    | 4-finger swipe right | ctrl+alt+shift+Left | move window to left workspace
up3       | 3-finger swipe up | ctrl+shift+Down | switch to bottom workspace
up4       | 4-finger swipe up | ctrl+alt+shift+Down | move window to bottom workspace
down3     | 3-finger swipe down | ctrl+shift+Down | switch to above workspace
down4     | 4-finger swipe down | ctrl+alt+shift+Up | move window to above workpace

## Uninstall
Clone the repository then run `bash uninstall`.

## Bug Reports
Create an issue [here](https://github.com/Hikari9/comfortable-swipe-ubuntu/issues/new) to report a bug. Please make sure
to add the following to your issue:

1. Content of `.log` (found in the cloned folder)
2. Output of `sudo systemctl status comfortable-swipe.service`
