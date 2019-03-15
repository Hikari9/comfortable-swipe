#!/bin/sh
dir="$(dirname $0)"
g++ "$dir/comfortable-swipe.cpp" \
    -o "$1" \
    -std=c++11 \
    -O2 -lxdo -Wno-unused-result \
    -DCOMFORTABLE_SWIPE_VERSION="\"$(cat $dir/VERSION | tr -d '[:space:]')\""
