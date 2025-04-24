#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"

#include "pico_rgb_keypad.hpp"
#include "keypad_ctrl.h"

using namespace pimoroni;

PicoRGBKeypad keypad;

void keypad_setup() {
    keypad.init(); // Set up GPIO
    keypad.set_brightness(0.1f);
}

void flash_led(int led, int time_on) {
    keypad.illuminate(led, 255, 0, 255);
    keypad.update();
    sleep_ms(time_on);

    keypad.clear();
    keypad.update();
    sleep_ms(time_on);
}
