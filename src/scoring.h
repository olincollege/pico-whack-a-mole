#pragma once
#include <stdint.h>

/**
 * Calls lcd_write_nibble twice to send four bits of the 8 bit val at a time.
 * The mode is the type of command being sent to the lcd screen
 *  (defined CMD_MODE or DATA_MODE)
 *
 * @param val unsigned integer of 8 bits
 * @param mode integer mode either CMD_MODE or DATA_MODE
 */
void lcd_send_byte(uint8_t val, int mode);

/**
 * Takes the nibble data and combines it with:
 *  LCD_BACKLIGHT bit
 * and
 *  either the DATA_MODE or CMD_MODE
 *
 * Calls the i2c_write_blocking (from i2c library) to send the data to the
 * screen over i2c Calls lcd_toggle_enable to tell the LCD to read the data
 *
 * @param nibble unsigned integer of 8 bits called nibble (in actual
 * implentation use only 4 of these 8 bits --> see lcd_send_byte)
 * @param mode integer mode either CMD_MODE or DATA_MODE
 *
 * Defines a temp data uint8_t to be either nibble, lcd_backlight (addr), or
 * mode ? data_mode:cmd_mode then uses i2c write_blocking lcd_toggle_enable
 */
void lcd_write_nibble(uint8_t nibble, int mode);

/**
 * This creates a pulse signal, used to latch onto the data
 * LCD screen needs to be pulsed as it only reads data from the rising and
 * falling edge of the pin
 *
 * Creates two 8bit integers called enable_on and enable_off
 *  enable_on is either val or the ENABLE_BIT
 *  enable_off is val and NOT ENABLE_BIT
 *
 * Calls i2c_write_blocking (i2c library) twice to send the high to low
 * transition through i2c
 *
 * @param val unsigned integer of 8 bits
 */
void lcd_toggle_enable(uint8_t val);

/**
 * Initializes the LCD by sending the required startup commands over I2C.
 *
 * Sets the LCD to 4-bit mode, 2-line display, display ON with cursor OFF,
 * entry mode set, and clears the display.
 *
 * No parameters.
 */
void lcd_init(void);

/**
 * Sends each character of a string one-by-one to the LCD screen
 * using lcd_send_byte in DATA_MODE. Used to display text.
 *
 * @param str const char pointer to a null-terminated string
 */
void lcd_send_string(const char* str);

/**
 * Increments the integer value pointed to by score and displays
 * the new score on the LCD.
 *
 * Uses sprintf to format "Your Score: X" into a buffer and sends it
 * with lcd_send_string.
 *
 * @param score Integer pointer to the score variable
 */
void update_score(int* score);

/**
 * Initializes the I2C pins and LCD screen.
 *
 * Calls stdio_init_all, configures I2C pins (SDA, SCL),
 * enables pull-up resistors, initializes I2C and LCD.
 *
 * Used at the beginning of the program to set up the screen.
 *
 * No parameters.
 */

void lcd_setup(void);

/**
 * Clears the LCD, displays a goodbye message with the final score,
 * waits a few seconds, and then clears the screen again.
 *
 * Uses lcd_send_byte to send clear and position commands.
 * Formats and displays "Your Score: X" and then a message telling user
 * which button resets the game.
 *
 * @param score Integer pointer to the final score
 */
void lcd_reset(int* score);
