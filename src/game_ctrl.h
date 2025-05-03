// game control file
#pragma once

/**
 * Generate a random integer representing an LED on the keypad between
 * MIN_LED (0) and MAX_LED (15)
 *
 * @return An int representing a random LED to turn on
 */
int generate_rand_led(void);

/**
 * Fetches the current time in ms
 *
 * @return An unsigned long representing the current time in ms
 */
unsigned long get_time(void);
