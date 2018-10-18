#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    BASE = 0,
    META,
    SYMB
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
//Macros

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  -   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |   /  |\/Sft |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * | 変換 | ALT  | GUI  | PrtSc| ESC/ |Space/|Tab/  |Back  |Enter/| Del  | Left | Down |  Up  | Right |
   * |      |      |      |      | LCtrl|~SYMB |Shift |Space |~META |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,             KC_T,                                     KC_Y,             KC_U,    KC_I,    KC_O,     KC_P,       KC_MINS, \
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,             KC_G,                                     KC_H,             KC_J,    KC_K,    KC_L,     KC_SCLN,    KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,             KC_B,                                     KC_N,             KC_M,    KC_COMM, KC_DOT,   KC_SLSH,    SFT_T(KC_BSLS), \
      LGUI(KC_SPC), KC_LALT, KC_LGUI, KC_PSCR, LT(KC_LCTL, KC_ESC), LT(SYMB, KC_SPC), SFT_T(KC_TAB),  KC_BSPC,  LT(META, KC_ENT), KC_DELT, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
      ),

  /* META
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  =   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |      |      |      |      |      |             | Left | Down |  Up  |Right |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |Shift |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  | F10  |\/Sft |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * | 変換 | GUI  |  App |PrtSc |ESC/  |Space/|Tab/  |Back  |Enter/| Del  |Reset |=>GAME|=>SYMB|  \   |
   * |      |      |      |      |~SYMB | Ctrl |Shift |Space |~META |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [META] = LAYOUT( \
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,  KC_9,    KC_0,    KC_EQL, \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, XXXXXXX, XXXXXXX, \
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8, KC_9, KC_F10, SFT_T(KC_RO), \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
  ),

  /* SYMB
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |  +   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |      |      |      |      |   {  |             |   }  |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |Shift |      |      |      |      |   [  |             |   ]  |      |   <  |   >  |   ?  |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * | 変換 | GUI  |  App |PrtSc |ESC/  |Space/|Tab/  |Back  |Enter/| Del  |PrtSc |=>GAME|=>SYMB|      |
   * |      |      |      |      |~SYMB |RCtrl |Shift |Space |~META |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [SYMB] = LAYOUT( \
    S(KC_GRV), S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),                 S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), S(KC_EQL), \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, S(KC_LBRC),                S(KC_RBRC), S(KC_9), S(KC_RBRC), S(KC_BSLS), S(KC_SCLN), S(KC_QUOT), \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC,                   KC_RBRC, XXXXXXX, S(KC_COMM), S(KC_DOT),  S(KC_SLSH), S(KC_RO), \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,   _______,    _______ \
  ),

};
