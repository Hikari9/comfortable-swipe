#!/bin/bash

dir="$(dirname $0)"
version="$(cat "$dir/VERSION" | tr -d '[:space:]')"
libraries=-lxdo -lconfig++

exec g++ $@ \
    -std=c++14 \
    -O2 \
    -lxdo \
    -lconfig++ \
    -Wno-unused-result \
    -DCOMFORTABLE_SWIPE_VERSION="\"$version\""
