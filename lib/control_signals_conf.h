// Buzzer
#define BUZ                 PB6

// Czewona dioda (workLed)
#define wLED                PC7
#define wLED_DIR            DDRC
#define wLED_PORT           PORTC

// Przyciski                // Pod PIND6 podpięty jest odbiornik IR (RC5)
#define Btn_DIR             DDRD
#define Btn_PORT            PORTD
#define Btn_LeftPlus        (!(PIND&(1<<PD7)))
#define Btn_LeftMinusPD     (!(PIND&(1<<PD6)))
#define Btn_LeftMinus       (!(PINB&(1<<PB0))) // PB0
#define Btn_PS              (!(PIND&(1<<PD5)))
#define Btn_S               (!(PIND&(1<<PD4)))
#define Btn_M               (!(PIND&(1<<PD3)))
#define Btn_Remote          (!(PIND&(1<<PD2)))
#define Btn_RightMinus      (!(PIND&(1<<PD1)))
#define Btn_RightPlus       (!(PIND&(1<<PD0))) // PD0
