#include QMK_KEYBOARD_H

#include "rgblight.h"

#define RELAY_PIN 11
#define RELAY_ON 0
#define RELAY_OFF 1

bool last_led_state;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE, KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_LEFT_BRACKET, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LEFT_BRACKET, KC_QUOTE, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON, KC_QUOTE, KC_SPACE, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_SPACE, KC_SPACE, KC_BACKSLASH, KC_RIGHT_BRACKET, KC_EQUAL, KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE),
};


void keyboard_post_init_user(void) {
    debug_enable=true;
    debug_matrix=true;

    last_led_state = rgblight_get_val() > 0 ? RELAY_ON : RELAY_OFF;
    gpio_set_pin_output(RELAY_PIN);
    gpio_write_pin(RELAY_PIN, last_led_state);
}

void housekeeping_task_user(void) {
    bool leds_on = rgblight_get_val() > 0 ? RELAY_ON : RELAY_OFF;
    if (leds_on != last_led_state) {
        last_led_state = leds_on;
        gpio_write_pin(RELAY_PIN, leds_on);
    }
}
