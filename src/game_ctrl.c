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
