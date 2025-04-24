// File for interacting with LED keypad
#pragma once

// make it so that C can use these functions
#ifdef __cplusplus
extern "C" {
    #include <cstdint>
#else
    #include <stdint.h>
#endif

void keypad_setup();

void flash_led(int led, int time_on);

#ifdef __cplusplus
}
#endif

// function for detecting when a button is pressed
