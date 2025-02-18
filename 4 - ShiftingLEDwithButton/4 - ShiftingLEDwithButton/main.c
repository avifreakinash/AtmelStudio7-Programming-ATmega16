/*
 * 4 - ShiftingLEDwithButton.c
 *
 * Created: 17-02-2025 23:02:35
 * Author : avinash
 *
  A Buttons is connected to PB0  (PIN 1 of Atmega 16) and GND.
  7 LEDs (PD0 - PD6) are connected, each in series with a 330 R resistor to GND.
  Pressing the Button shifts (glows) the LED from PD0 to PD6 
  
  Settings under Tools->Extended Tools of AtmelStudio7 for External Programmer (USBasp) :
  Title		:	USBasp Release
  Path		:	C:\avrdude-6.3-mingw32\avrdude.exe
  Arguments	:	-c USBasp -p m16 -U flash:w:$(ProjectDir)\Release\$(TargetName).hex:i
 *
*/

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

uint8_t LED ;
uint8_t count;						 
uint16_t Stream_of_Zeros;		// When button is Pressed, the micro controller button pin goes LOW and generates a streams of few "Zero and Ones" before finally coming to Zero, and
								// creating a stable stream of Zeros until the button is not Released
uint16_t Streams_of_Ones;		// When Button is Released, the micro controller button pin goes HIGH and generates a streams of few "Ones and Zeros" before finally coming to ONE, and
								// creating a stable stream of ONnes until the button is Released
int main(void)
{
		DDRD |= 0b01111111;		// Setting PINS as Output for LEDs
		PORTD	=	 0x00;		// Setting LEDs OFF initially
		
		DDRB	&=	 ~(1<< PINB0) ;	// Initialize BUTTON pin
		PORTB	|=	 (1 << PINB0) ;	// Ensure pin is HIGH (PULLED UP) initially
	
	while (1)
	{				
		if (  bit_is_clear(PINB , 0) )				//  If Button is Pressed  
		{
			Stream_of_Zeros++;
			if (Stream_of_Zeros >= 500)
			{	
				if(count == 0)		//	Temp variable to make sure loop executes only once - if this is not present, all LEDs will lit up with just one press,
									//  as streams of zero's still overflows 500 count. The count is Reset in else statement to initialize initial state of count =0  
				{
					count = 1;		//  Count is Set to execute this loop exactly once, to get button toggle effect
					PORTD |= 1<<LED;
					LED++;
					if (LED > 6)
					{
						for( uint8_t i=0;i<5;i++)
						{
							PORTD = 0b11111111;
							_delay_ms(100);
							PORTD = 0b00000000;
							_delay_ms(100);
						}
						LED = 0; 
					}
				}
				Stream_of_Zeros = 0;
			}
		}
		else											// if Button is Released 
		{
			Streams_of_Ones++;			 // Count a good amount of continuous ONEs to be sure that button is actually released
			if (Streams_of_Ones >= 500)
			{
				count = 0;		// Reset counter
				Streams_of_Ones = 0;
			}
		}
	}
}
		