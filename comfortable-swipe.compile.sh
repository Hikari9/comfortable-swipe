#!/bin/sh
g++ $(dirname $0)/comfortable-swipe.cpp -std=c++11 -O2 -lxdo -Wno-unused-result -o $1
