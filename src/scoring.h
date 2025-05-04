#pragma once
#include <stdint.h>


/**
 * Calls lcd_write_nibble twice to send four bits of the 8 bit val at a time.
 * The mode is the type of command being sent to the lcd screen 
 *  (defined CMD_MODE or DATA_MODE)
 * @param unsigned integer of 8 bits called val
 * @param integer called mode
 */
void lcd_send_byte(uint8_t val, int mode);

/**
 * Takes the nibble data and combines it with: 
 *  LCD_BACKLIGHT bit
 * and
 *  either the DATA_MODE or CMD_MODE
 * 
 * Calls the i2c_write_blocking (from i2c library) to send the data to the screen over i2c
 * Calls lcd_toggle_enable to tell the LCD to read the data
 *  
 * @param unsigned integer of 8 bits called nibble (in actual implentation use only 4 of these 8 bits --> see lcd_send_byte)
 * @param integer mode  either CMD_MODE or DATA_MODE
 *
 * defines a temp data uint8_t to be either nibble, lcd_backlight (addr), or
 * mode ? data_mode:cmd_mode then uses i2c write_blocking lcd_toggle_enable
 */
void lcd_write_nibble(uint8_t nibble, int mode);


/**
 * This creates a pulse signal, used to latch onto the data
 * LCD screen needs to be pulsed as it only reads data from the rising and falling edge of the pin
 * 
 * Creates two 8bit integers called enable_on and enable_off
 *  enable_on is either val or the ENABLE_BIT
 *  enable_off is val and NOT ENABLE_BIT
 * 
 * Calls i2c_write_blocking (i2c library) twice to send the high to low transition through i2c
 * 
 * @param unsigned integer of 8 bits called val 
 */
void lcd_toggle_enable(uint8_t val);

/**
 * 
 */
void lcd_init();

/**
 * 
 */
void lcd_send_string(const char* str);

/**
 * takes in its getting from detect about the result
 * if its success add 1
 * if fail -1
 * return intger
 */
void update_score(int* score);

/**
 * 
 */
void lcd_setup();
