// main game loop
#include <stdio.h>

#include "game_ctrl.h"
#include "keypad_ctrl.h"
#include "pico/stdlib.h"

int main(void) {
  keypad_setup();
  for (int i = 0; i < 15; i++) {
    int on_led = generate_rand_led();
    flash_led(on_led, 500);
  }

  return 0;
}
