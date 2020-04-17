#!/bin/bash

set -ex

DIR="$(dirname "$0")"
root="$(dirname "$DIR")"
compiler="$root/cpp.compile.sh"
command_line="$root/command_line.cpp"
module="$root/comfortable_swipe"

# just call abort on error
tempout="$(mktemp)"
abort () {
    rm "$tempout"
    echo "Test aborted"
    exit 1
}

# try to compile every cpp/hpp file in module
# header files first
# then compile cpp files
# finally, compile command line
shopt -s nullglob
for cpp in \
    "$module"/**/*.h \
    "$module"/**/*.hpp \
    "$module"/**/*.cpp \
    "$module"/lib \
    "$command_line"
do
    "$compiler" -c "$cpp" -o "$tempout" || abort
done
