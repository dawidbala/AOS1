/*
 * ADC.c
 *
 * Created: 2014-02-12 16:46:07
 *  Author: Piotr
 */ 
#include "ADC.h"

void ADC_init(void){
	ADMUX |= (1<<REFS0);//ustawiam napi�cie odniesienia na AVCC (napi�cie zasilania uk�adu ~5V)
	ADCSRA |= (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);//ustawienie prescalera na 128 = cz�stotliwo�� taktowania 125kHz
	ADCSRA |= (1<<ADEN);//w��czenie przetwornika
	
}
uint16_t ADC_get(uint8_t channel){
	ADMUX=(ADMUX&0b11100000)|(channel&0b00011111);//ustawiam kana�
	ADCSRA |= (1<<ADSC);//rozpoczynam konwersj�
	while(ADCSRA&(1<<ADSC));//czekamy na zako�czenie tej konwersji
	return ADC;
}
