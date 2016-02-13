//
//  main.c
//  AOS1
//
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
    
   ADC_init();
    
    LCD_GoTo(0,0);//ustawiamy siÍ w pierwszej kolumnie i pierwszym wierszu
    LCD_WriteText("LCD ADC display");
    
    LCD_GoTo(0,1);//ustawiamy siÍ w pierwszej kolumnie i drugim wierszu
    LCD_WriteText("A0=     A1=    ");
    
    char buffer[6];
    uint16_t val;
    
    while(1)
    {
        val=ADC_get(0);//pobieram odczyt
        sprintf(buffer,"%04d",val);//konwertujÍ go na ciπg znakÛw i dopisujÍ zera
        LCD_GoTo(3,1);//ustawiam siÍ na poczπtku pola, w ktÛrym ma byÊ widoczny wynik
        LCD_WriteText(buffer);//wyúwietlam go (nadpisujÍ poprzedni)
        
        val=ADC_get(1);
        sprintf(buffer,"%04d",val);
        LCD_GoTo(11,1);
        LCD_WriteText(buffer);
    }
    
    
    
    
    
    
    
    
    
  //  while(1)
 //   {
      
        
        // DIODA LED
        /* if (PIND == 0x7F)
        {
            if(prev_state == 1)
            {
                PORTC ^= (1<<7);
            }
            prev_state = 0;
        }
        else
            {
                prev_state = 1;
            }*/
        
   /*     if (PIND == 0x7F)
        {
            PORTC &= (~(1<<7));
        }
        else if (PIND == 0xBF)
        {
            PORTC |= (1<<7);
        }
        
        _delay_ms(1);  */
  //  }
    
}