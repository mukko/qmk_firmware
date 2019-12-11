#include QMK_KEYBOARD_H

extern uint8_t is_master;

#define _QWERTY     0
#define _LOWER      1
#define _RAISE      2
#define _ADJUST     3
#define _ALT_WIN    4
#define _FN         5

#define TAB         KC_TAB
// for KC_C_() --> C()     KC_S_() --> S()
#define KC_C_       C
#define KC_S_       S
#define KC_LOWER    LOWER
#define KC_RAISE    RAISE
#define KC_RESET    RESET
#define KC_____     KC_TRNS
#define KC_XXXX     KC_NO

#define KC_BR_PR    KC_PARENTHESIS
#define KC_BR_SQ    KC_SQ_BRACKETS

enum custom_keycodes {
      QWERTY = SAFE_RANGE
    , KC_ALLUP
    , KC_LOWER
    , KC_RAISE
    , KC_SFT_ESC
    , KC_CTL_QOT
    , KC_CTL_MIN
    , KC_SFT_TAB
    , KC_SFT_ENT
    , KC_SFT_EQL
    , KC_ALT_EX
    , KC_WIN_EX
    , KC_FN_EX
    , KC_xSFT
    , KC_PARENTHESIS
    , KC_SQ_BRACKETS
};

// https://docs.qmk.fm/#/

#define LAYOUT_kc( \
	L00, L01, L02, L03, L04, L05, R00, R01, R02, R03, R04, R05, \
	L10, L11, L12, L13, L14, L15, R10, R11, R12, R13, R14, R15, \
	L20, L21, L22, L23, L24, L25, R20, R21, R22, R23, R24, R25, \
	L30, L31, L32, L33, L34, L35, R30, R31, R32, R33, R34, R35 \
	) \
    LAYOUT( \
        KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04, KC_##L05, KC_##R00, KC_##R01, KC_##R02, KC_##R03, KC_##R04, KC_##R05, \
        KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14, KC_##L15, KC_##R10, KC_##R11, KC_##R12, KC_##R13, KC_##R14, KC_##R15, \
        KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##L25, KC_##R20, KC_##R21, KC_##R22, KC_##R23, KC_##R24, KC_##R25, \
        KC_##L30, KC_##L31, KC_##L32, KC_##L33, KC_##L34, KC_##L35, KC_##R30, KC_##R31, KC_##R32, KC_##R33, KC_##R34, KC_##R35 \
	)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc( \
      Q       , W       , E       , R       , T       , Y            , T       , Y       , U       , I       , O       , P       \
    , A       , S       , D       , F       , G       , H            , G       , H       , J       , K       , L       , SCLN    \
    , SFT_ESC , Z       , X       , C       , V       , B            , B       , N       , M       , COMM    , DOT     , SLSH    \
    , TAB     , LALT    , XXXX    , CTL_MIN , xSFT    , LOWER        , RAISE   , xSFT    , CTL_QOT , XXXX    , RALT    , ENTER   \
)
, [_LOWER] = LAYOUT_kc( \
      1       , 2       , 3       , 4       , 5       , SPACE        , GRV     , 6       , 7       , 8       , 9       , 0       \
    , DEL     , ____    , LBRC    , RBRC    , ENTER   , TAB          , EQL     , LEFT    , DOWN    , UP      , RGHT    , BSLS    \
    , BSPC    , ____    , ____    , ALT_EX  , FN_EX   , ____         , BSPC    , HOME    , END     , PGUP    , PGDN    , ____    \
    , ____    , ____    , XXXX    , ____    , ____    , ____         , DEL     , ____    , ____    , XXXX    , ____    , ____    \
)

, [_RAISE] = LAYOUT_kc( \
      1       , 2       , 3       , 4       , 5       , SPACE        , GRV     , 6       , 7       , 8       , 9       , 0       \
    , ____    , ____    , LBRC    , RBRC    , ____    , ____         , ____    , PSCR    , ____    , ____    , ____    , ____    \
    , ____    , ____    , BR_PR   , BR_SQ   , ____    , ____         , WIN_EX  , FN_EX   , ____    , ____    , ____    , ____    \
    , ____    , ____    , XXXX    , ____    , ____    , ____         , ____    , ____    , ____    , XXXX    , ____    , ____    \
)

, [_ALT_WIN] = LAYOUT_kc( \
      Q       , W       , E       , R       , T       , Y            , T       , Y       , U       , I       , O       , P       \
    , A       , S       , D       , F       , G       , H            , G       , H       , J       , K       , L       , ____    \
    , ____    , Z       , X       , C       , V       , B            , B       , N       , M       , XXXX    , XXXX    , ____    \
    , ____    , XXXX    , XXXX    , S_(TAB) , TAB    , ____          , ____    , ____    , ____    , XXXX    , XXXX    , ____    \
)

, [_FN] = LAYOUT_kc( \
      F1      , F2      , F3      , F4      , F5      , F6           , F1      , F2      , F3      , F4      , F5      , F6   \
    , F7      , F8      , F9      , F10     , F11     , F12          , F7      , F8      , F9      , F10     , F11     , F12  \
    , XXXX    , XXXX    , LALT    , XXXX    , XXXX    , XXXX         , XXXX    , XXXX    , XXXX    , RALT    , XXXX    , XXXX    \
    , ____    , ____    , XXXX    , ____    , ____    , ____         , RESET   , ALLUP   , ____    , XXXX    , ____    , ____    \
)
};

static bool lower_interrupted   = false;
static bool raise_interrupted   = false;
static bool ctrl_l_interrupted  = false;
static bool ctrl_r_interrupted  = false;
static bool sft_l_interrupted   = false;
static bool sft_r_interrupted   = false;
static bool sft_x_interrupted   = false;

uint16_t last_mod_pressed_t     = 0;
uint16_t last_pressed_shf_l     = 0;
uint16_t last_pressed_shf_r     = 0;
uint16_t last_pressed_shf_x     = 0;
uint16_t last_pressed_ctrl_l    = 0;
uint16_t last_pressed_ctrl_r    = 0;
uint16_t last_pressed_raise     = 0;
uint16_t last_pressed_lower     = 0;

const uint8_t TAP_TIME = 200;

void clear_all_flags(void) {
    raise_interrupted   = true;
    lower_interrupted   = true;
    ctrl_l_interrupted  = true;
    ctrl_r_interrupted  = true; 
    sft_l_interrupted   = true;
    sft_r_interrupted   = true;
    sft_x_interrupted   = true;
}
void up_all_modKeys(void) {
    unregister_code(KC_LSFT);
    unregister_code(KC_RSFT);
    unregister_code(KC_LCTRL);
    unregister_code(KC_RCTRL);
    unregister_code(KC_LALT);
    unregister_code(KC_RALT);
    unregister_code(KC_LWIN);
    unregister_code(KC_RWIN);
    set_single_persistent_default_layer(_QWERTY);
}
void layer_switch_with_tapping(uint16_t layercode, uint16_t tapkey, bool *is_interrupted, uint16_t *timestamp, keyrecord_t *record) {
    if (record->event.pressed){
        (*timestamp) = timer_read();
        (*is_interrupted) = false;
        layer_on(layercode);
        // update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    else {
        layer_off(layercode);
        // update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (! (*is_interrupted)){
            clear_all_flags();
            if (timer_elapsed(*timestamp) < TAP_TIME) {
                tap_code(tapkey); } } }
}
void modifier_key_with_tapping(uint16_t modkey, uint16_t tapkey, bool *is_interrupted, uint16_t *timestamp, keyrecord_t *record) {
    if (record->event.pressed) {
        (*timestamp) = timer_read();
        (*is_interrupted) = false;
        register_code(modkey); }
    else {
        unregister_code(modkey);
        if (! (*is_interrupted)) {
            clear_all_flags();
            if (timer_elapsed(*timestamp) < TAP_TIME) {
                tap_code(tapkey); } } }
}

// この関数で mod keys に関して bug 発生するかも

void send_key_set(uint16_t key, uint16_t l_key, uint16_t r_key, keyrecord_t *record) {
    if (! record->event.pressed){
        tap_code16(l_key);
        tap_code16(r_key);
        clear_mods();
        clear_all_flags();
        tap_code(KC_LEFT); }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
}

    switch (keycode) {
        case KC_xSFT:
            if (record->event.pressed){
                sft_x_interrupted = false;
                last_pressed_shf_x = timer_read();
                register_code(KC_LSFT); }
            else {
                unregister_code(KC_LSFT);
                sft_x_interrupted = true; }
            return false;
            break;
        case QWERTY:
          if (record->event.pressed){
              set_single_persistent_default_layer(_QWERTY); }
          return false;
          break;
        case KC_LOWER:
            layer_switch_with_tapping(_LOWER, KC_SPC, &lower_interrupted, &last_pressed_lower, record);
            return false;
            break;
        case KC_RAISE:
            layer_switch_with_tapping(_RAISE, KC_SPC, &raise_interrupted, &last_pressed_raise, record);
            return false;
            break;
    //    case CTL_ESC:
    //        modifier_key_with_tapping(KC_LCTRL, KC_ESC, &ctrl_l_interrupted, record);
    //        return false;
    //        break;
        case KC_SFT_ESC:
            modifier_key_with_tapping(KC_LSFT, KC_ESC, &sft_l_interrupted, &last_pressed_shf_l, record);
            return false;
            break;
        case KC_CTL_QOT:
            modifier_key_with_tapping(KC_RCTRL, KC_QUOT, &ctrl_r_interrupted, &last_pressed_ctrl_r, record);
            return false;
            break;
        case KC_CTL_MIN:
            modifier_key_with_tapping(KC_LCTRL, KC_MINS, &ctrl_r_interrupted, &last_pressed_ctrl_l, record);
            return false;
            break;
        case KC_SFT_TAB:
            modifier_key_with_tapping(KC_LSFT, KC_TAB, &sft_l_interrupted, &last_pressed_shf_l, record);
            return false;
            break;
        case KC_SFT_ENT:
            modifier_key_with_tapping(KC_RSFT, KC_ENT, &sft_r_interrupted, &last_pressed_shf_r, record);
            return false;
            break;
        case KC_SFT_EQL:
            modifier_key_with_tapping(KC_RSFT, KC_EQL, &sft_r_interrupted, &last_pressed_shf_r, record);
            return false;
            break;
        // case ADJUST:
        //     if (record->event.pressed) {
        //       layer_on(_ADJUST); }
        //     else {
        //       layer_off(_ADJUST); }
        //     return false;
        //     break;
        
          case KC_PARENTHESIS:
            send_key_set(keycode, RSFT(KC_9), LSFT(KC_0), record);
            return false;
            break;
        case KC_SQ_BRACKETS:
            send_key_set(keycode, KC_LBRC, KC_RBRC, record);
            return false;
            break;
        case KC_ALT_EX:
            if (record->event.pressed){
                register_code(KC_LALT);
                layer_on(_ALT_WIN); }
            else {
                layer_off(_ALT_WIN);
                unregister_code(KC_LALT); }
            return false;
            break;
        case KC_WIN_EX:
            if (record->event.pressed){
                register_code(KC_LWIN);
                layer_on(_ALT_WIN); }
            else {
                layer_off(_ALT_WIN);
                unregister_code(KC_LWIN); }
            return false;
            break;
        case KC_FN_EX:
            if (record->event.pressed){
                layer_on(_FN); }
            else {
                layer_off(_FN); }
            return false;
            break;
        case KC_ALLUP:
            clear_all_flags();
            up_all_modKeys();
            break;
        default:
            if (record->event.pressed) {
                if (sft_x_interrupted) {
                    clear_all_flags(); }
                else {
                    clear_all_flags();
                    sft_x_interrupted = false; }

                if (sft_x_interrupted && timer_elapsed(last_pressed_shf_x) < TAP_TIME) {
                    last_pressed_shf_x = 0;
                    register_code(KC_LSFT);
                    tap_code(keycode);
                    unregister_code(KC_LSFT);
                    return false; } }
            break; }

    return true; 
}
