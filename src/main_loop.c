// main game loop
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "game_ctrl.h"
#include "keypad_ctrl.h"
#include "pico/stdlib.h"

unsigned long get_time() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int main(void) {
  keypad_setup();
  uint16_t cur_states = 0;
  uint16_t last_states = 0;
  int* is_led_on = (int*)malloc(sizeof(int*));
  *is_led_on = 0;
  int target_led = 0;

  while (1) {
    target_led = generate_rand_led();
    unsigned long start_time = 0;
    unsigned long time_on = 3000;

    while (1) {
      unsigned long now = get_time();

      if (!(*is_led_on)) {
        turnon_led(target_led, is_led_on);
        start_time = now;
      }

      if ((*is_led_on) && (now - start_time >= time_on)) {
        turnoff_led(target_led, is_led_on);
        break;
      }

      cur_states = get_buttons();
      int pressed = button_pressed(cur_states, last_states);

      if (*is_led_on && (target_led == pressed)) {
        // trigger the increase score function here
      }
      last_states = cur_states;
    }
  }
  free(is_led_on);

  return 0;
}
