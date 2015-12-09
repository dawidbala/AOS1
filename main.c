//
//  main.c
//  AVRTest
//
//  Created by David on 02.12.2015.
//
//

#include "avr_compiler.h"

//#define ledPin_bm   (1 << 0)
//#define ledPort     PORTC
//#define ledDDR      DDRC


int main(void){
    
    DDRC = 0xFF;
    PORTC = 0x80;
    _delay_ms(1000);
    
    
    
    
}