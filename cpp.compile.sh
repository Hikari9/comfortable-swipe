#!/bin/bash

dir="$(dirname $0)"
version="$(cat "$dir/VERSION" | tr -d '[:space:]')"

exec g++ $@ \
    -std=c++11 \
    -O2 -lxdo -Wno-unused-result \
    -DCOMFORTABLE_SWIPE_VERSION="\"$version\""
