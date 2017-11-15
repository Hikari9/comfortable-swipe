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

1. You'll need some group permissions to read touchpad input data. Run
    ```bash
    sudo gpasswd -a $USER $(ls -l /dev/input/event* | awk '{print $4}' | head --line=1)
    ```
2. ***Important***: After inputing your `sudo` password, log out then log back in
3. Run
    ```
    comfortable-swipe start
    ```
4. Optional: Automatically run on startup
    ```
    comfortable-swipe autostart
    ```
5. Optional: Change keyboard configurations (refer [below](#configurations)).  
    Then restart after making changes with
    ```
    comfortable-swipe restart
    ```

## Configurations
Comfortable swipe makes use of keyboard shortcuts for configurations. The configuration file is located at `/usr/share/comfortable-swipe/comfortable-swipe.conf`. Make sure to run `comfortable-swipe restart` after making changes.

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
Download the `uninstall` script then run `bash uninstall`  

## Bug Reports
Create an issue [here](https://github.com/Hikari9/comfortable-swipe-ubuntu/issues/new) to report a bug.
