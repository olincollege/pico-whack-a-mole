#include "game_ctrl.h"

const int MIN_LED = 0;
const int MAX_LED = 15;

int generate_rand_led() {
  int on_led = rand() % (MAX_LED - MIN_LED + 1) + MIN_LED;
  return on_led;
}
