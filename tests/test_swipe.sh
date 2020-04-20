#!/bin/bash

set -ex

DIR="$(dirname "$0")"
ROOT="$(dirname "$DIR")"
COMPILER="$ROOT/compile.sh"

# just call abort on error
TEMPOUT="$(mktemp)"
abort () {
    echo "Test aborted"
    exit 1
}

# try to compile main test
# use empty configuration /dev/null
EMPTY_CONFIG="$(mktemp)"
echo "threshold = 0.0" >> "$EMPTY_CONFIG"
"$COMPILER" "$ROOT/comfortable-swipe-main.cpp" -o "$TEMPOUT" \
    -DCOMFORTABLE_SWIPE_AUTOSTART="\"$ROOT/comfortable-swipe.desktop\"" \
    -DCOMFORTABLE_SWIPE_CONFIG="\"$EMPTY_CONFIG\"" \
    || abort
chmod +x "$TEMPOUT"

set +x

# try to run start, then wait for the user to swipe
echo "Simulating swipe..."

# get output result
OUTPUT="$(mktemp)"
"$TEMPOUT" <<EOF > "$OUTPUT"
 event7   GESTURE_SWIPE_BEGIN  +1.72s   3
 event7   GESTURE_SWIPE_UPDATE  +1.72s  3 -12.26/-0.42 (-33.14/-1.12 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.73s  3 -14.08/ 0.00 (-38.06/ 0.00 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.74s  3 -15.78/-0.42 (-42.65/-1.12 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.75s  3 -16.63/-0.14 (-44.95/-0.37 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.75s  3 -16.63/-0.42 (-44.95/-1.12 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.76s  3 -16.39/ 0.14 (-44.29/ 0.37 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.77s  3 -15.66/ 0.28 (-42.32/ 0.75 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.78s  3 -13.96/ 0.55 (-37.73/ 1.50 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.78s  3 -12.38/ 0.28 (-33.46/ 0.75 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.79s  3 -10.56/ 0.55 (-28.54/ 1.50 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.80s  3 -8.86/ 0.69 (-23.95/ 1.87 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.81s  3 -6.92/ 1.53 (-18.70/ 4.12 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.81s  3 -5.10/ 1.53 (-13.78/ 4.12 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.82s  3 -4.13/ 1.39 (-11.15/ 3.75 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.83s  3 -3.40/ 0.97 (-9.19/ 2.62 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.84s  3 -2.43/ 0.97 (-6.56/ 2.62 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.84s  3 -1.82/ 0.69 (-4.92/ 1.87 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.85s  3 -0.97/ 0.69 (-2.62/ 1.87 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.86s  3 -0.36/ 0.69 (-0.98/ 1.87 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.87s  3 -0.24/ 0.42 (-0.66/ 1.12 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.88s  3  0.23/ 0.26 ( 0.66/ 0.75 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.88s  3  0.99/ 0.13 ( 2.95/ 0.37 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.89s  3  2.31/ 0.42 ( 6.23/ 1.12 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.90s  3  3.88/ 0.97 (10.50/ 2.62 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.91s  3  7.65/ 0.55 (20.67/ 1.50 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.91s  3 12.26/ 0.55 (33.14/ 1.50 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.92s  3 17.36/-0.42 (46.92/-1.12 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.93s  3 21.73/-1.25 (58.73/-3.37 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.94s  3 24.64/-2.64 (66.60/-7.12 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.94s  3 26.95/-3.75 (72.83/-10.12 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.95s  3 27.80/-4.72 (75.13/-12.75 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.96s  3 27.07/-4.86 (73.16/-13.12 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.97s  3 25.49/-5.27 (68.90/-14.25 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.97s  3 23.06/-4.72 (62.34/-12.75 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.98s  3 20.15/-4.16 (54.46/-11.25 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +1.99s  3 17.24/-3.33 (46.59/-9.00 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +2.00s  3 13.84/-2.64 (37.40/-7.12 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +2.00s  3 10.80/-1.80 (29.20/-4.87 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +2.01s  3  7.77/-0.83 (21.00/-2.25 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +2.02s  3  5.46/ 0.14 (14.76/ 0.37 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +2.03s  3  3.03/ 0.28 ( 8.20/ 0.75 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +2.04s  3  1.82/ 0.00 ( 4.92/ 0.00 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +2.04s  3  0.61/-0.28 ( 1.64/-0.75 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +2.05s  3  0.24/-0.14 ( 0.66/-0.37 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +2.06s  3 -0.22/ 0.13 (-0.66/ 0.37 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +2.07s  3  0.00/ 0.06 ( 0.00/ 0.37 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +2.09s  3 -0.05/ 0.06 (-0.33/ 0.37 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +2.10s  3 -0.05/ 0.00 (-0.33/ 0.00 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +2.10s  3 -0.05/ 0.05 (-0.33/ 0.37 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +2.11s  3 -0.05/ 0.06 (-0.33/ 0.37 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +2.12s  3  0.05/ 0.00 ( 0.33/ 0.00 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +2.13s  3 -0.11/ 0.00 (-0.66/ 0.00 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +2.13s  3  0.00/ 0.07 ( 0.00/ 0.37 unaccelerated)
 event7   GESTURE_SWIPE_UPDATE  +2.14s  3 -2.41/-0.50 (-7.22/-1.50 unaccelerated)
 event7   GESTURE_SWIPE_END  +2.19s     3
EOF

EXPECTED_OUTPUT="SWIPE left3
SWIPE right3"

echo "$EXPECTED_OUTPUT"

if [[ "$(cat "$OUTPUT")" == "$EXPECTED_OUTPUT" ]]; then
    echo "PASSED"
else
    echo "Did not match expected output:" >&2
    echo "$EXPECTED_OUTPUT" >&2
    abort
fi
