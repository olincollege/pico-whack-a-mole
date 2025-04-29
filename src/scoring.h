#pragma once

/**
 * args: unsigned int of 8 bytes (uint8_t) called val
 * sleep for 500 microseconds
 * enable_on int = val or addr of enable_bit
 * enable_off = val AND  enable_bit addr
 * i2c_write_blocking() to
 */
void lcd_toggle_enable(uint8_t val);

/**
 * args:
 *  nibble (int type uint8_t)
 *  mode (int)
 *
 * defines a temp data uint8_t to be either nibble, lcd_backlight (addr), or
 * mode ? data_mode:cmd_mode then uses i2c write_blocking lcd_toggle_enable
 */
void lcd_write_nibble(uint8_t nibble, int mode);

void lcd_send_byte(uint8_t val, int mode);
void lcd_init();
void lcd_send_string(const char* str);

/**
 * takes in its getting from detect about the result
 * if its success add 1
 * if fail -1
 * return intger
 */
int update_score(int result);

/**
 * print out the score in terminal or lcd screen
 */
void display();
