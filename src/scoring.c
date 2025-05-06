#include "scoring.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "hardware/i2c.h"
#include "pico/stdlib.h"

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
i2c_inst_t* I2C_PORT = i2c1;

// LCD control constants
const uint8_t I2C_SDA_PIN = 6;
const uint8_t I2C_SCL_PIN = 7;
const uint8_t LCD_ADDR = 0x27;
const uint8_t LCD_BACKLIGHT = 0x08;
const uint8_t ENABLE_BIT = 0x04;
const uint8_t CMD_MODE = 0x00;
const uint8_t DATA_MODE = 0x01;

// LCD commands
const uint8_t INIT_CMD_1 = 0x30;
const uint8_t INIT_CMD_2 = 0x20;
const uint8_t DISPLAY_ON_CMD = 0x0C;
const uint8_t ENTRY_MODE_CMD = 0x06;
const uint8_t CLEAR_DISPLAY_CMD = 0x01;
const uint8_t LINE_1_CMD = 0x80;
const uint8_t LINE_2_CMD = 0xC0;

// timing constants
const uint32_t LCD_TOGGLE_DELAY_US = 500;
const uint32_t LCD_RESET_DELAY_MS = 2;
const uint32_t LCD_INIT_DELAY_MS_1 = 50;
const uint32_t LCD_INIT_DELAY_MS_2 = 5;
const uint32_t LCD_RESET_TIME_MS = 3000;

// more constants to aboid magic number warnings
const uint8_t LCD_NIBBLE_MASK = 0xF0;
const uint32_t LCD_INIT_DELAY_US = 150;
const uint8_t LCD_2_LINE_MODE_CMD = 0x28;

const uint8_t BUFFER_SIZE = 32;

void lcd_send_byte(uint8_t val, int mode) {
  // NOLINTNEXTLINE(hicpp-signed-bitwise)
  lcd_write_nibble(val & LCD_NIBBLE_MASK, mode);
  // NOLINTNEXTLINE(hicpp-signed-bitwise)
  lcd_write_nibble((val << 4) & LCD_NIBBLE_MASK, mode);
}

void lcd_write_nibble(uint8_t nibble, int mode) {
  // NOLINTNEXTLINE(hicpp-signed-bitwise)
  uint8_t data = nibble | LCD_BACKLIGHT | (mode ? DATA_MODE : CMD_MODE);
  i2c_write_blocking(I2C_PORT, LCD_ADDR, &data, 1, false);
  lcd_toggle_enable(data);
}

void lcd_toggle_enable(uint8_t val) {
  sleep_us(LCD_TOGGLE_DELAY_US);
  // NOLINTNEXTLINE(hicpp-signed-bitwise)
  uint8_t enable_on = val | ENABLE_BIT;
  // NOLINTNEXTLINE(hicpp-signed-bitwise)
  uint8_t enable_off = val & ~ENABLE_BIT;
  i2c_write_blocking(I2C_PORT, LCD_ADDR, &enable_on, 1, false);
  sleep_us(LCD_TOGGLE_DELAY_US);
  i2c_write_blocking(I2C_PORT, LCD_ADDR, &enable_off, 1, false);
  sleep_us(LCD_TOGGLE_DELAY_US);
}

void lcd_init(void) {
  sleep_ms(LCD_INIT_DELAY_MS_1);
  lcd_write_nibble(INIT_CMD_1, CMD_MODE);
  sleep_ms(LCD_INIT_DELAY_MS_2);
  lcd_write_nibble(INIT_CMD_1, CMD_MODE);
  sleep_us(LCD_INIT_DELAY_US);
  lcd_write_nibble(INIT_CMD_2, CMD_MODE);  // Set 4-bit mode

  lcd_send_byte(LCD_2_LINE_MODE_CMD, CMD_MODE);  // 2-line mode
  lcd_send_byte(DISPLAY_ON_CMD, CMD_MODE);       // Display ON, Cursor OFF
  lcd_send_byte(ENTRY_MODE_CMD, CMD_MODE);       // Entry mode
  lcd_send_byte(CLEAR_DISPLAY_CMD, CMD_MODE);    // Clear display
  sleep_ms(LCD_RESET_DELAY_MS);
}

void lcd_send_string(const char* str) {
  while (*str) {
    lcd_send_byte(*str++, DATA_MODE);
  }
}

void lcd_setup(void) {
  stdio_init_all();

  i2c_init(I2C_PORT, 100 * 1000);
  gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA_PIN);
  gpio_pull_up(I2C_SCL_PIN);

  lcd_init();
  lcd_send_string("ready...");
}

void update_score(int* score) {
  (*score) = (*score) + 1;
  char buffer[BUFFER_SIZE];

  lcd_send_byte(CLEAR_DISPLAY_CMD, CMD_MODE);  // Clear screen

  lcd_send_byte(LINE_1_CMD, CMD_MODE);  // Line 1
  lcd_send_string("Your Score:");

  lcd_send_byte(LINE_2_CMD, CMD_MODE);  // Line 2
  (void)snprintf(buffer, sizeof(buffer), "%d", *score);
  lcd_send_string(buffer);
}
// NOLINTNEXTLINE(readability-non-const-parameter)
void lcd_reset(int* score) {
  char buffer[BUFFER_SIZE];

  lcd_send_byte(CLEAR_DISPLAY_CMD, CMD_MODE);
  lcd_send_byte(LINE_1_CMD, CMD_MODE);

  (void)snprintf(buffer, sizeof(buffer), "Final Score: %d", *score);
  lcd_send_string(buffer);

  sleep_ms(LCD_RESET_TIME_MS);  // wait 3 seconds

  lcd_send_byte(CLEAR_DISPLAY_CMD, CMD_MODE);
  lcd_send_byte(LINE_1_CMD, CMD_MODE);
  lcd_send_string("Good Game!");
  lcd_send_byte(LINE_2_CMD, CMD_MODE);
  lcd_send_string("Press Button 0 to Restart!");
}
