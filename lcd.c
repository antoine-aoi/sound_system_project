/*
 * lcd.c
 *
 *  Created on: Oct 8, 2024
 *      Author: Antoine Ashraf
 */


#include "lcd.h"


void lcd_write_command(uint16_t command)
{
	// Clear RS pin for command mode
	HAL_GPIO_WritePin(GPIOB, LCD_RS_Pin, GPIO_PIN_RESET);

	// Write command on data pins
	GPIOA->ODR = command;

	// Clear then set the WR pin to effectively write the data
	HAL_GPIO_WritePin(GPIOB, LCD_WR_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, LCD_WR_Pin, GPIO_PIN_SET);
}


void lcd_write_data(uint16_t data)
{
	// Set RS pin for data mode
	HAL_GPIO_WritePin(GPIOB, LCD_RS_Pin, GPIO_PIN_SET);

	// Write command on data pins
	GPIOA->ODR = data;

	// Clear then set the WR pin to effectively write the data
	HAL_GPIO_WritePin(GPIOB, LCD_WR_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, LCD_WR_Pin, GPIO_PIN_SET);
}


void lcd_address_set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    lcd_write_command(0x2a);
lcd_write_data(x1>>8);
lcd_write_data(x1);
lcd_write_data(x2>>8);
lcd_write_data(x2);

	lcd_write_command(0x2b);
lcd_write_data(y1>>8);
lcd_write_data(y1);
lcd_write_data(y2>>8);
lcd_write_data(y2);

lcd_write_command(0x2c);
}


void lcd_initialize(void)
{
	HAL_GPIO_WritePin(GPIOB, LCD_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(GPIOB, LCD_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(15);
	HAL_GPIO_WritePin(GPIOB, LCD_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(15);

	HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, LCD_WR_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin, GPIO_PIN_RESET);

	lcd_write_command(0xCB);
	lcd_write_data(0x39);
	lcd_write_data(0x2C);
	lcd_write_data(0x00);
	lcd_write_data(0x34);
	lcd_write_data(0x02);

	lcd_write_command(0xCF);
	lcd_write_data(0x00);
	lcd_write_data(0XC1);
	lcd_write_data(0X30);

	lcd_write_command(0xE8);
	lcd_write_data(0x85);
	lcd_write_data(0x00);
	lcd_write_data(0x78);

	lcd_write_command(0xEA);
	lcd_write_data(0x00);
	lcd_write_data(0x00);

	lcd_write_command(0xED);
	lcd_write_data(0x64);
	lcd_write_data(0x03);
	lcd_write_data(0X12);
	lcd_write_data(0X81);

	lcd_write_command(0xF7);
	lcd_write_data(0x20);

	lcd_write_command(0xC0);    //Power control
	lcd_write_data(0x23);   //VRH[5:0]

	lcd_write_command(0xC1);    //Power control
	lcd_write_data(0x10);   //SAP[2:0];BT[3:0]

	lcd_write_command(0xC5);    //VCM control
	lcd_write_data(0x3e);   //Contrast
	lcd_write_data(0x28);

	lcd_write_command(0xC7);    //VCM control2
	lcd_write_data(0x86);   //--

	lcd_write_command(0x36);    // Memory Access Control
	lcd_write_data(0x48);

	lcd_write_command(0x3A);
	lcd_write_data(0x55);

	lcd_write_command(0xB1);
	lcd_write_data(0x00);
	lcd_write_data(0x18);

	lcd_write_command(0xB6);    // Display Function Control
	lcd_write_data(0x08);
	lcd_write_data(0x82);
	lcd_write_data(0x27);

	lcd_write_command(0x11);    //Exit Sleep
	HAL_Delay(120);

	lcd_write_command(0x29);    //Display on
	lcd_write_command(0x2c);
}


void lcd_v_line(uint16_t x, uint16_t y, uint16_t l, uint16_t c)
{
  unsigned int i,j;
  lcd_write_command(0x02c); //write_memory_start
  HAL_GPIO_WritePin(GPIOB, LCD_RS_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin, GPIO_PIN_RESET);
  l=l+y;
  lcd_address_set(x,y,x,l);
  j=l*2;
  for(i=1;i<=j;i++)
  {
    lcd_write_data(c);
  }
  HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin, GPIO_PIN_SET);
}


void lcd_clear(uint16_t j)
{
	uint16_t i,m;
	lcd_address_set(0,0,240,320);
	//Lcd_Write_Com(0x02c); //write_memory_start
	//digitalWrite(LCD_RS,HIGH);
	HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin, GPIO_PIN_RESET);
	for(i=0;i<240;i++)
	{
		for(m=0;m<320;m++)
		{
			lcd_write_data(j>>8);
			lcd_write_data(j);
		}
	}
	HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin, GPIO_PIN_SET);
}
