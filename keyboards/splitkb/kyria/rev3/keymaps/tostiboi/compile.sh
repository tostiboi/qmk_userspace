#!/bin/bash

# Navigate to the QMK firmware directory

qmk compile -e CONVERT_TO=liatris -kb splitkb/kyria/rev3 -km tostiboi
