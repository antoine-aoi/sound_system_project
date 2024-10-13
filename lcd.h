/*
 * lcd.h
 *
 *  Created on: Oct 8, 2024
 *      Author: Reserch
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "gpio.h"

void lcd_write_command(uint16_t command);
void lcd_write_data(uint16_t data);
void lcd_address_set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void lcd_initialize(void);
void lcd_v_line(uint16_t x, uint16_t y, uint16_t l, uint16_t c);
void lcd_clear(uint16_t j);

#endif /* INC_LCD_H_ */
