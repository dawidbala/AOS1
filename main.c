//
//  main.c
//  AOS1
//
//  Created by David on 02.12.2015.
//


#include "lib/avr_compiler.h"
#include <avr/io.h>
#include <util/delay.h>
#include "lib/lcd.c"


//#define ledPin_bm   (1 << 0)
//#define ledPort     PORTC
//#define ledDDR      DDRC


int main(void){
    
    lcd_init();
    
    while(1) {
        
        lcd_string("AOS 1 0.1.1");
        PORTC ^= (1<<PC7);
        _delay_ms(500);
       }

}