
/*
 * BlinkLed.c
 * Led is connected to PD6 (PIN 20 of ATmega 16) with a 270R Resistor in series to GND
 
 Settings under Tools->Extended Tools of AtmelStudio7 for External Programmer (USBasp) :
 Title		:	USBasp Release
 Path		:	C:\avrdude-6.3-mingw32\avrdude.exe
 Arguments	:	-c USBasp -p m16 -U flash:w:$(ProjectDir)\Release\$(TargetName).hex:i

 * Created: 06-02-2025 13:45:53
 * Author : avinash
 */ 

#define F_CPU 1000000UL
#define DELAY_MS 100				    // Treated as a compile-time constant
#include <avr/io.h>
#include <util/delay.h>

void init_led( volatile uint8_t *, volatile uint8_t *, uint8_t );
void blink_led(	volatile uint8_t *, uint8_t pin);

int main(void)
{
	init_led(&DDRD, &PORTD, PIND6);		// Initialize LED on PORTD, PIN6
	while (1)
	{
		blink_led(&PORTD, PIND6);		// Blink LED 
	}
}

// Function to initialize LED pin (Flexible for any port)

void init_led( volatile uint8_t *ddr, volatile uint8_t *port, uint8_t pin) 
	{
	*ddr	|=	(1 << pin);		// Set pin as output
	*port	&=	 ~(1 << pin);	// Ensure LED is OFF initially
	}

// Function to blink LED (Flexible for any port)

void blink_led(	volatile uint8_t *port, uint8_t pin) 
	{
	*port	^=	 (1 << pin);	// Toggle LED
	_delay_ms(DELAY_MS);		// Delay for specified time 	
	}

