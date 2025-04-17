#pragma once

#include <detect.h>



/**
 * randomizing which button to select for turning on
 */


 button random();

 /**
  * turn on a button
  */
 void on();
  /**
  * turn on a button
  */
 void off();

 /**
  * game loop
  * turn something on, wait for 2 secs, turn off
  * for X amount of times (maybe condition is once all buttons in the matrix have been chosen 1?)
  */
void game_loop();

