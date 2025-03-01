/*
 * # Olle's Preonic layout
 *
 * ## Preamble
 *
 * This layout's goal is the following:
 * - All characters for writing english text should be easily available
 * - All characters for writing swedish text should be easily available
 * - All characters for programming in a generic language should be easily available
 * - All characters used by the three major OSes should be available in some way
 *   (e.g. CTRL + ALT + DELETE)
 * - If possible, being able to work without a mouse would be a massive plus
 *
 * N.B!
 * This keyboard expects the OS keyboard layout to be one of the US INTL ones.
 * To be used on macOS you might need my custom keyboard layout in lollek/dotfiles,
 * otherwise the swedish support will not work.
 *
 * ## Layer Description
 *
 * There are several layers available, two permanent ones and four which require
 * holding down a key.
 *
 * ### QWERTY (default)
 * The QWERTY layer is very similar to a normal keyboard, especially a swedish one,
 * since åäö are in their correct places. Not much to comment on this layer.
 * This layer aims to have all characters for writing english and swedish texts.
 *
 * ### MANUAL (toggleable)
 * This layer is a movement layer. It has full mouse support with three speed
 * settings. It also contains most keys for moving around in a text application
 * or other program.
 *
 * ### SYSTEM (keydown from QWERTY)
 * This layer has all system buttons, both for the computer and the keyboard.
 * For example screen brightness or system volume. But also qmk reset, music
 * mode, etc. The key to hold down is placed in an awkward place to avoid
 * accidentally entering this layer.
 *
 * ### SPACE1 (keydown from QWERTY)
 * Convenience keys for navigation when writing text.
 *
 * ### SPACE2 (keydown from QWERTY)
 * Convenience keys for navigation when writing text.
 *
 * ### LOWER (keydown from QWERTY)
 * This layer has many special keys which are available without pressing shift
 * on a normal keyboard, but this is not a hard rule. The layer is formatted for
 * convenience when programming.
 *
 * ### RAISE (keydown from QWERTY)
 * This layer has many special keys which are available when pressing shift
 * on a normal keyboard, but this is not a hard rule. The layer is formatted for
 * convenience when programming.
 *
 * ### ADJUST (keydown from LOWER or RAISE)
 * This is the overflow layer. I don't know what will end up here, but I think
 * it will have convenience keys and perhaps special keys which are too rarely
 * used to have a place on QWERTY, LOWER or RAISE.
 *
 * Helpful links for modifications:
 * - https://docs.qmk.fm/#/keycodes
 * - all stuff under docs/
 */

#include QMK_KEYBOARD_H
#include "muse.h"

enum preonic_layers {
  _QWERTY,
  _MANUAL,
  _SYSTEM,
  _SPACE1,
  _SPACE2,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  MANUAL,
  SYSTEM,
  SPACE1,
  SPACE2,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | RM-W |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | RM-P | RM-Q |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   ?  | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |System| GUI  | Alt  |Lower |Space1|Space2| Raise| RAlt |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,                 KC_6,                KC_7,                KC_8,    KC_9,    KC_0,       KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,                 KC_Y,                KC_U,                KC_I,    KC_O,    KC_P,       RALT(KC_W),
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,                 KC_H,                KC_J,                KC_K,    KC_L,    RALT(KC_P), RALT(KC_Q),
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,                 KC_N,                KC_M,                KC_COMM, KC_DOT,  KC_QUES,    KC_ENT,
  KC_LCTL, SYSTEM,  KC_LGUI, KC_LALT, LOWER,  LT(_SPACE1, KC_SPC),  LT(_SPACE2, KC_SPC), LT(_RAISE, KC_ENT),  KC_RALT, XXXXXXX, XXXXXXX,    XXXXXXX
),

/* Manual
 * ,-----------------------------------------------------------------------------------.
 * |      |Accel1|Accel2|Accel3|      |      |      |      |      |      |      | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |Click1| MUp  |Click3|      |      | WLeft| WDown| WUp  |WRight|      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  | MLeft| MDown|MRight|Click2|      | Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |      | Home | PGDN | PGUP |  End |      | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |      | GUI  | Alt  |Lower | Space| Space| Raise| RAlt |      |      |Qwerty|
 * `-----------------------------------------------------------------------------------'
 */
[_MANUAL] = LAYOUT_preonic_grid(
  XXXXXXX, KC_ACL0, KC_ACL1, KC_ACL2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
  KC_TAB,  KC_BTN1, KC_MS_U, KC_BTN3, XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_D,            KC_WH_U, KC_WH_R, XXXXXXX, XXXXXXX,
  KC_ESC,  KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN2, XXXXXXX, KC_LEFT, KC_DOWN,            KC_UP,   KC_RIGHT,XXXXXXX, XXXXXXX,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    XXXXXXX, KC_HOME, KC_PGDN,            KC_PGUP, KC_END,  XXXXXXX, KC_ENT,
  KC_LCTL, XXXXXXX, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  LT(_RAISE, KC_ENT), KC_RALT, XXXXXXX, XXXXXXX, QWERTY
),


/* System
 * ,-----------------------------------------------------------------------------------.
 * |Light+|Vol+  | AuOn |MusOn |      |RgbTog|      |      | NLock|   /  |   *  |  =   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Light-|Vol-  | AuOff|MusOff| Reset|      |      |      |   7  |   8  |   9  |  -   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | MPrev| MNext|Voice+|MusMod|      |      |      |      |   4  |   5  |   6  |  +   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | MPlay|Voice-|      |      |      |      |      |   1  |   2  |   3  | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |   ,  |   0  |   .  |Manual|
 * `-----------------------------------------------------------------------------------'
 */
[_SYSTEM] = LAYOUT_preonic_grid(
  KC_BRIU, KC_VOLU, AU_ON,   MU_ON,   XXXXXXX,RGB_TOG,XXXXXXX,XXXXXXX,  KC_NLCK, KC_PSLS, KC_PAST, KC_PEQL,
  KC_BRID, KC_VOLD, AU_OFF,  MU_OFF,  RESET,  XXXXXXX,XXXXXXX,XXXXXXX,  KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
  KC_MPRV, KC_MNXT, MUV_IN,  MU_MOD,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,  KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
  XXXXXXX, KC_MPLY, MUV_DE,  XXXXXXX, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,  KC_P1,   KC_P2,   KC_P3,   KC_PENT,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,  KC_PCMM, KC_P0,   KC_PDOT, MANUAL
),

/* Space1
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | WLeft| WDown|  WUp |WRight|      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Left | Down |  Up  | Right|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ____ | Home | PGDN | PGUP |  End |      |      |      |      |      |      | ____ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * `-----------------------------------------------------------------------------------'
 */
[_SPACE1] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Space2
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      | WLeft| WDown|  WUp |WRight|      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      | Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ____ |      |      |      |      |      | Home | PGDN | PGUP |  End |      | ____ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * `-----------------------------------------------------------------------------------'
 */
[_SPACE2] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,XXXXXXX, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   -  |   '  |   (  |   )  |      |      |   [  |   ]  |   :  |   +  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ____ |      |      |      |   /  |      |      |   \  |      |      |      | ____ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  XXXXXXX, KC_MINS, KC_QUOT, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_SCLN, KC_PLUS, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_SLSH, XXXXXXX, XXXXXXX, KC_NUBS, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______, _______, _______, _______, _______, _______, _______, ADJUST,  _______, _______, _______, _______
),


/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   _  |   "  |   <  |   >  |      |      |   {  |   }  |   :  |   =  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ____ |      |      |      |   ?  |      |      |   |  |      |      |      | ____ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  XXXXXXX, KC_UNDS, KC_DQUO, KC_LT,   KC_GT,   XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, KC_COLN, KC_EQL,  XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_QUES, XXXXXXX, XXXXXXX, KC_PIPE, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______, _______, _______, _______, ADJUST,  _______, _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ____ |      |      |      |      |      |      |      |      |      |      | ____ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case MANUAL:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_MANUAL);
          }
          return false;
          break;
        case SYSTEM:
          if (record->event.pressed) {
            layer_on(_SYSTEM);
          } else {
            layer_off(_SYSTEM);
          }
          return false;
          break;
        case SPACE1:
          if (record->event.pressed) {
            layer_on(_SPACE1);
          } else {
            layer_off(_SPACE1);
          }
          return false;
          break;
        case SPACE2:
          if (record->event.pressed) {
            layer_on(_SPACE2);
          } else {
            layer_off(_SPACE2);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case ADJUST:
          if (record->event.pressed) {
            layer_on(_ADJUST);
          } else {
            layer_off(_ADJUST);
          }
          return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef RGBLIGHT_ENABLE
              rgblight_step();
            #endif
            #ifdef __AVR__
            writePinLow(E6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            writePinHigh(E6);
            #endif
          }
          return false;
          break;
      }
    return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
}


void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
