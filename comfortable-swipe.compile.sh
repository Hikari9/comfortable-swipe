#!/bin/sh
dir="$(dirname $0)"
g++ "$dir/comfortable-swipe.cpp" -std=c++11 -O2 -lxdo -Wno-unused-result -o -DCOMFORTABLE_SWIPE_VERSION="$(cat $dir/VERSION)" "$1"
