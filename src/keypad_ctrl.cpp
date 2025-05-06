//NOLINTBEGIN(llvmlibc-implementation-in-namespace)

#include "keypad_ctrl.h"
#include "pico/stdlib.h"
#include "pico_rgb_keypad.hpp"

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

using namespace pimoroni;

//NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
PicoRGBKeypad keypad;

struct color {uint8_t r, g, b;};

const color RED  = {100, 0, 0};
const color GREEN  = {0, 100, 0};
const color PURPLE  = {100, 0, 100};
const color OFF  = {50, 50, 50};

const float BRIGHTNESS = 0.1F;

void keypad_setup(void) {
    keypad.init(); // Set up GPIO
    keypad.set_brightness(BRIGHTNESS);

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

//NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
void flash_status(int led, int correct) {
    const int flash_time = 400;
    if (correct == 1) {
        keypad.illuminate(led, GREEN.r, GREEN.g, GREEN.b); // green
        keypad.update();
        sleep_ms(flash_time);
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
    const uint16_t changed_buttons = cur_states ^ prev_states;
    const uint16_t pressed_buttons = cur_states & changed_buttons;

    for (int i = 0; i < keypad.NUM_PADS; i++) {
        //NOLINTNEXTLINE(hicpp-signed-bitwise)
        if ((pressed_buttons & (1 << i)) != 0) { 
            return i;
        }
    }

    return -1;
}

//NOLINTEND(llvmlibc-implementation-in-namespace)
