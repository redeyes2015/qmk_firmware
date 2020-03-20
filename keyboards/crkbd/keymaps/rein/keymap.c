#include QMK_KEYBOARD_H

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   	[0] = LAYOUT(KC_NO, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LGUI, KC_NO, KC_A, LALT_T(KC_S), LCTL_T(KC_D), KC_F, KC_G, KC_H, KC_J, RCTL_T(KC_K), RALT_T(KC_L), KC_SCLN, KC_NO, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_ESC, LT(1,KC_SPC), LT(4,KC_TAB), LT(4,KC_BSPC), LT(2,KC_ENT), LT(3,KC_DEL)),
	[1] = LAYOUT(RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_UP, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LALT, KC_LCTL, KC_LSFT, KC_TRNS, LCTL(KC_LEFT), KC_LEFT, KC_DOWN, KC_RGHT, LCTL(KC_RGHT), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_TRNS, KC_TRNS, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[2] = LAYOUT(KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS, KC_TRNS, KC_1, LALT_T(KC_2), LCTL_T(KC_3), KC_4, KC_5, KC_6, KC_7, RCTL_T(KC_8), RALT_T(KC_9), KC_0, KC_TRNS, KC_TRNS, KC_GRV, KC_PIPE, KC_UNDS, KC_QUOT, KC_DQUO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TILD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[3] = LAYOUT(KC_TRNS, KC_INS, KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PAUS, KC_SLCK, KC_PSCR, KC_F10, KC_TRNS, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F11, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RSFT, KC_RCTL, KC_RALT, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_APP, KC_TRNS, KC_TRNS, KC_TRNS),
	[4] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PIPE, KC_BSLS, KC_UNDS, KC_MINS, KC_TRNS, KC_TRNS, KC_EQL, KC_PLUS, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS, KC_GRV, KC_TILD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

int RGB_current_mode;

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  return true;
}
