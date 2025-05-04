#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "pico/stdlib.h"

#include "pico_rgb_keypad.hpp"
#include "keypad_ctrl.h"

using namespace pimoroni;

PicoRGBKeypad keypad;

int OFF_COLOR = 0x05;

void keypad_setup(void) {
    keypad.init(); // Set up GPIO
    keypad.set_brightness(0.1f);

    // Initialize all LEDs to a dim whitish while "off"
    for(int i = 0; i < keypad.NUM_PADS; i++) {
        keypad.illuminate(i, OFF_COLOR, OFF_COLOR, OFF_COLOR);
    }
}

void turnon_led (int led, int* is_led_on) {
    keypad.illuminate(led, 0, 0, 255); // blue
    keypad.update();
    *is_led_on = 1;
}

void turnoff_led(int led, int* is_led_on) {
    keypad.illuminate(led, OFF_COLOR, OFF_COLOR, OFF_COLOR);
    keypad.update();
    *is_led_on = 0;
}

void flash_status(int led, int correct) {
    if (correct) {
        keypad.illuminate(led, 0, 255, 0); // green
    }
    else {
        keypad.illuminate(led, 255, 0, 0); // red
    }
    keypad.update();
    sleep_ms(500);
}

uint16_t get_buttons(void) {
    return keypad.get_button_states();
}

int button_pressed(uint16_t cur_states, uint16_t prev_states) {
    uint16_t changed_buttons = cur_states ^ prev_states;
    uint16_t pressed_buttons = cur_states & changed_buttons;

    for (int i = 0; i < keypad.NUM_PADS; i++) {
        if (pressed_buttons & (1 << i)) { 
            int pressed_button = i; 
            return pressed_button;
        }
    }

    return -1;
}

