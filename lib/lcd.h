/*
 * lcd.h
 */

#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>

#define LCD_PORT	PORTC

#define LCD_DDR		DDRC

#define LCD_RS		PC5
#define LCD_E		PC4
#define LCD_D4		PC3
#define LCD_D5		PC2
#define LCD_D6		PC1
#define LCD_D7		PC0
#define LED         PC7

inline void lcd_half( uint8_t data );
void lcd_byte( uint8_t byte );
void lcd_cmd( uint8_t cmd );
void lcd_data( uint8_t data );
void lcd_string( char * string );
void lcd_init();
void lcd_cls();
void lcd_locate( uint8_t x, uint8_t y);
void led(void);

#endif /* LCD_H_ */