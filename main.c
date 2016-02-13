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
#include "lib/control_signals_conf.h" // Definicje portów
#include "lib/HD44780.h" // Ekran LCD
#include "lib/HD44780.c"
#include "lib/ADC.h" // Przetwornik analogowo-cyfrowy
#include "lib/ADC.c"


// Główna funkcja
int main(void)
{
// Konfiguracja portów
    Btn_DIR = 0x00;
    Btn_PORT = 0xff;
    wLED_DIR     |= (1<<wLED);
    wLED_PORT    |= (1<<wLED);
    
    
// Inicjalizacje modółów
    LCD_Initalize(); // Inicjalizacja LCD
    
    
// Ekran startowy
    LCD_GoTo(0,0); // Kursor w pierwszyej kolumnie pierwszego wiersza.
    LCD_WriteText("AOS 1");
    
    LCD_GoTo(0,1); // Kursor w pierwszej kolumnie drugiego wiersza.
    LCD_WriteText("version: 0.1");
    
    
//Główna pętla
    while(1)
    {
// MENU
      if (PIND == Btn_LeftMinus)  // L+
        {
            PORTC &= (~(1<<7));
            LCD_Clear();
            LCD_GoTo(0,0);
            LCD_WriteText("L+");
        }
      else if (PIND == Btn_LeftPlus) // L-
        {
            PORTC |= (1<<7);
            LCD_Clear();
            LCD_GoTo(0,0);
            LCD_WriteText("L-");
        }
      else if (PIND == Btn_PS) // P/S
        {
            LCD_Clear();
            LCD_GoTo(0,0);
            LCD_WriteText("P/S");
        }
      else if (PIND == Btn_S) // S
        {
          LCD_Clear();
          LCD_GoTo(0,0);
          LCD_WriteText("S");
        }
      else if (PIND == Btn_M) // M
        {
            LCD_Clear();
            LCD_GoTo(0,0);
            LCD_WriteText("M");
        }
      else if (PIND == Btn_Remote) // R
        {
            LCD_Clear();
            LCD_GoTo(0,0);
            LCD_WriteText("R");
        }
      else if (PIND == Btn_RightMinus) // R-
        {
            LCD_Clear();
            LCD_GoTo(0,0);
            LCD_WriteText("R-");
        }
      else if (PIND == Btn_RightPlus) // R+
        {
            LCD_Clear();
            LCD_GoTo(0,0);
            LCD_WriteText("R+");
        }
        _delay_ms(1); // Eliminacja migotania styków
   }
    
}