#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "pico/stdlib.h"

#include "pico_rgb_keypad.hpp"
#include "keypad_ctrl.h"

using namespace pimoroni;

PicoRGBKeypad keypad;

struct color {uint8_t r, g, b;};

color RED  = {100, 0, 0};
color GREEN  = {0, 100, 0};
color PURPLE  = {100, 0, 100};
color OFF  = {50, 50, 50};

void keypad_setup(void) {
    keypad.init(); // Set up GPIO
    keypad.set_brightness(0.1f);

    // Initialize all LEDs to a dim whitish while "off"
    for(int i = 0; i < keypad.NUM_PADS; i++) {
        keypad.illuminate(i, OFF.r, OFF.g, OFF.b);
    }
    keypad.update();
}

void turnon_led (int led, int* is_led_on) {
    keypad.illuminate(led, PURPLE.r, PURPLE.g, PURPLE.b);
    keypad.update();
    *is_led_on = 1;
}

void turnoff_led(int led, int* is_led_on) {
    keypad.illuminate(led, OFF.r, OFF.g, OFF.b);
    keypad.update();
    *is_led_on = 0;
}

void flash_status(int led, int correct) {
    if (correct) {
        keypad.illuminate(led, GREEN.r, GREEN.g, GREEN.b); // green
        keypad.update();
        sleep_ms(400);
    }
    else {
        for(int i = 0; i < keypad.NUM_PADS; i++) {
            keypad.illuminate(i, RED.r, RED.g, RED.b); // everything red
            keypad.update();
        }
    }
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

