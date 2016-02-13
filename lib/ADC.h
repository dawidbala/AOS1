/*
 * ADC.h
 *
 * Created: 2014-02-12 16:46:21
 *  Author: Piotr
 */ 
#ifndef _ADC_H
#define _ADC_H

#include <avr/io.h>

//funkcje do obs³ugi ADC
void ADC_init(void);
uint16_t ADC_get(uint8_t channel);

#endif