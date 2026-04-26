/* Copyright 2022 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef RGB_MATRIX_ENABLE
#    define ENABLE_RGB_MATRIX_BREATHING
#    define ENABLE_RGB_MATRIX_RAINBOW_MOOD
#    define ENABLE_RGB_MATRIX_RAINBOW_SWIRL
#    define ENABLE_RGB_MATRIX_SNAKE
#    define ENABLE_RGB_MATRIX_KNIGHT
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#    define ENABLE_RGB_MATRIX_TWINKLE
#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 8
#    define RGB_MATRIX_VAL_STEP 8
#    ifndef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    	define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#    endif
#endif

// Most tactile encoders have detents every 4 stages
#define ENCODER_RESOLUTION 4
#define FORCE_NKRO
#define ONESHOT_TIMEOUT 8000
#define TAPPING_TERM 501
#define PERMISSIVE_HOLD
#define RETRO_TAPPING
#define COMBO_COUNT 16
#define COMBO_TERM 60
#define COMBO_VARIABLE_LEN

