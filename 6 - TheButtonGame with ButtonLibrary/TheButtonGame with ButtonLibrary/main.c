/*
 * TheButtonGame with ButtonLibrary.c
 *
 * Created: 28-02-2025 13:01:35
 * Author : avinash
 */ 

#define numberOfButtons 2
#define F_CPU 1000000UL
#include"ButtonPress.h"
#include <util/delay.h>

void Blink_port_LEDs (volatile uint8_t *port);
void ProcessButtonPress(uint8_t button_id);
void Reset_all_LED_Counter ();
uint8_t LED[2] ;

int main(void)
{
	DDRD |= 0b01111111;		// Setting PINS as Output for LEDs
	DDRC |= 0b01111111;
	PORTD	=	 0x00;		// Setting LEDs OFF initially
	PORTC	=	 0x00;
	
	DDRB	&=	 ~( (1<< PINB0) | (1<< PINB1) );	// Initialize BUTTON pin
	PORTB	|=	 (1 << PINB0) | (1 << PINB1) ;		// Ensure pin is HIGH (PULLED UP) initially
	
	while (1)
	{
		if (  ButtonPressed(PINB , 0, 500) )	ProcessButtonPress(0);		//  If Button is Pressed
		if (  ButtonPressed(PINB , 1, 500) )	ProcessButtonPress(1);
		
	}
}


void ProcessButtonPress(uint8_t button_id)
{
		
		if(button_id == 0)
			{
				
				PORTD |= 1<<LED[0];		//	Shift LEDs of PORT D
				LED[0]++;
				if (LED[0] > 6)
				{
					Blink_port_LEDs (&PORTD);
					Reset_all_LED_Counter ();
					PORTC = 0b00000000;
				}
			}
		if(button_id == 1)
			{
				PORTC |= 1<<LED[1];		//	Shift LEDs of PORT C
				LED[1]++;
				if (LED[1] > 6)
				{
					Blink_port_LEDs (&PORTC);
					Reset_all_LED_Counter ();
					PORTD = 0b00000000;
				}
			}
		
	
}


void Blink_port_LEDs (volatile uint8_t *port)
{
	for( uint8_t i=0;i<5;i++)
	{
		*port = 0b11111111;
		_delay_ms(100);
		*port = 0b00000000;
		_delay_ms(100);
	}
}

void Reset_all_LED_Counter ()
{
	LED[1] = 0;
	LED[0] = 0;
}