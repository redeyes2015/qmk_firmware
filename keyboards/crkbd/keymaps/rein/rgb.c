#include QMK_KEYBOARD_H

uint16_t get_tapping_term(uint16_t keycode) {
    switch (keycode) {
        case OSL(6):
        case OSM(MOD_LSFT):
        case OSM(MOD_LCTL):
        case OSM(MOD_LALT):
        case OSM(MOD_LGUI):
            return 1000;
        case LCTL_T(KC_SPC):
            return 180;
        case LT(4,KC_TAB):
            return 150;
        default:
            return TAPPING_TERM;
    }
}

#ifdef RGBLIGHT_ENABLE

#define HSV_BLACK 0,0,0

void keyboard_post_init_user(void) {
    rgblight_sethsv_noeeprom(HSV_BLACK);
}

#define HSV_SET_THUMB(color) { \
        rgblight_sethsv_at(color, 6); \
        rgblight_sethsv_at(color, 13); \
        rgblight_sethsv_at(color, 14); \
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 2:
            HSV_SET_THUMB(HSV_RED);
            break;
        case 3:
            HSV_SET_THUMB(HSV_YELLOW);
            break;
        case 4:
            HSV_SET_THUMB(HSV_CYAN);
            break;
        case 5:
            HSV_SET_THUMB(HSV_PURPLE);
            break;
        case 6:
            HSV_SET_THUMB(HSV_BLUE);
            break;
        default:
            HSV_SET_THUMB(HSV_BLACK);
            break;
    }
    return state;
}

static void set_mod_light (uint8_t mods, uint8_t mod_mask, uint8_t begin) {
    if ((mods & mod_mask) != 0) {
        rgblight_sethsv_range(HSV_BLUE, begin, begin + 3);
    }
    else {
        rgblight_sethsv_range(HSV_BLACK, begin, begin + 3);
    }
}

void oneshot_mods_changed_user(uint8_t mods) {
    set_mod_light(mods, MOD_MASK_SHIFT, 10);
    set_mod_light(mods, MOD_MASK_CTRL, 15);
    set_mod_light(mods, MOD_MASK_ALT, 18);
    set_mod_light(mods, MOD_MASK_GUI, 21);
}
#endif
