/*
 * RC5.c
 *
 * Created: 2014-02-12 20:32:10
 *  Author: Piotr
 *
 * Description: biblioteka do odbioru i dekodowania sygna��w z pilot�w RC5
 */ 
#include "RC5.h"

volatile uint8_t RC5_decoded_flag=0;
volatile uint8_t command, address, toggle;

uint8_t RC5_get(uint8_t* addr, uint8_t* comm, uint8_t* tog){
	if(RC5_decoded_flag){
		*addr=address;
		*comm=command;
		*tog=toggle;
		RC5_decoded_flag=0;
		return 1;		
	}else{
		return 0;
	}
}

void RC5_init(void){
	DDRD &= ~(1<<PB6);//pin ICP1 jako wej�cie z podci�ganiem
	PORTD |= (1<<PB6);

	//taktowanie z preskalera 16MHz/64, timer pracuje w trybie Input Capture (ICR)
	TCCR1B |=(1<<CS11)|(1<<CS10);//preskaler 64
	TCCR1B &= ~(1<<ICES1);//zbocze opadaj�ce do pierwszego wyzwolenia

	TIMSK |= (1<<TICIE1);//aktywowanie przerwania
	RC5_decoded_flag = 0;//zerowanie flagi
}

//dekodowanie w przerwaniu ICR1
ISR(TIMER1_CAPT_vect){
	
	static uint16_t LastICR;//ostatnia warto�� przechwycenia
	uint16_t PulseWidth;//szeroko�� impulsu mi�dzy zboczami
	static uint8_t  EdgeCt;//licznik zbocz
	static uint8_t  BitCt;//licznik bit�w odebranych
	static uint8_t  BitVal;//warto�� aktualnie przetwarzanego bitu
	static uint16_t RC5_tmp;//tymczasowa zmienna do kt�rej zapisywane s� kolejno odbierane bity

	PulseWidth = ICR1 - LastICR;//szeroko�� impulsu
	LastICR=ICR1;//zapisujemy dane tego zbocza

	TCCR1B ^= (1<<ICES1);//zmiana zbocza wyzwalaj�cego na przeciwne
	

	if(EdgeCt == 0){//je�li system dekodowania zosta� wyzerowany
		BitCt=0;//resetujemy wszystkie zmienne
		BitVal=1;
		RC5_tmp=0;
		TCCR1B &= ~(1<<ICES1);//zbocze opadaj�ce do pierwszego wyzwolenia
	}

	if(PulseWidth < MIN_HALF_BIT || PulseWidth > MAX_BIT){//impuls za d�ugi lub za kr�tki - reset dekodowania
		EdgeCt=0;
		}else if(PulseWidth >= MIN_HALF_BIT && PulseWidth <= MAX_HALF_BIT){//impuls kr�tki (1/2 CLK)
		if(EdgeCt % 2  == 0){//je�li to parzyste zbocze
			RC5_tmp<<=1;//to zapisujemy bit
			RC5_tmp|=(uint64_t)BitVal;
			BitCt++;//i zwi�kszamy licznik odebranych bit�w
		}
		EdgeCt++;//zwi�kszamy licznik zbocz
		}else{//przeciwny wypadek - (PulseWidth > MAX_HALF_BIT && PulseWidth < MAX_BIT)
		//czyli d�ugi impuls (1 CLK)
		BitVal^=0x01;//zmieniamy warto�� aktualnie przetwarzanego bitu
		RC5_tmp<<=1;//i zapisujemy bit
		RC5_tmp|=(uint64_t)BitVal;
		BitCt++;//i zwi�kszamy licznik odebranych bit�w
		EdgeCt+=2;//i zwi�kszamy licznik zbocz o 2 (dla porz�dku)
	}

	if(BitCt==13){//je�li odebrali�my ca�� ramk�
		EdgeCt=0;//resetujemy system do obdioru kolejnej
		if (RC5_decoded_flag == 0) {//i je�li poprzednie dekodowanie zosta�o odebrane w programie
			command = RC5_tmp & 0b0000000000111111;
			address = (RC5_tmp & 0b0000011111000000) >> 6;
			toggle = (RC5_tmp& 0b0000100000000000) >> 11;
			RC5_decoded_flag=1;//i przypisujemy fladze to czy zdekodowano poprawnie ramk�, czy nie
		}
	}

}