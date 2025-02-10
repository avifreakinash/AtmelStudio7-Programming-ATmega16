/*
 * AddingButton.c
 *
 Button is connected to PB0 (PIN 1 of Atmega 16) and GND
 Led is connected to PD6 (PIN 20 of ATmega 16) with a 270R Resistor in series to GND
 
 Settings under Tools->Extended Tools of AtmelStudio7 for External Programmer (USBasp) :
 Title		:	USBasp Release
 Path		:	C:\avrdude-6.3-mingw32\avrdude.exe
 Arguments	:	-c USBasp -p m16 -U flash:w:$(ProjectDir)\Release\$(TargetName).hex:i

 * Created: 06-02-2025 18:41:14
 * Author : avinash
 */ 
	
#define F_CPU 1000000UL
#define DELAY_MS 500				    // Treated as a compile-time constant
#include <avr/io.h>
#include <util/delay.h>

void init_led( volatile uint8_t *, volatile uint8_t *, uint8_t );
void init_button( volatile uint8_t *, volatile uint8_t *, uint8_t );

int main(void)
{
	init_led(&DDRD, &PORTD, PIND6);		// Initialize LED on PORTD, PIN6
	init_led(&DDRD, &PORTD, PIND5);		// Initialize LED on PORTD, PIN6
	init_button(&DDRB, &PORTB, PINB0);  // Initialize Button on PORTB, PINB0
		
	while (1)
	{
				
		PORTD	^=	 (1 << PIND6) | (1 << PIND5);		// Toggle LED 
		
		//if ( bit_is_clear(PINB , 1) )	
		if(	!( PINB & (1<<PINB0))	)
		{
			_delay_ms(50);
		}
		else
		{
			_delay_ms(500);			
		}
	}
}

// Function to initialize LED pin 

void init_led( volatile uint8_t *ddr, volatile uint8_t *port, uint8_t pin) 
	{
	*ddr	|=	(1 << pin);		// Set pin as output
	*port	&=	 ~(1 << pin);	// Ensure LED is OFF initially
	}

// Function to initialize BUTTON pin 

void init_button(volatile uint8_t *ddr, volatile uint8_t *port, uint8_t pin)
{
	*ddr	&=	 ~(1 << pin);		// Set pin as Input
	*port	|=	 (1 << pin);		// Ensure pin is HIGH (PULLED UP) initially
}
