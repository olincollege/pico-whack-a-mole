// main game loop
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game_ctrl.h"
#include "keypad_ctrl.h"
#include "pico/stdlib.h"
#include "scoring.h"

int RESET_BUTTON = 0;
int STARTUP_TIME_MS = 800;

int main(void) {
  keypad_setup();
  lcd_setup();
  srand(time_us_64());
  uint16_t cur_states = 0;
  uint16_t last_states = 0;
  int pressed = -1;

  int* score = (int*)malloc(sizeof(int));
  *score = 0;
  int* is_led_on = (int*)malloc(sizeof(int));
  *is_led_on = 0;
  int target_led = 0;

  unsigned long start_time = 0;
  unsigned long start_time_off = 0;
  unsigned long now = 0;
  unsigned long time_on = 500;
  unsigned long time_off = (rand() % (800 - 200 + 1)) + 200;

  int reset_state = 0;

  sleep_ms(STARTUP_TIME_MS);  // startup

  while (1) {
    // main loop
    target_led = generate_rand_led();
    start_time = get_time();

    while (!reset_state) {
      // time loop for turning one led on
      now = get_time();

      if (!(*is_led_on)) {
        turnon_led(target_led, is_led_on);
        start_time = now;
      }

      if ((*is_led_on) && (now - start_time >= time_on)) {
        turnoff_led(target_led, is_led_on);
        start_time_off = get_time();
        break;
      }

      cur_states = get_buttons();
      pressed = button_pressed(cur_states, last_states);

      if (pressed != -1) {
        if (correct_led_pressed(is_led_on, target_led, pressed)) {
          update_score(score);
          flash_status(pressed, 1);
          turnoff_led(pressed, is_led_on);
        } else {
          flash_status(pressed, 0);
          reset_state = 1;
          lcd_reset(score);
        }
        start_time_off = get_time();
        now = get_time();
        break;
      }
      last_states = cur_states;
    }

    while (!reset_state) {
      // time loop keeping led off
      if (now - start_time_off >= time_off) {
        break;
      }
      now = get_time();
    }

    while (reset_state) {
      // reset loop, waiting for reset button press
      cur_states = get_buttons();
      int pressed_reset = button_pressed(cur_states, last_states);
      if (pressed_reset == RESET_BUTTON) {
        reset_state = 0;
        keypad_setup();
        *score = 0;
        sleep_ms(STARTUP_TIME_MS);
      }
      last_states = cur_states;
    }
  }
  free(score);
  free(is_led_on);
  return 0;
}
