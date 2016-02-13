//
//  main.c
//  AOS1
//  version 0.1
//  Created by David on 02.12.2015.
//

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lib/avr_compiler.h"

//Obsługa modółów
#include "lib/control_signal_conf.h"

//LCD
#include "lib/HD44780.h"
#include "lib/ADC.h"
#include "lib/HD44780.c"
#include "lib/ADC.c"




//#define ledPin_bm  (1 << 0)
//#define ledPort    PORTC
//#define ledDDR      DDRC


int main(void)
{
    DDRD = 0x00;
    PORTD = 0xff;
   DDRC |= (1<<LED);
    PORTC |= (1<<LED);
    
    uint8_t prev_state = 0;
    
    
    LCD_Initalize();//inicjalizacja LCD
    
    LCD_GoTo(0,0);// kursor w pierwszyej kolumnie pierwszego wiersza
    LCD_WriteText("AOS 1");
    
    LCD_GoTo(0,1);//kursor w pierwszej kolumnie drugiego wiersza
    LCD_WriteText("version: 0.1");
    

   
    
    while(1)
    {
// MENU
      if (PIND == 0x7F)  // L+
        {
            PORTC &= (~(1<<7));
            LCD_Clear();
            LCD_GoTo(0,0);// kursor w pierwszyej kolumnie pierwszego wiersza
            LCD_WriteText("L+");
        }
      else if (PIND == 0xBF) // L-
        {
            PORTC |= (1<<7);
            LCD_Clear();
            LCD_GoTo(0,0);// kursor w pierwszyej kolumnie pierwszego wiersza
            LCD_WriteText("L-");
        }
      else if (PIND == 0xDF) // P/S
        {
            LCD_Clear();
            LCD_GoTo(0,0);// kursor w pierwszyej kolumnie pierwszego wiersza
            LCD_WriteText("P/S");
        }
      else if (PIND == 0xEF) // S
        {
          LCD_Clear();
          LCD_GoTo(0,0);// kursor w pierwszyej kolumnie pierwszego wiersza
          LCD_WriteText("S");
        }
      else if (PIND == 0xF7) // M
        {
            LCD_Clear();
            LCD_GoTo(0,0);// kursor w pierwszyej kolumnie pierwszego wiersza
            LCD_WriteText("M");
        }
      else if (PIND == 0xFB) // R
        {
            LCD_Clear();
            LCD_GoTo(0,0);// kursor w pierwszyej kolumnie pierwszego wiersza
            LCD_WriteText("R");
        }
      else if (PIND == 0xFD) // R-
        {
            LCD_Clear();
            LCD_GoTo(0,0);// kursor w pierwszyej kolumnie pierwszego wiersza
            LCD_WriteText("R-");
        }
      else if (PIND == 0xFE) // R+
        {
            LCD_Clear();
            LCD_GoTo(0,0);// kursor w pierwszyej kolumnie pierwszego wiersza
            LCD_WriteText("R+");
        }
        _delay_ms(1); // Eliminacja migotania styków
   }
    
}