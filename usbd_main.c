#include <board_init.h>
#include <boot.h>
#include <delay.h>
#include <error.h>
#include <irq.h>
#include <usbd_configure.h>
#include <usbd_power.h>
#include <usbd_api.h>
#include <board_def.h>
#include <pwr_periph.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <motor.h>
typedef uint8_t bool;
#define true 1
#define false 0

#define MOTOR_M2	(1UL<<5)
#define MOTOR_M1	(1UL<<6)
#define MOTOR_M0	(1UL<<7)
#define MOTOR1_STEP	(1UL<<3)
#define MOTOR1_DIR	(1UL<<4)
#define MOTOR2_STEP	(1UL<<1)
#define MOTOR2_DIR	(1UL<<2)
#define MOTOR3_STEP	(1UL<<(8+7))
#define MOTOR3_DIR	(1UL<<0)
#define MOTOR1_ENABLE	(1UL<<(8+6))
#define MOTOR2_ENABLE	(1UL<<(8+5))
#define MOTOR3_ENABLE	(1UL<<(8+4))
static volatile int8_t stop=1;
static uint32_t delay=10000/2;
 uint8_t motor_number=1;

uint8_t i = 0;
bool step=false;

void hc_setbits(uint32_t data);
void hc_clearbits(uint32_t data);
void hc_tooglebits(uint32_t data);
void hc_outbits(uint32_t data);
uint32_t hc_getbits(void);
void hc_init();



void motor_mode12(void)
{
  hc_outbits((hc_getbits()&(~(MOTOR_M0|MOTOR_M1|MOTOR_M2)))|MOTOR_M0);
}
void motor_mode14(void)
{
  hc_outbits((hc_getbits()&(~(MOTOR_M0|MOTOR_M1|MOTOR_M2)))|MOTOR_M1);
}
void motor_mode18(void)
{
  hc_outbits((hc_getbits()&(~(MOTOR_M0|MOTOR_M1|MOTOR_M2)))|MOTOR_M0|MOTOR_M1);
}
void motor_mode116(void)
{
  hc_outbits((hc_getbits()&(~(MOTOR_M0|MOTOR_M1|MOTOR_M2)))|MOTOR_M2);
}
void motor_mode132(void)
{
  hc_outbits((hc_getbits()&(~(MOTOR_M0|MOTOR_M1|MOTOR_M2)))|MOTOR_M0|MOTOR_M2);
}
void motor_modegfull(void)
{
  hc_outbits((hc_getbits()&(~(MOTOR_M0|MOTOR_M1|MOTOR_M2))));
}
void motor_left(void)
{
    stop=1;
    if(motor_number==1)
    {
	hc_setbits(MOTOR1_DIR);
    }else if(motor_number==2)
      {
  	hc_setbits(MOTOR2_DIR);
      }if(motor_number==3)
	    {
		hc_setbits(MOTOR3_DIR);
	    }
}
void motor_right(void)
{
    stop=1;
    if(motor_number==1)
    {
	hc_clearbits(MOTOR1_DIR);
     }else
       if(motor_number==2)
          {
      	hc_clearbits(MOTOR2_DIR);
           }else  if(motor_number==3)
             {
         	hc_clearbits(MOTOR3_DIR);
              }
}
void motor_stop(void)
{
	stop=0;
}
void motor_speed_up(void)
{
	delay-=30;
}
void motor_speed_down(void)
{
	delay+=30;
}
void motor_step(void)
{
  if(motor_number==1)
  {
      hc_tooglebits(MOTOR1_STEP);
  }else
    if(motor_number==2)
     {
         hc_tooglebits(MOTOR2_STEP);
     }
    else
      if(motor_number==3)
       {
           hc_tooglebits(MOTOR3_STEP);
       }

}
////////////////////////////////////////////////
//////////////74HC595-driver////////////////////
static uint32_t hc_out=0;

void hc_tooglebits(uint32_t data)
{
  hc_out^=data;
  hc_outbits(hc_out);
}
void hc_setbits(uint32_t data)
{
  hc_out|=data;
  hc_outbits(hc_out);
}
void hc_clearbits(uint32_t data)
{
  hc_out&=~data;
  hc_outbits(hc_out);
}
uint32_t hc_getbits(void)
{
  return hc_out;
}
void hc_outbits(uint32_t data)
{
  hc_out=data;
  //GPIO_Pin_0-SHCP
  //GPIO_Pin_1-STCP
  //GPIO_Pin_2-OE
  //GPIO_Pin_3-DS

  GPIOA->BSRRH=GPIO_Pin_0|GPIO_Pin_1;
  int i=0;
  for(i=0;i<24;i++)
  {
	GPIOA->BSRRH=GPIO_Pin_0;
	if((data>>i)&0x01)
	{
	    GPIOA->BSRRL=GPIO_Pin_3;
	}else
	{
	    GPIOA->BSRRH=GPIO_Pin_3;
	}
	Delay(5);
	GPIOA->BSRRL=GPIO_Pin_0;
	Delay(5);

  }
  GPIOA->BSRRH=GPIO_Pin_0;
  GPIOA->BSRRL=GPIO_Pin_1;
  Delay(5);
  GPIOA->BSRRH=GPIO_Pin_1;
}
void hc_init()
{
  hc_outbits(0xffffff);
  GPIOA->BSRRH=GPIO_Pin_2;
}
////////////////////////////////////////////////////////
int main(void)
{
	int sysclk;
	usb_speed_t speed;
	usb_phy_t phy;

	GetBootParams(&sysclk, &speed, &phy);
	AllPinsDisable();

	GPIO_InitTypeDef GPIO_InitStruct;


	LEDconfigure();

	ErrorResetable(USBDpreConfigure(speed, phy), 1);

	Delay(2000000);
	IRQprotectionConfigure();
	ErrorResetable(ClockConfigure(sysclk), 2);
	ErrorResetable(PWRconfigure(HIGH_IRQ_PRIO, 0, sysclk), 4);
	ErrorResetable(USBDconfigure(HIGH_IRQ_PRIO, 0, sysclk), 5);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3 ;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	hc_init();
	hc_clearbits(MOTOR1_ENABLE);
	hc_clearbits(MOTOR2_ENABLE);
	hc_clearbits(MOTOR3_ENABLE);
	for (;;)
	{

		if( step|| stop)
		{
		    GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
		    motor_step();
		    Delay(10*delay);
		    if(step) i++;
		    step=false;
		}
	}

}

