// main game loop
#include <stdio.h>

#include "game_ctrl.h"
#include "keypad_ctrl.h"
#include "pico/stdlib.h"

int main(void) {
  keypad_setup();
  uint16_t cur_states = 0;
  uint16_t last_states = 0;

  while (1) {
    cur_states = get_buttons();
    int on = button_pressed(cur_states, last_states);
    last_states = cur_states;

    sleep_ms(100);
  }
  // for (int i = 0; i < 15; i++) {
  //   int on_led = generate_rand_led();
  //   flash_led(on_led, 500);
  // }

  return 0;
}
