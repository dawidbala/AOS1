//
//  main.c
//  AOS1
//
//  Created by David on 02.12.2015.
//
/*

//#include "lib/avr_compiler.h"
#include <avr/io.h>
#include <util/delay.h>
#include "lib/lcd.c"
#include "lib/lcd.h"


//#define ledPin_bm   (1 << 0)
//#define ledPort     PORTC
//#define ledDDR      DDRC


int main(void){
    DDRD = 0x00;
    PORTD = 0xff;
    DDRC |= (1<<LED);
    PORTC |= (1<<LED);

  while(1) {
      
      
      if (PIND != 0xFF)
      {
          PORTC &= (~(1<<7));
      }
      else
      {
          PORTC |= (1<<7);
      };
      
      
  }
    
}*/


#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lib/avr_compiler.h"
#include "lib/lcd.c"
#include "lib/lcd.h"


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
    
    while(1)
    {
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
        
        if (PIND == 0x7F)
        {
            PORTC &= (~(1<<7));
        }
        else if (PIND == 0xBF)
        {
            PORTC |= (1<<7);
        }
        
        _delay_ms(1);
    }
    
}


/*
 //////////////
 
 int main(void){
 DDRD = 0x00;
 PORTD = 0xff;
 DDRC |= (1<<LED);
 PORTC |= (1<<LED);
 
 while(1) {
 
 
 if (PIND != 0xFF)
 {
 PORTC &= (~(1<<7));
 }
 else
 {
 PORTC |= (1<<7);
 };
 
 
 }
 
 
 
 */
 








     //   _delay_ms(500);

    //    PORTC ^= (1<<LED);
 
        
    //    _delay_ms(500);
        
        
        
        
        
        
    //   if(!(PORTD & 0x01)) PORTC = (1<<LED);
       // _delay_ms(80);
        
 //       PORTC ^= (1<<LED);
   // _delay_ms(3000);
  //      PORTC ^= (0<<LED);
    
      //  PORTC ^= (0<<LED);
        
    //   lcd_string("AOS 1 0.1.2");
        
        // if((PIND & 0x01)) PORTC ^= (0<<LED);
// if (!(PIND & 0x01)) PORTC ^= (1<<LED);
    //   PORTC ^= (0<<LED);
      // _delay_ms(1000);
     //   PORTC ^= (1<<LED);
          // _delay_ms(500);
     //
