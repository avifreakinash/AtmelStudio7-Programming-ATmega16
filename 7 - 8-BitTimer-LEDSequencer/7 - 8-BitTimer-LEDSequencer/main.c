/*
 * 7 - 8-BitTimer-LEDSequencer.c
 *
 * Created: 08-03-2025 20:30:28
 * Author : avinash
 
 7 LEDs are connected to PORTC and PORTD, respectively.

 The LEDs on PORTD illuminate sequentially, each lighting up every 1/7th of a second.
 Once all PORTD LEDs have lit up, the LEDs on PORTC follow the same pattern, with each turning on every second.

 The program utilizes an 8-bit Timer/Counter with a prescaler of 1024 to control LED timing.
 */


#include<avr/io.h>
#define F_CPU 1000000UL
int LED_Number[2];

int main(void)

{
	DDRD |= 0b01111111;		// Setting PINS as Output for LEDs
	DDRC |= 0b01111111;
	PORTD	=	 0x00;		// Setting LEDs OFF initially
	PORTC	=	 0x00;
	TCCR0 |= 1<<CS00 | 1<<CS02 ;	//  clkI/O/1024 (From prescaler)
	
	// clkI/O/1024 = 1000000/1024 = 976.5625 HZ
	// 976.5625 / 7 = 139.50
	while(1)
	{
		if (TCNT0 >= 139)  // 1/7th of a sec
		{
			TCNT0	=	0 ;					// Reset Timer
			PORTD	=	1<<LED_Number[0] ;	// Shift LED on PORT D
			LED_Number[0]++;
			if (LED_Number[0] > 7)
			{
				LED_Number[0] = 0;
				PORTD	 = 0x00;
				PORTC	=  1<<LED_Number[1] ;	// Shift LED on PORT C
				LED_Number[1] ++;
				if (LED_Number[1] > 7)
				{
					LED_Number[1] = 0;
					PORTC = 0x00;
				}
			}
		}
	}
}
