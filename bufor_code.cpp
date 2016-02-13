/* Kod który może się przydać.
 
 
 
 int main (void
 }
 
     uint8_t prev_state = 0; // zmienna do zmiany stanu diody
 {
 ON OFF DIODA
 while(1)
{
    
    
    // DIODA LED
  if (PIND == 0x7F)
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
     }
    
       if (PIND == 0x7F)
     {
     PORTC &= (~(1<<7));
     }
     else if (PIND == 0xBF)
     {
     PORTC |= (1<<7);
     }
     
     _delay_ms(1);
}*/