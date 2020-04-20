#!/bin/bash
# main compile script
# usage: ./compile.sh *.cpp
set -e

DIR="$(dirname $0)"
VERSION="$(cat "$DIR/VERSION" | tr -d '[:space:]')"

g++ "$@" -std=c++14 -O2 -Wall -lxdo -linih -DCOMFORTABLE_SWIPE_VERSION="\"$VERSION\""
