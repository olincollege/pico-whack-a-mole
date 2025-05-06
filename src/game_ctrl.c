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
  // NOLINTNEXTLINE(misc-include-cleaner)
  struct timeval tv_time;
  gettimeofday(&tv_time, NULL);
  const int mili_divider = 1000;
  return (tv_time.tv_sec * mili_divider) + (tv_time.tv_usec / mili_divider);
}

// NOLINTNEXTLINE(readability-non-const-parameter)
int correct_led_pressed(int* is_led_on, int target_led, int pressed) {
  // If nothing has been pressed, or target led is off return -1
  if (pressed == -1 || (*is_led_on == 0)) {
    return -1;
  }

  // Correct led pressed while LED was on
  return (*is_led_on && (target_led == pressed));
}
