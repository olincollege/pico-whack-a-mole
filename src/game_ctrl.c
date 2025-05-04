#include "game_ctrl.h"

#include <stdlib.h>
#include <sys/time.h>

const int MIN_LED = 0;
const int MAX_LED = 15;

int generate_rand_led(void) {
  int on_led = rand() % (MAX_LED - MIN_LED + 1) + MIN_LED;
  return on_led;
}

unsigned long get_time(void) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int correct_led_pressed(int* is_led_on, int target_led, int pressed) {
  // If nothing has been pressed, or target led is off return -1
  if (pressed == -1 || (*is_led_on == 0)) {
    return 0;
  }

  // If wrong led pressed
  if (target_led != pressed) {
    return 0;
  }

  // Correct led pressed while LED was on
  if (*is_led_on && (target_led == pressed)) {
    return 1;
  }
}
