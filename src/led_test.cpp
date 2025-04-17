#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"

#include "pico_rgb_keypad.hpp"

using namespace pimoroni;

PicoRGBKeypad pico_keypad;

int main() {
    pico_keypad.init(); // Set up GPIO
    pico_keypad.set_brightness(0.1f); // It's bright, trust us!

    pico_keypad.illuminate(0, 255, 0, 255);

    pico_keypad.update();
    sleep_ms(100);
}
