// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW 0
#define _RS 1
#define _LW 2
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    * |------+------+------+------+------+------+-------------+------+------+------+-----
    * | 変換 | ALT  | GUI  | ESC/ |Space/|Tab/  |Back  |Enter/| \/Sft|   =  |  -  |  '  |
    * |     |      |      | LCtrl|  ~LW |Shift |Space |~RS   |      |      |     |     |
    * `---------------------------------------------------------------------------------
    */
  [_QW] = LAYOUT( /* Qwerty */
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P    ,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN ,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH ,
    LCTL(KC_SPC), KC_LALT, KC_LGUI, LCTL_T(KC_ESC), LT(_LW, KC_SPC), SFT_T(KC_TAB), KC_BSPC, LT(_RS, KC_ENT), SFT_T(KC_BSLS), KC_EQL, KC_MINS, KC_QUOT
  ),

  /*
   *  1   2   3   4   5       ||       6   7   8   9   0
   *  `                       ||      left down up right  +
   *  F1  F2  F3  F4  F5      ||      F6  F7  F8  F9 F10
   *  __  __  __  __  __  __  ||  __  __  __  +  _  "
   */
  [_RS] = LAYOUT( /* [> RAISE <] */
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0 ,
    KC_GRV,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PLUS ,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10 ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PLUS, KC_UNDS, KC_DQUO ),

  /*
   *  !   @   #   $    %       ||     ^   &   *  (  )
   *  ~               {       ||      }          [  ]
   *                  [       //      ]       <  >  ?
   *  __  __  __  __  __  __  ||  __  __  __  +  _  "
   */
  [_LW] = LAYOUT( /* [> LOWER <] */
    KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN  ,
    S(KC_GRV),XXXXXXX, XXXXXXX, XXXXXXX, KC_LCBR,                   KC_RCBR, KC_F4,   KC_F5,   KC_LBRC,   KC_RBRC  ,
    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC,                   KC_RBRC, XXXXXXX, S(KC_COMM),KC_LCBR, KC_RCBR,
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, KC_PLUS, KC_UNDS, KC_DQUO )

};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        register_code(KC_RSFT);
      } else {
        unregister_code(KC_RSFT);
      }
    break;
  }
  return MACRO_NONE;
};
