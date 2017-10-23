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

1. Make sure `~/.local/bin/` is added to your PATH.
2. Run
    
    ```
    comfortable-swipe start
    ```
    
3. Optional: Automatically run on startup

    ```
    comfortable-swipe-autostart
    ```

### Permissions
Sometimes, you'll need some permissions to read touchpad input data.

1. Find out your permission group with `ls -l /dev/input/event*`
    ```bash
    $ ls -l /dev/input/event*

    crw-rw---- 1 root input 13, 64 Oct 23 23:09 /dev/input/event0
    crw-rw---- 1 root input 13, 65 Oct 23 23:09 /dev/input/event1
    crw-rw---- 1 root input 13, 66 Oct 23 23:09 /dev/input/event2
    crw-rw---- 1 root input 13, 67 Oct 23 23:09 /dev/input/event3
    ```

2. Check the fourth column (e.g. `input`) then run
    ```bash
    sudo gpasswd -a $USER input
    ```

3. ***Important***: Log out / Log back in 

## Configurations
The configuration file is located at `~/.config/comfortable-swipe.conf`.  
Make sure to run `comfortable-swipe restart` after making changes.

Property  | Description | Default Value | Default Behavior
--------- | ----------- | -------------- | -----
left3     | 3-finger swipe left | ctrl+shift+Right | switch to right workspace
right3    | 3-finger swipe right | ctrl+shift+Left | switch to left workspace
up3       | 3-finger swipe up | super+w | window spread
down3     | 3-finger swipe down | super+w | window spread
left4     | 4-finger swipe left | ctrl+alt+shift+Right | move window to right workspace
right4    | 4-finger swipe right | ctrl+alt+shift+Left | move window to left workspace
up4       | 4-finger swipe up | super+d | show desktop
down4     | 4-finger swipe down | super+d | show desktop
threshold | mouse pixels to activate swipe; higher = less sensitive; integers only | 20

## Uninstall
Download the `uninstall` script then run `bash uninstall`  

## Bug Reports
Create an issue [here](https://github.com/Hikari9/comfortable-swipe-ubuntu/issues/new) to report a bug.
