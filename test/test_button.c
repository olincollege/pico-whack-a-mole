#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <stdio.h>

#include "../src/game_ctrl.h"

Test(button, none_pressed) {
  uint16_t last_buttons = 0b0000000100000000;
  uint16_t cur_buttons = 0b0000000100000000;

  printf("%d", last_buttons);
}
