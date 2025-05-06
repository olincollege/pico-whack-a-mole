/**
 * Test to verify we are reading the correct button when pressed.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../src/game_ctrl.h"
#include "../src/keypad_ctrl.h"
#include "../src/scoring.h"
#include "pico/stdlib.h"

int main(void) {
  keypad_setup();
  lcd_setup();
  uint16_t cur_states = 0;
  uint16_t last_states = 0;
  int* is_led_on = (int*)malloc(sizeof(int));
  *is_led_on = 0;

  while (1) {
    cur_states = get_buttons();
    int pressed = button_pressed(cur_states, last_states);

    if (pressed == -1) {
      lcd_send_byte(0x01, 0);
      lcd_send_string("Nothing Pressed");
    } else {
      char buffer[16];
      turnon_led(pressed, is_led_on);
      lcd_send_byte(0x01, 0);  // Clear screen
      lcd_send_byte(0x80, 0);  // Line 1
      lcd_send_string("Button:");
      lcd_send_byte(0xC0, 0);  // Line 2
      snprintf(buffer, sizeof(buffer), "%d", pressed);
      lcd_send_string(buffer);

      sleep_ms(500);
      turnoff_led(pressed, is_led_on);
    }

    last_states = cur_states;
  }
  free(is_led_on);

  return 0;
}
