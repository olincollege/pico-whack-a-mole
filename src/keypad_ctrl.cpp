#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "pico/stdlib.h"

#include "pico_rgb_keypad.hpp"
#include "keypad_ctrl.h"

using namespace pimoroni;

PicoRGBKeypad keypad;

void keypad_setup(void) {
    keypad.init(); // Set up GPIO
    keypad.set_brightness(0.1f);
}

void turnon_led (int led, int* is_led_on) {
    keypad.illuminate(led, 255, 0, 255);
    keypad.update();
    *is_led_on = 1;
}

void turnoff_led(int led, int* is_led_on) {
    keypad.illuminate(led, 0, 0, 0);
    keypad.update();
    *is_led_on = 0;
}

uint16_t get_buttons(void) {
    return keypad.get_button_states();
}

int button_pressed(uint16_t cur_states, uint16_t prev_states) {
    uint16_t changed_buttons = cur_states ^ prev_states;
    uint16_t pressed_buttons = cur_states & changed_buttons;

    for (int i = 0; i < keypad.NUM_PADS; i++) {
        if (pressed_buttons & (1 << i)){ // iterates a 1 through the bits via i by shifting the 1 i places. 'ands' the one with the current_button_states and so if it is 1 it will enter the if
            int pressed_button = i; 
            return pressed_button;
        }
    }
    return -1;
}

