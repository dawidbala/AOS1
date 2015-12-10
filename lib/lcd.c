/*
 * lcd.c
 */

#include "lcd.h"
inline void lcd_half( uint8_t data ) {
    
    if( data & (1<<0)) LCD_PORT |= (1<<LCD_D4);
    else LCD_PORT &= ~(1<<LCD_D4);
    
    if( data & (1<<1)) LCD_PORT |= (1<<LCD_D5);
    else LCD_PORT &= ~(1<<LCD_D5);
    
    if( data & (1<<2)) LCD_PORT |= (1<<LCD_D6);
    else LCD_PORT &= ~(1<<LCD_D6);
    
    if( data & (1<<3)) LCD_PORT |= (1<<LCD_D7);
    else LCD_PORT &= ~(1<<LCD_D7);
    
    
}

void lcd_byte( uint8_t byte ) {
    
    LCD_PORT |= (1<<LCD_E);
    lcd_half( byte >> 4 );
    LCD_PORT &= ~(1<<LCD_E);
    
    
    LCD_PORT |= (1<<LCD_E);
    lcd_half( byte );
    LCD_PORT &= ~(1<<LCD_E);
    
    _delay_us(120);
}

void lcd_cmd( uint8_t cmd ) {
    
    LCD_PORT &= ~(1<<LCD_RS);
    lcd_byte( cmd );
}

void lcd_data( uint8_t data ) {
    
    LCD_PORT |= (1<<LCD_RS);
    lcd_byte( data );
}

void lcd_string( char * string ) {
    
    while( *string ) lcd_data( *string++ );
}

void lcd_cls() {
    lcd_cmd( 0x01 );
}

void lcd_locate( uint8_t y, uint8_t x ) {
    
    switch( y ) {
            
        case 0: y = 0x00; break;
        case 1: y = 0x40; break;
            
            
            
            lcd_cmd( (0x80+y+x) );
            
    }
}

void lcd_init() {
    
    LCD_DDR |= ( (1<<LCD_RS) | (1<<LCD_E) | (1<<LCD_D4) | (1<<LCD_D5) | (1<<LCD_D6) | (1<<LCD_D7));
    
    lcd_cmd( 0x06 );
    lcd_cmd( 0x0C );
    lcd_cmd( 0x17 );
    lcd_cmd( 0x28 );
    
    lcd_cls();
    
    _delay_us(200);
    
}

