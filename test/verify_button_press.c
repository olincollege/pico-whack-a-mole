#include <stdio.h>
#include <stdlib.h>

#include "../src/game_ctrl.h"
#include "../src/keypad_ctrl.h"
#include "../src/scoring.h"
#include "pico/stdlib.h"

int main(void) {
  stdio_init_all();
  keypad_setup();
  lcd_setup();

  uint16_t cur_states = 0;
  uint16_t last_states = 0;
  int* is_led_on = (int*)malloc(sizeof(int));
  *is_led_on = 0;
  int target_led = 3;

  lcd_send_byte(0x01, 0);
  lcd_send_string("Test: Press LED 3");

  turnon_led(target_led, is_led_on);

  while (1) {
    cur_states = get_buttons();
    int pressed = button_pressed(cur_states, last_states);

    if (pressed != -1) {
      lcd_send_byte(0x01, 0);

      if (correct_led_pressed(is_led_on, target_led, pressed)) {
        lcd_send_string("PASS: Correct");
        flash_status(pressed, 1);
      } else {
        lcd_send_string("FAIL: Wrong Btn");
        flash_status(pressed, 0);
      }

      turnoff_led(target_led, is_led_on);
      break;
    }

    last_states = cur_states;
  }

  free(is_led_on);

  while (1) tight_loop_contents();
  return 0;
}
