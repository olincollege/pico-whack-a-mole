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
void keypad_setup(void);


/**
 * Function to flash an LED on and off.
 * 
 * @param led: The integer representing an LED button on the keypad to flash
 * @param time_on: An integer in ms representing the amount of time the LED 
 * will spend on and off
 */
void flash_led(int led, int time_on);

/**
 * Function to find which button 0-15 has been pressed. Only works for one press,
 * and returns only the first one from 0 to 15 if mulitple are pressed at the same time.
 * 
 * @param cur_states An unsigned 16-bit integer containing current button states, each bit
 * representing if the button is currently being pressed (1) or not (0)
 * @param prev_states An unsigned 16-bit integer containing previous button states
 * 
 * @return An integer (0-15) representing which button was pressed.
 */
int button_pressed(uint16_t cur_states, uint16_t prev_states);

/**
 * Function to get current button states.
 * 
 * @return An unsigned 16-bit integer containing current button states, each bit
 * representing if the button is currently being pressed (1) or not (0)
 */
uint16_t get_buttons(void);

#ifdef __cplusplus
}
#endif

// function for detecting when a button is pressed
