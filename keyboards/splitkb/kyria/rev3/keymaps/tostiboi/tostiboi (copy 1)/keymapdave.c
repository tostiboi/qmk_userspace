/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
 * 
 * 
 */



#include QMK_KEYBOARD_H
#include <stdio.h>
#include "modular_bongocat.h"

enum layers
{
    _HOOGENDOORN = 0,
    _MEDIA,
    _MOVE,
    _MOUSE,
    _SYM,
    _NUM,
    _FUN,
    _RGB,
};


uint8_t base_layers[5] = {_HOOGENDOORN, _MEDIA, _MOVE, _MOUSE, _SYM};
uint8_t current_base_layer = _HOOGENDOORN;

// OLED setup
#define IDLE_FRAMES 5
#define IDLE_SPEED 30
#define TAP_FRAMES 2
#define TAP_SPEED 40
#define ANIM_FRAME_DURATION 200
#define ANIM_SIZE 512

bool gui_on = true;
//char wpm_str[8];
//uint32_t anim_timer = 0;
//uint32_t anim_sleep = 0;
//uint8_t current_idle_frame = 0;
//uint8_t current_tap_frame = 0;

//static long int oled_timeout = 600000; // 10 minutes


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |Ctrl/' "|.ui.uoeooupyaienha,/kq.uopyy.uopyaienh;,/kqxlb
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | [ {  |CapsLk|  |F-keys|  ] } |   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Adjust| LGUI | LAlt/| Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
 *                        |      |      | Enter|      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_HOOGENDOORN] = LAYOUT(
     KC_ESC, LT(7,KC_DOT), KC_U,         KC_O,         KC_P,         KC_Y,                                               KC_X,           KC_C,         KC_L,         KC_B,         KC_V,         KC_NO,
     KC_ESC, LGUI_T(KC_A), LALT_T(KC_I), LCTL_T(KC_E), LSFT_T(KC_N), KC_H,                                               KC_M,           LSFT_T(KC_D), LCTL_T(KC_R), LALT_T(KC_T), LGUI_T(KC_S), KC_NO,
     KC_ESC, KC_SCLN,      LT(0,KC_COMM),LT(0,KC_SLSH),LT(0,KC_K),   KC_Q,        KC_NO  , KC_NO,   LT(7,KC_ESC), KC_NO,        KC_F,           KC_G,         KC_W,         KC_J,         KC_Z,         KC_NO,
                                         KC_NO , LT(1,KC_ESC), LT(2,KC_SPC), LT(3,KC_TAB), KC_NO,   KC_NO, LT(4,KC_ENT), LT(5,KC_BSPC),  LT(6,KC_DEL), KC_NO
    ),
/*
 * Base Layer: Dvorak
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   | ' "  | , <  | . >  |   P  |   Y  |                              |   F  |   G  |   C  |   R  |   L  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   O  |   E  |   U  |   I  |                              |   D  |   H  |   T  |   N  |   S  |Ctrl/- _|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift | ; :  |   Q  |   J  |   K  |   X  | [ {  |CapsLk|  |F-keys|  ] } |   B  |   M  |   W  |   V  |   Z  | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Adjust| LGUI | LAlt/| Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
 *                        |      |      | Enter|      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
 
    [_MEDIA] = LAYOUT(
     KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
     KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                    KC_NO,    KC_NO,    KC_MPRV,  KC_VOLD,  KC_VOLU,  KC_MNXT, 
     KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO,  KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                           KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO,  KC_NO,    KC_MSTP,KC_MPLY,   KC_MUTE,  KC_NO   
    ),


    [_MOVE] = LAYOUT(
     KC_NO,  KC_UNDO,  KC_CUT, KC_COPY,  KC_PSTE,  KC_AGIN,                              KC_AGIN,  KC_PSTE,  KC_COPY,  KC_CUT,   KC_UNDO, KC_NO, 
     KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO,                                KC_CAPS,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT, KC_NO, 
     KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,  KC_INS,   KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,  KC_NO,
                               KC_NO,    KC_NO,    KC_NO,   KC_NO, KC_NO, KC_NO, KC_ENT, KC_BSPC,  KC_DEL,   KC_NO
    ),

    [_MOUSE] = LAYOUT(
    KC_NO, KC_NO, KC_NO, KC_NO, KC_BRIU,  KC_NO,                                      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_BRID,  KC_NO,                                      KC_NO,    KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R, KC_NO, 
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO,  KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_WH_L,  KC_WH_D,  KC_WH_U,  KC_WH_R, KC_NO,
                         KC_NO, KC_NO,    KC_NO,  KC_NO,    KC_NO,  KC_NO,  KC_BTN1,  KC_BTN3,  KC_BTN2,  KC_NO
    ),

    
  [_SYM] = LAYOUT(
    KC_NO,KC_LCBR, KC_AMPR, KC_ASTR,  KC_LPRN, KC_RCBR,                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
    KC_NO,KC_COLN, KC_DLR,  KC_PERC,  KC_CIRC, KC_PLUS,                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
    KC_NO,KC_EXLM, KC_AT,   KC_HASH,  KC_BSLS, KC_PIPE, KC_NO,    KC_NO, KC_NO, KC_NO,KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
                            KC_NO,    KC_LPRN, KC_RPRN, KC_UNDS,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),

  [_NUM] = LAYOUT(
    KC_NO, KC_LBRC,  KC_7,   KC_8,   KC_9,   KC_RBRC,                                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
    KC_NO, KC_SCLN,  KC_4,   KC_5,   KC_6,   KC_EQL,                                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
    KC_NO, KC_GRV,   KC_1,   KC_2,   KC_3,   KC_BSLS,  KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
                             KC_NO,  KC_DOT, KC_0,     KC_MINS,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),

  [_FUN] = LAYOUT(
    KC_NO,  KC_F12, KC_F7, KC_F8,   KC_F9,  KC_PSCR,                              KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, DB_TOGG, 
    KC_NO,  KC_F11, KC_F4, KC_F5,   KC_F6,  KC_SCRL,                              KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
    KC_NO,  KC_F10, KC_F1, KC_F2,   KC_F3,  KC_PAUS,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                           KC_NO,   KC_APP, KC_SPC,   KC_TAB,KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ), 


  [_RGB] = LAYOUT(
     KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
     KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD,    KC_NO, 
     KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO,  KC_NO,    KC_NO,   KC_NO,    RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,    KC_NO,
                           KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO,  KC_NO,    KC_MSTP,KC_MPLY,   KC_MUTE,  KC_NO   
    )
};

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

// OLED width
#define WIDTH 128

oled_rotation_t oled_init_user(oled_rotation_t rotation)
{
	return OLED_ROTATION_180;
}

static void render_current_layer(void)
{
    if(current_base_layer == _HOOGENDOORN)
        oled_write_P(PSTR("Colemak-DH\n"), false);
    else if(current_base_layer == _MEDIA)
        oled_write_P(PSTR("Qwertz\n"), false);
    else if (current_base_layer == _MOVE)
        oled_write_P(PSTR("Gaming\n"), false);
}

/**
 ** return: if true, start scrolling, to reduce burn in
 ** return: if false, content changed, do not scroll
 */
static bool render_status(void)
{
    static uint8_t scroll_timer = 0;

    // return value bool, scroll or not
    // QMK Logo and version information
    // render_qmk_logo();
    oled_write_P(PSTR("Tostiboi\n"), false);
    uint8_t highest_layer = get_highest_layer(layer_state);

    // Func Layer can cycle between base Layers, Display new Layer
    if(highest_layer != _FUN)
        oled_write_P(PSTR("\n"), false);
    else
    {
        oled_write_P(PSTR("New Base: "), false);
        render_current_layer();
        scroll_timer = 0;
    }

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Lay: "), false);
    if(highest_layer == _FUN)
    {
        oled_write_P(PSTR("3: Symbols\n"), false);
        scroll_timer = 0;
    }
    else if(highest_layer == _NUM)
    {
        oled_write_P(PSTR("4: Nav, Num\n"), false);
        scroll_timer = 0;
    }
    else if(highest_layer == _SYM)
    {
        oled_write_P(PSTR("Func: F,Med,RGB\n"), false);
        scroll_timer = 0;
    }
    else
    {
        render_current_layer();
    }

    if (scroll_timer < 255)
        scroll_timer++;

    if (scroll_timer < 255)
        return false;
    else
        return true;
}

bool oled_task_user(void)
{

    static bool logos_rendered = false;
    // normal case
    if (is_keyboard_master())

    {
        // Will scroll OLED, if "home" screen was displayed for 255 refreshes
        // TODO: random vertical offset
        if(!logos_rendered)
        {
            #ifdef QMK_LOGO_ENABLE
            render_short_array_pos(qmk_logo, 0, 0, qmk_logo_width);
            #endif
            #ifdef KYRIA_LOGO_ENABLE
            render_short_array_pos(kyria_logo, WIDTH-kyria_logo_width, -6, kyria_logo_width);
            #endif
            logos_rendered = true;

        }
        oled_set_cursor(0,4);
        bool render_stat_ret = render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
        if (render_stat_ret)
            oled_scroll_left();
        else
            oled_scroll_off();
    } else
    {
        render_anim();
        render_wpm();
    }
    return false;
}

void keyboard_pre_init_user(void) {
  // Set our LED pin as output
  setPinOutput(24);
  // Turn the LED off
  // (Due to technical reasons, high is off and low is on)
  writePinHigh(24);
}

