# Ubuntu-Comfortable-3-Finger-Swipe
Author: Rico Tiongson  

Comfortable 3-finger and 4-finger swipe gestures. Uses Xdotool in native C++. For Ubuntu 14.04 LTS and beyond.

## Installation
1. `sudo apt install libinput-tools libinput-dev libxdo-dev`
2. `git clone https://github.com/Hikari9/Ubuntu-Comfortable-3-Finger-Swipe.git`
3. `cd Ubuntu-Comfortable-3-Finger-Swipe`
4. Tweak `src/comfortable-swipe.cpp` to fit keyboard shortcuts of your gestures
5. `bash install`

## How to Run
1. `comfortable-swipe-serve`
2. Flick away!

### Input Permissions
Sometimes, you'll need some permissions to read touchpad input data. Perform these steps to solve the permission issue:

1. `sudo gpasswd -a input $USER`
2. Log out / log back in

## Optional: Add to Startup Applications
1. `gnome-session-properties`
2. Click `Add`, then enter `comfortable-swipe-serve`

  ![Comfortable Swipe](img/sample.png)