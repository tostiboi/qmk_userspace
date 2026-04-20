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
#include "g/keymap_combo.h"
#include <stdio.h>



/* // OLED setup
#define IDLE_FRAMES 5
#define ALLIANZ_FRAMES 209
#define IDLE_SPEED 30
#define TAP_FRAMES 2
#define TAP_SPEED 40
#define ANIM_FRAME_DURATION 200
#define ANIM_SIZE 1024

bool gui_on = true;
char wpm_str[10];
uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;
uint8_t current_idle_frame = 0;
uint8_t current_tap_frame = 0;

static long int oled_timeout = 600000; // 10 minutes */

enum layer_names {
    Base,
    Media,
    Nav,
    Mouse,
    Sym,
    Num,
    Func,
    GUI,
    _FROG,
    _SYM,
    _NUM,
    _EXT,
};

// Layer Mode aliases
#define BSP_EXT LT(_EXT,KC_BSPC)
#define OSYM OSL(_SYM)
#define ONUM OSL(_NUM)
#define OSFT OSM(MOD_LSFT)
#define OGUI OSM(MOD_LGUI)
#define ATAB LCA(KC_TAB)
#define OALT OSM(MOD_LALT)
#define OCTL OSM(MOD_LCTL)
#define CBSP C(KC_BSPC)

enum custom_keycodes {
    ABSDEL = SAFE_RANGE,
    ABSCPY,
    ABSPST,
};




// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   "  |   U  |   O  |   P  |   Y  |                              |   X  |   C  |   L  |   B  |   V  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   I  |   E  |   N  |   H  |                              |   M  |   D  |   R  |   T  |   S  |Ctrl/' "|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   /  |   .  |   ,  |   K  |   Q  | Num  | Sym  |  | Sym  | Num  |   F  |   G  |   W  |   J  |   Z  | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |WHEEL |      | Esc  | Space| Tab  |  | Ent  | Bksp | Del  |      |WHEEL |
 *                        |      |      | Media| Nav  | Mouse|  | Sym  | Num  | Func |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [Base] = LAYOUT(
     KC_TAB, LT(7,KC_QUOTE),KC_U,           KC_O,           KC_P,           KC_Y,                                                                           KC_X,         KC_C,         KC_L,         KC_B,         KC_V,         KC_BSPC,
     KC_LCTL, LGUI_T(KC_A),  LALT_T(KC_I),   LCTL_T(KC_E),   LSFT_T(KC_N),   KC_H,                                                                           KC_M,         LSFT_T(KC_D), LCTL_T(KC_R), LALT_T(KC_T), LGUI_T(KC_S), KC_RCTL,
     KC_LSFT, KC_SLSH,       LT(0,KC_DOT),   LT(0,KC_COMMA), LT(0,KC_K),     KC_Q,           TG(5),          TG(4),   TG(4),   TG(5),          KC_F,         KC_G,         KC_W,         KC_J,         KC_Z,         KC_RSFT,
                                            KC_NO,          KC_NO,          LT(1,KC_ESC),   LT(2,KC_SPC),   LT(3,KC_TAB),   LT(4,KC_ENT),   LT(5,KC_BSPC),  LT(6,KC_DEL), KC_NO,        KC_NO
    ),
 
    [Media] = LAYOUT(
     KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
     KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                    KC_NO,    KC_NO,    KC_MPRV,  KC_VOLD,  KC_VOLU,  KC_MNXT, 
     KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO,  KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                           KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO,  KC_MSTP,  KC_MPLY, KC_MUTE,  KC_NO,    KC_NO   
    ),


    [Nav] = LAYOUT(
     DF(_FROG),  KC_UNDO,  KC_CUT, KC_COPY,  KC_PSTE,  KC_AGIN,                              KC_AGIN,  KC_PSTE,  KC_COPY,  KC_CUT,   KC_UNDO, KC_NO, 
     KC_NO,  KC_NO,    KC_NO,  ABSCPY,   ABSPST,   ABSDEL,                                KC_CAPS,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT, KC_NO, 
     KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,  KC_INS,   KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,  KC_NO,
                               KC_NO,    KC_NO,    KC_NO,   KC_NO, KC_NO, KC_ENT,KC_BSPC,KC_DEL,   KC_NO,    KC_NO 
    ),

    [Mouse] = LAYOUT(
    KC_NO, KC_NO, KC_NO, KC_NO, KC_BRIU,  KC_NO,                                      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_BRID,  KC_NO,                                      KC_NO,    KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R, KC_NO, 
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO,  KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_WH_L,  KC_WH_D,  KC_WH_U,  KC_WH_R, KC_NO,
                         KC_NO, KC_NO,    KC_NO,  KC_NO,    KC_NO,  KC_BTN1,KC_BTN3,  KC_BTN2,  KC_NO,    KC_NO
    ),

    
  [Sym] = LAYOUT(
    KC_NO,KC_LCBR, KC_AMPR, KC_ASTR,  KC_LPRN, KC_RCBR,                                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
    KC_NO,KC_COLN, KC_DLR,  KC_PERC,  KC_CIRC, KC_PLUS,                                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
    KC_NO,KC_TILD, KC_EXLM, KC_AT,   KC_HASH,  KC_PIPE, KC_NO,    KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
                            KC_NO,    KC_NO,   KC_LPRN, KC_RPRN,  KC_UNDS,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),

  [Num] = LAYOUT(
    KC_NO, KC_LBRC,  KC_7,   KC_8,   KC_9,   KC_RBRC,                                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
    KC_NO, KC_SCLN,  KC_4,   KC_5,   KC_6,   KC_EQL,                                      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
    KC_NO, KC_GRV,   KC_1,   KC_2,   KC_3,   KC_BSLS,  KC_NO,    KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
                             KC_NO,  KC_NO,  KC_DOT,   KC_0,     KC_MINS,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),

  [Func] = LAYOUT(
    KC_NO,  KC_F12, KC_F7, KC_F8,   KC_F9,  KC_PSCR,                              KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, DB_TOGG, 
    KC_NO,  KC_F11, KC_F4, KC_F5,   KC_F6,  KC_SCRL,                              KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
    KC_NO,  KC_F10, KC_F1, KC_F2,   KC_F3,  KC_PAUS,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                           KC_NO, KC_NO,   KC_APP, KC_SPC,   KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ), 


  [GUI] = LAYOUT(
     QK_BOOT,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    QK_BOOT, 
     KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD,    KC_NO, 
     KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO,  KC_NO,    KC_NO,   KC_NO,    RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,   KC_NO,
                           KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO,   KC_MSTP,KC_MPLY,   KC_MUTE,  KC_NO, KC_NO  
    ),

    [_FROG] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_F,    KC_D,    KC_N,    KC_I,    KC_G,                         KC_G,    KC_I,    KC_N,    KC_D,    KC_F,  KC_ESC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      BSP_EXT,    KC_S,    KC_T,    KC_H,    KC_E,    KC_O,                         KC_O,    KC_E,    KC_H,    KC_T,    KC_S, BSP_EXT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         OSFT,    KC_C,    KC_W,    KC_R,    KC_A,    KC_U,   KC_NO, KC_NO,  KC_NO,    KC_NO,                      KC_U,    KC_A,    KC_R,    KC_W,    KC_C,    OSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_NO, KC_NO,  ONUM,    OSYM,  KC_SPC,     KC_SPC,    OSYM,    ONUM, KC_NO, KC_NO \
                                      //`--------------------------'  `--------------------------'
    ),

    [_SYM] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_LBRC, KC_LCBR, KC_LPRN,   KC_AT, KC_CIRC,                      KC_CIRC,   KC_AT, KC_LPRN, KC_LCBR, KC_LBRC,  KC_TAB,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSLS, KC_COLN, KC_SCLN, KC_QUES, KC_EXLM, KC_SLSH,                      KC_SLSH, KC_EXLM, KC_QUES, KC_SCLN, KC_COLN, KC_BSLS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TILD, KC_RBRC, KC_RCBR, KC_RPRN, KC_AMPR, KC_ASTR,    KC_NO, KC_NO,  KC_NO,    KC_NO,                  KC_ASTR, KC_AMPR, KC_RPRN, KC_RCBR, KC_RBRC, KC_TILD,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      KC_NO, KC_NO,    XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, KC_NO, KC_NO \
                                      //`--------------------------'  `--------------------------'
    ),

    [_NUM] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_EQL,    KC_6,    KC_7,    KC_8,    KC_9,  KC_DOT,                       KC_DOT,    KC_9,    KC_8,    KC_7,    KC_6,  KC_EQL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_PLUS,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_5,    KC_4,    KC_3,    KC_2,    KC_1, KC_PLUS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_MINS, KC_HASH,  KC_DLR, KC_PERC,    KC_0, KC_COMM,    KC_NO, KC_NO,  KC_NO,    KC_NO,                  KC_COMM,    KC_0, KC_PERC,  KC_DLR, KC_HASH, KC_MINS,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      KC_NO, KC_NO,    XXXXXXX, XXXXXXX,    OGUI,       OGUI, XXXXXXX, XXXXXXX, KC_NO, KC_NO \
                                      //`--------------------------'  `--------------------------'
    ),

    [_EXT] = LAYOUT( \
/*I recommend adding a TO() that leads to your two-handed layer to the first and last key in the next line of code if you 
are adding this keymap to a two-handed keymap. It is left blank for this purpose.*/
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      DF(0), KC_WBAK, KC_HOME,   KC_UP,  KC_END, KC_WFWD,                      KC_WFWD, KC_HOME,   KC_UP,  KC_END, KC_WBAK, TO(1),\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    ATAB, KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL,                       KC_DEL, KC_LEFT, KC_DOWN, KC_RGHT,    ATAB, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, C(KC_Z), C(KC_X), C(KC_C), C(KC_V),    OALT,      KC_NO, KC_NO,  KC_NO,    KC_NO,                   OALT, C(KC_V), C(KC_C), C(KC_X), C(KC_Z), XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_NO, KC_NO,    OSFT,    OCTL,    CBSP,       CBSP,    OCTL,    OSFT, KC_NO, KC_NO\
                                      //`--------------------------'  `--------------------------'
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ABSPST:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_TAP(X_BTN1) SS_DELAY(200) "int" SS_DELAY(200) SS_TAP(X_TAB) SS_DELAY(200) SS_TAP(X_ENT));
        } else {
            // when keycode QMKBEST is released
        }
        break;
    
        case ABSCPY:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_TAP(X_BTN1) SS_DELAY(50) SS_TAP(X_BTN1) SS_DELAY(200) SS_LCTL("c") SS_DELAY(200) SS_TAP(X_LALT) SS_DELAY(100) "hy" SS_DELAY(500) SS_TAP(X_HOME) SS_DELAY(200) SS_TAP(X_SPC) SS_DELAY(200) SS_TAP(X_LEFT) SS_DELAY(200) SS_LCTL("v") SS_DELAY(200) SS_TAP(X_TAB) SS_DELAY(200) "t" SS_DELAY(200) SS_TAP(X_TAB) SS_DELAY(200) SS_TAP(X_ENT));
          //  SEND_STRING(SS_LALT("ty") SS_DELAY(500) SS_TAP(X_HOME) SS_LCTL(SS_DOWN(X_LSHFT)SS_TAP(X_RIGHT)SS_UP(X_LSHFT)) SS_TAP(X_SPC) SS_TAP(X_LEFT) SS_LCTL("v") SS_TAP(X_TAB) "t" SS_TAP(X_TAB) SS_TAP(X_ENT));
        } else {
            // when keycode QMKBEST is released
        }
        break;

        case ABSDEL: 
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            //SEND_STRING("Wahahaha");
            SEND_STRING(SS_TAP(X_DEL) SS_DELAY(100) SS_TAP(X_DOWN) SS_DELAY(100) SS_TAP(X_UP) SS_DELAY(100) SS_TAP(X_F2) SS_DELAY(500) SS_TAP(X_LEFT) SS_DELAY(100) SS_LCTL(SS_LSFT(SS_TAP(X_RIGHT))) SS_LCTL("c") SS_LALT(SS_TAP(X_TAB)) );
        } else {
            // when keycode QMKBEST is released
        }
        break;
    };
    return true;
};


oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case Base:
                oled_write_P(PSTR("base\n"), false);
                break;
            case Media:
                oled_write_P(PSTR("media\n"), false);
                break;
            case Nav:
                oled_write_P(PSTR("nav\n"), false);
                break;
            case Mouse:
                oled_write_P(PSTR("mouse\n"), false);
                break;
            case Sym:
                oled_write_P(PSTR("sym\n"), false);
                break;
            case Num:
                oled_write_P(PSTR("num\n"), false);
                break;
            case Func:
                oled_write_P(PSTR("func\n"), false);
                break;
            case GUI:
                oled_write_P(PSTR("gui\n"), false);
                break;
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
            // 'kingcurtis', 128x64px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x40, 
0x00, 0x20, 0x08, 0x40, 0x12, 0x0c, 0x20, 0x02, 0x98, 0x44, 0x02, 0x28, 0x04, 0x90, 0x20, 0x4c, 
0x10, 0x90, 0x40, 0x08, 0x20, 0x40, 0x88, 0x20, 0x10, 0xc8, 0x60, 0x10, 0xc0, 0x00, 0x80, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08, 0x80, 0x10, 0x04, 0x00, 0x00, 0x01, 0x40, 
0x00, 0x90, 0x44, 0x00, 0x90, 0x41, 0x00, 0x80, 0x34, 0x40, 0x81, 0x90, 0x62, 0x8c, 0x80, 0x60, 
0x02, 0x80, 0x04, 0x21, 0x80, 0x92, 0x41, 0x00, 0x86, 0x01, 0x10, 0x04, 0x01, 0x92, 0x00, 0x03, 
0x18, 0x44, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0xe0, 0xc0, 0xc0, 0x20, 0xe0, 
0xc0, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 
0x00, 0xc0, 0x20, 0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 
0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x80, 0xc0, 0x20, 0xe0, 0xc0, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x40, 0x24, 0x91, 0x48, 
0x26, 0x91, 0x10, 0x0c, 0x01, 0x8c, 0x84, 0x11, 0x01, 0x02, 0x18, 0x41, 0x06, 0x34, 0xc1, 0x9a, 
0x66, 0x65, 0x99, 0x8a, 0x26, 0x31, 0xcc, 0x06, 0x10, 0x46, 0x09, 0xa4, 0x24, 0xc8, 0x4a, 0x10, 
0x80, 0xa0, 0x01, 0x01, 0x10, 0x04, 0x00, 0x00, 0x00, 0x3f, 0x60, 0x7d, 0x7d, 0x3d, 0x62, 0x7f, 
0x7f, 0x1e, 0x31, 0x6a, 0x6a, 0x6a, 0x69, 0x7f, 0x7e, 0x1f, 0xb0, 0x6f, 0x6f, 0x6f, 0x80, 0xff, 
0xff, 0x3f, 0x60, 0x6e, 0x6e, 0x6e, 0x71, 0x3f, 0x1e, 0x1e, 0x31, 0x6e, 0x6e, 0x6e, 0x71, 0x3f, 
0x1e, 0x18, 0x35, 0x6a, 0x6a, 0x6a, 0x61, 0x7f, 0x7f, 0x3e, 0x61, 0x7e, 0x7e, 0x03, 0x03, 0x1e, 
0x31, 0x6e, 0x6e, 0x6e, 0x60, 0x7f, 0x7f, 0x36, 0x6d, 0x6a, 0x6a, 0x6a, 0x76, 0x3f, 0x1b, 0x00, 
0x00, 0x00, 0x00, 0x91, 0x10, 0x00, 0x60, 0x00, 0x80, 0x30, 0x44, 0x99, 0x22, 0x66, 0x19, 0xcc, 
0x36, 0x32, 0xca, 0xb9, 0x36, 0xdc, 0xf0, 0x26, 0xec, 0xd8, 0x33, 0x6c, 0x8c, 0xb3, 0x4c, 0x6d, 
0x33, 0x3f, 0xed, 0x2c, 0xb2, 0xf2, 0x58, 0xe0, 0xa4, 0x60, 0xd0, 0x90, 0x61, 0xc0, 0x93, 0x45, 
0xd0, 0x9a, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0xf8, 0x14, 0xfc, 0xf8, 0xc0, 0xa0, 0x50, 0x50, 0x50, 0xd1, 0xf3, 0x63, 0x03, 0x03, 0x01, 
0x00, 0xf8, 0x04, 0xfc, 0xf8, 0xf8, 0x14, 0xfc, 0xf8, 0xf8, 0x04, 0xbc, 0xb8, 0x50, 0xe8, 0xf8, 
0x30, 0xc0, 0x20, 0x50, 0x50, 0x50, 0x30, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0xd0, 
0xd0, 0x30, 0xd0, 0xd0, 0x30, 0xe0, 0xc0, 0xe0, 0x10, 0xf0, 0xe0, 0xe0, 0x10, 0xf0, 0xe0, 0x00, 
0x00, 0x00, 0x86, 0x30, 0x4c, 0x21, 0x88, 0x80, 0x34, 0x01, 0x92, 0x10, 0x45, 0x49, 0x12, 0x24, 
0xc9, 0x13, 0x24, 0xcd, 0x13, 0x36, 0xcd, 0x99, 0x36, 0x66, 0x9b, 0x22, 0x68, 0x98, 0x24, 0x70, 
0xc9, 0x28, 0x70, 0xc1, 0x61, 0xbe, 0x97, 0x75, 0x6d, 0x9e, 0x73, 0x6d, 0x9f, 0xf3, 0x4d, 0x36, 
0xb6, 0x49, 0x00, 0x10, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x07, 0x0c, 0x0f, 0x0f, 0x06, 0x0d, 0x0d, 0x0d, 0x0d, 0x0e, 0x07, 0x03, 0x00, 0x00, 0x00, 
0x00, 0x07, 0x0c, 0x0f, 0x0f, 0x07, 0x0c, 0x0f, 0x0f, 0x07, 0x0c, 0x0f, 0x07, 0x07, 0x0c, 0x0f, 
0x0f, 0x03, 0x06, 0x0d, 0x0d, 0x0d, 0x0d, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0c, 0x0f, 
0x07, 0x0c, 0x0f, 0x07, 0x0c, 0x0f, 0x0f, 0x03, 0x36, 0x6d, 0x6d, 0x6d, 0x70, 0x3f, 0x1f, 0x00, 
0x00, 0x00, 0x01, 0x00, 0x03, 0x01, 0x04, 0x00, 0x42, 0x08, 0x01, 0x24, 0x88, 0x02, 0x31, 0x84, 
0x04, 0x61, 0x0c, 0x10, 0x53, 0x02, 0x2c, 0xc9, 0x91, 0x04, 0x60, 0x89, 0x08, 0x44, 0x80, 0x08, 
0x08, 0x88, 0x09, 0x31, 0x46, 0x81, 0x35, 0x46, 0x49, 0x31, 0x0e, 0xc2, 0x31, 0x0c, 0x42, 0x33, 
0x89, 0xe0, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0xf4, 
0x02, 0xf5, 0xf5, 0x3f, 0x3e, 0xc0, 0xa8, 0x54, 0x54, 0x54, 0x0c, 0xfc, 0xf8, 0xf8, 0x04, 0xf4, 
0xf4, 0x0c, 0xf4, 0xf4, 0x0c, 0xf8, 0xf0, 0xfe, 0x05, 0xff, 0xfe, 0xfe, 0x01, 0xff, 0xfe, 0xf8, 
0x84, 0x7c, 0x78, 0x78, 0x04, 0xfc, 0xf8, 0xfe, 0x41, 0xff, 0xfe, 0xfe, 0x41, 0xff, 0xfe, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x08, 0x20, 0x02, 0x00, 0x08, 
0x82, 0x00, 0x09, 0x21, 0x04, 0x11, 0x42, 0x10, 0x04, 0x83, 0x22, 0x09, 0x45, 0x14, 0x10, 0x03, 
0x22, 0x18, 0x87, 0x20, 0x0a, 0x89, 0x24, 0x02, 0x09, 0x21, 0x04, 0x10, 0x00, 0x63, 0x18, 0x01, 
0x03, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x03, 0x03, 
0x01, 0x03, 0x03, 0x01, 0x03, 0x03, 0x03, 0x01, 0x03, 0x03, 0x03, 0x01, 0x03, 0x03, 0x03, 0x00, 
0x0d, 0x1b, 0x1b, 0x1b, 0x1c, 0x0f, 0x07, 0x01, 0x03, 0x03, 0x03, 0x01, 0x03, 0x03, 0x03, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x11, 0x00, 0x48, 0x00, 0x02, 0x48, 
0x00, 0x10, 0x04, 0x00, 0x40, 0x00, 0x02, 0x80, 0x00, 0x08, 0x80, 0x01, 0x10, 0x00, 0x81, 0x00, 
0x04, 0x00, 0x00, 0x20, 0x00, 0x04, 0x80, 0x00, 0x11, 0x00, 0x02, 0x10, 0x00, 0x00, 0x20, 0x00, 
0x00, 0x20, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
         };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
    return false;
}

bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
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

