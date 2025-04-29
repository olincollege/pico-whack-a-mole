#include "scoring.h"

#include <stdio.h>
#include <string.h>

#include "hardware/i2c.h"
#include "pico/stdlib.h"

#define I2C_PORT i2c0
#define I2C_SDA 4
#define I2C_SCL 5
#define LCD_ADDR 0x27  // Often 0x27 or 0x3F

// Commands
#define LCD_BACKLIGHT 0x08
#define ENABLE_BIT 0x04
#define CMD_MODE 0x00
#define DATA_MODE 0x01

void lcd_send_byte(uint8_t val, int mode) {
  lcd_write_nibble(val & 0xF0, mode);
  lcd_write_nibble((val << 4) & 0xF0, mode);
}

void lcd_write_nibble(uint8_t nibble, int mode) {
  uint8_t data = nibble | LCD_BACKLIGHT | (mode ? DATA_MODE : CMD_MODE);
  i2c_write_blocking(I2C_PORT, LCD_ADDR, &data, 1, false);
  lcd_toggle_enable(data);
}

void lcd_toggle_enable(uint8_t val) {
  sleep_us(500);
  uint8_t enable_on = val | ENABLE_BIT;
  uint8_t enable_off = val & ~ENABLE_BIT;
  i2c_write_blocking(I2C_PORT, LCD_ADDR, &enable_on, 1, false);
  sleep_us(500);
  i2c_write_blocking(I2C_PORT, LCD_ADDR, &enable_off, 1, false);
  sleep_us(500);
}

void lcd_init() {
  sleep_ms(50);
  lcd_write_nibble(0x30, CMD_MODE);
  sleep_ms(5);
  lcd_write_nibble(0x30, CMD_MODE);
  sleep_us(150);
  lcd_write_nibble(0x20, CMD_MODE);  // Set 4-bit mode

  lcd_send_byte(0x28, CMD_MODE);  // 2-line mode
  lcd_send_byte(0x0C, CMD_MODE);  // Display ON, Cursor OFF
  lcd_send_byte(0x06, CMD_MODE);  // Entry mode
  lcd_send_byte(0x01, CMD_MODE);  // Clear display
  sleep_ms(2);
}

void lcd_send_string(const char* str) {
  while (*str) {
    lcd_send_byte(*str++, DATA_MODE);
  }
}

int main() {
  stdio_init_all();

  i2c_init(I2C_PORT, 100 * 1000);  // 100 kHz
  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA);
  gpio_pull_up(I2C_SCL);

  lcd_init();
  lcd_send_string("Hello!");

  while (1) tight_loop_contents();
}
