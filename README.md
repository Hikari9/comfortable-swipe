# Comfortable Swipe (Ubuntu)
Comfortable 3-finger (and 4-finger) swipe gestures for Ubuntu 14.04 LTS+.

by Rico Tiongson     
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)  

## Installation
1. `sudo apt install libinput-tools libinput-dev libxdo-dev`
2. `git clone https://github.com/Hikari9/comfortable-swipe-ubuntu.git`
3. `cd comfortable-swipe-ubuntu`
4. Tweak `src/comfortable-swipe.cpp` to fit keyboard shortcuts of your gestures
5. `bash install`

## How to Run
1. `comfortable-swipe start`
2. Flick away!

### Permissions
Sometimes, you'll need some permissions to read touchpad input data. Perform these steps to solve the permission issue:

1. `sudo gpasswd -a $USER input`
2. Log out / log back in

## Optional: Add to Startup Applications
1. `gnome-session-properties`
2. Add, then enter:  
    ![Add to Startup Applications](img/sample.png)

3. Save

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

## Bug Reports
Please create an issue to report a bug.
