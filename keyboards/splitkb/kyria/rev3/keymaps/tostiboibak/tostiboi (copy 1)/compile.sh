#!/bin/bash

# Navigate to the QMK firmware directory
cd /home/joost/qmk_firmware

qmk compile -e CONVERT_TO=promicro_rp2040 -kb splitkb/kyria/rev3 -km tostiboi
