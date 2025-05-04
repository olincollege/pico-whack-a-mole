// main game loop
#include <stdio.h>
#include <stdlib.h>

#include "game_ctrl.h"
#include "keypad_ctrl.h"
#include "pico/stdlib.h"
#include "scoring.h"

int main(void) {
  keypad_setup();
  lcd_setup();
  uint16_t cur_states = 0;
  uint16_t last_states = 0;
  int* score = (int*)malloc(sizeof(int));
  *score = 0;
  int* is_led_on = (int*)malloc(sizeof(int));
  *is_led_on = 0;
  int target_led = 0;
  int skip = 1;

  while (1) {
    target_led = generate_rand_led();
    unsigned long start_time = 0;
    unsigned long time_on = 500;

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

      if (pressed != -1) {
        if (correct_led_pressed(is_led_on, target_led, pressed)) {
          update_score(score);
          flash_status(pressed, 1);
          turnoff_led(pressed, is_led_on);
        } else {
          flash_status(pressed, 0);
          turnoff_led(target_led, is_led_on);
          turnoff_led(pressed, is_led_on);
        }
        break;
      }

      last_states = cur_states;
    }
  }
  free(is_led_on);
  free(score);
  return 0;
}
