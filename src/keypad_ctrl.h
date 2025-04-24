// File for interacting with LED keypad
#pragma once

// make it so that C can use these functions
#ifdef __cplusplus
extern "C" {
    #include <cstdint>
#else
    #include <stdint.h>
#endif


/**
 * Function to initialize and setup keypad.
 */
void keypad_setup();


/**
 * Function to flash an LED on and off.
 * 
 * @param led: The integer representing an LED button on the keypad to flash
 * @param time_on: An integer in ms representing the amount of time the LED 
 * will spend on and off
 */
void flash_led(int led, int time_on);

#ifdef __cplusplus
}
#endif

// function for detecting when a button is pressed
