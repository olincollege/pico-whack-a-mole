// game control file
#pragma once

/**
 * Generate a random integer representing an LED on the keypad between
 * MIN_LED (0) and MAX_LED (15)
 *
 * @return An int representing a random LED to turn on
 */
int generate_rand_led();

// when a button is pressed, check to see it matches the random number
