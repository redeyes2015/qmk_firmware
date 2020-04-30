#include QMK_KEYBOARD_H

#ifdef RGBLIGHT_LAYERS

#define RGBLIGHT_THUMBS(color) RGBLIGHT_LAYER_SEGMENTS( \
    {6, 1, color}, \
    {13, 1, color}, \
    {14, 1, color} \
)

const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_THUMBS(HSV_RED);
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_THUMBS(HSV_YELLOW);
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_THUMBS(HSV_ORANGE);
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_THUMBS(HSV_PURPLE);

const rgblight_segment_t PROGMEM my_shift_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {10, 3, HSV_WHITE}
);
const rgblight_segment_t PROGMEM my_ctrl_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {15, 3, HSV_WHITE}
);
const rgblight_segment_t PROGMEM my_alt_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {18, 3, HSV_WHITE}
);
const rgblight_segment_t PROGMEM my_gui_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {21, 3, HSV_WHITE}
);

enum my_rgblayout_index {
    my_layer1_index = 0,
    my_layer2_index,
    my_layer3_index,
    my_layer4_index,
    my_shift_index,
    my_ctrl_index,
    my_alt_index,
    my_gui_index
};

#define MY_LAYER_DEFINE(name) [name##_index] = name##_layer

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    MY_LAYER_DEFINE(my_layer1),
    MY_LAYER_DEFINE(my_layer2),
    MY_LAYER_DEFINE(my_layer3),
    MY_LAYER_DEFINE(my_layer4),
    MY_LAYER_DEFINE(my_shift),
    MY_LAYER_DEFINE(my_ctrl),
    MY_LAYER_DEFINE(my_alt),
    MY_LAYER_DEFINE(my_gui)
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_sethsv_noeeprom(0, 0, 0);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(my_layer1_index, layer_state_cmp(state, 1));
    rgblight_set_layer_state(my_layer2_index, layer_state_cmp(state, 2));
    rgblight_set_layer_state(my_layer3_index, layer_state_cmp(state, 3));
    rgblight_set_layer_state(my_layer4_index, layer_state_cmp(state, 4));
    return state;
}

void oneshot_mods_changed_user(uint8_t mods) {
    rgblight_set_layer_state(my_shift_index, (mods & MOD_MASK_SHIFT) != 0);
    rgblight_set_layer_state(my_ctrl_index, (mods & MOD_MASK_CTRL) != 0);
    rgblight_set_layer_state(my_alt_index, (mods & MOD_MASK_ALT) != 0);
    rgblight_set_layer_state(my_gui_index, (mods & MOD_MASK_GUI) != 0);
}
#endif
