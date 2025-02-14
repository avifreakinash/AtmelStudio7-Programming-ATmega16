/*
 * ButtonDebounce.c
 *
 * 
 Button is connected to PB0 (PIN 1 of Atmega 16) and GND
 Led is connected to PD6 and PD6 (PIN19 & PIN20 of ATmega 16) with a 270R Resistor in series to GND
 
 THIS PROGRAM TOGGLES THE LEDS ALTERNATIVELY ON BUTTON PRESSES
 
 Settings under Tools->Extended Tools of AtmelStudio7 for External Programmer (USBasp) :
 Title		:	USBasp Release
 Path		:	C:\avrdude-6.3-mingw32\avrdude.exe
 Arguments	:	-c USBasp -p m16 -U flash:w:$(ProjectDir)\Release\$(TargetName).hex:i
 
 * Created: 08-02-2025 13:26:58
 * Author : avinash
 */ 
	
#define F_CPU 1000000UL
#define DELAY_MS 500				    // Treated as a compile-time constant
#include <avr/io.h>
#include <util/delay.h>

void init_led( volatile uint8_t *ddr, volatile uint8_t *port, uint8_t pin, uint8_t InitialLedState) ; // InitialLedState : 0 (off) or 1 (on)
void init_button(volatile uint8_t *ddr, volatile uint8_t *port, uint8_t pin);

int main(void)
{
	init_led(&DDRD, &PORTD, PIND5,1);		// Initialize LED on PORTD, PIN5
	init_led(&DDRD, &PORTD, PIND6,0);		// Initialize LED on PORTD, PIN6
	init_button(&DDRB, &PORTB, PINB0);  // Initialize Button on PORTB, PINB0
	int Pressed_count = 0 ;				// Counter to hold the state of LEDs until button is pressed again 
	int Stream_of_Zeros = 0;			// When button is Pressed, the micro controller button pin goes LOW and generates a streams of few "Zero and Ones" before finally coming to Zero, and
										// creating a stable stream of Zeros until the button is not Released
	int Streams_of_Ones = 0;			// When Button is Released, the micro controller button pin goes HIGH and generates a streams of few "Ones and Zeros" before finally coming to ONE, and
										// creating a stable stream of ONnes until the button is Released
		
	while (1)
	{				
		//if ( bit_is_clear(PINB , 1) )	
		if(	!( PINB & (1<<PINB0))	)	// if bit is clear ( Button is Pressed ) 
		{
			Stream_of_Zeros++;					// Count a good amount of continuous ZEROs to be sure that button is actually pressed
			if (Stream_of_Zeros >= 500)  
				{								
					if (Pressed_count == 0)		// when counter = 0 
						{
						Pressed_count = 1;      // set counter
						PORTD	^=	 (1 << PIND5) | (1 << PIND6);  // Toggle Leds
						}
						Stream_of_Zeros =0;
				}
		}
		else	// if bit is NOT clear ( Button is Released )
		{
			Streams_of_Ones ++;					// Count a good amount of continuous ONEs to be sure that button is actually released
			if (Streams_of_Ones >= 500)
				{
					Pressed_count = 0;		// Reset counter
					Streams_of_Ones = 0;
				}
		}
	}
}

// Function to initialize LED pin 

void init_led( volatile uint8_t *ddr, volatile uint8_t *port, uint8_t pin, uint8_t InitialLedState ) 
	{
	*ddr	|=	(1 << pin);		// Set pin as output
	if (InitialLedState)	
	*port	|=	 (1 << pin);	// LED is ON initially
	else
	*port	&=	 ~(1 << pin);	// LED is OFF initially
	}

// Function to initialize BUTTON pin 

void init_button(volatile uint8_t *ddr, volatile uint8_t *port, uint8_t pin)
{
	*ddr	&=	 ~(1 << pin);		// Set pin as Input
	*port	|=	 (1 << pin);		// Ensure pin is HIGH (PULLED UP) initially
}
