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

/**
 * Returns if the correct led was pressed or not
 *
 * @param is_led_on An integer pointer that contains the status of the target
 * led 0 if off, 1 if on
 * @param target_led An integer representing the target led (0-15)
 * @param pressed An integer representing which LED was pressed (0-15), or -1 if
 * none
 *
 * @return An integer representing if the correct led was pressed (1) or not
 * (0), or -1 if none were pressed
 */

int correct_led_pressed(int* is_led_on, int target_led, int pressed);
