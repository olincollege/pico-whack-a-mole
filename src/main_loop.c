// main game loop
#include "keypad_ctrl.h"
#include "pico/stdlib.h"

int main(void) {
  for (int i = 0; i < 5; i++) {
    keypad_setup();
    flash_led(0, 200);
  }
  return 0;
}
