/*
 * TheButtonGame.c
 *
 *
  2 Buttons are connected to PB0 & PB1 (PIN 1 and PIN 2 of Atmega 16) and GND.
  A total of 14 LEDs are connected, with 7 LEDs on PD0 to PD6 and 7 LEDs on PC0 to PC6, each in series with a 330 R resistor to GND.
  Each button controls either of the PORT LEDs. Pressing either Button increases the LED count (glow) of respective PORT/side.
  2 Players are needed to press the button. Whoever presses the button fast to light up all the 7 LEDs on his PORT/side wins the game.
  
  Settings under Tools->Extended Tools of AtmelStudio7 for External Programmer (USBasp) :
  Title		:	USBasp Release
  Path		:	C:\avrdude-6.3-mingw32\avrdude.exe
  Arguments	:	-c USBasp -p m16 -U flash:w:$(ProjectDir)\Release\$(TargetName).hex:i
 
 * Created: 12-02-2025 11:00:14
 * Author : avinash
 */ 
	
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

void ProcessButtonPress(volatile uint8_t button_id);
void ProcessButtonRelease(volatile uint8_t button_id);
void Blink_port_LEDs (volatile uint8_t *port);
void Reset_all_LED_Counter ();

uint8_t LED[2] ;
volatile uint8_t count[2];
uint16_t Stream_of_Zeros[2];		// When button is Pressed, the micro controller button pin goes LOW and generates a streams of few "Zero and Ones" before finally coming to Zero, and
									// creating a stable stream of Zeros until the button is not Released
uint16_t Streams_of_Ones[2];		// When Button is Released, the micro controller button pin goes HIGH and generates a streams of few "Ones and Zeros" before finally coming to ONE, and
									// creating a stable stream of ONnes until the button is Released

int main(void)
{
	DDRD |= 0b01111111;		// Setting PINS as Output for LEDs
	DDRC |= 0b01111111;
	PORTD	=	 0x00;		// Setting LEDs OFF initially
	PORTC	=	 0x00;
	
	DDRB	&=	 ~( (1<< PINB0) | (1<< PINB1) );	// Initialize BUTTON pin
	PORTB	|=	 (1 << PINB0) | (1 << PINB1) ;	// Ensure pin is HIGH (PULLED UP) initially
	
	while (1)
	{
		if (  bit_is_clear(PINB , 0) )	ProcessButtonPress(0);		//  If Button is Pressed
		else	ProcessButtonRelease(0);							//  if Button is Released
		
		if (  bit_is_clear(PINB , 1) )	ProcessButtonPress(1);
		else	ProcessButtonRelease(1);
	}
}


void ProcessButtonPress(uint8_t button_id)
{
	Stream_of_Zeros[button_id]++;
	if (Stream_of_Zeros[button_id] >= 500)
	{
		if(count[button_id] == 0)		//	Temp variable to make sure loop executes only once - if this is not present, all LEDs will lit up with just one press,
										//  as streams of zero's still overflows 500 count. The count is Reset in else statement to initialize initial state of count =0
		{
			count[button_id] = 1;		//  Count is Set to execute this loop exactly once, to get button toggle effect
			
			if(button_id == 0)
			{
				PORTD |= 1<<LED[0];		//	Shift Leds of PORT D
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
				PORTC |= 1<<LED[1];		//	Shift Leds of PORT C
				LED[1]++;
				if (LED[1] > 6)
				{
					Blink_port_LEDs (&PORTC);
					Reset_all_LED_Counter ();
					PORTD = 0b00000000;
				}
			}
		}
		Stream_of_Zeros[button_id] = 0;
	}
}

void ProcessButtonRelease(uint8_t button_id)
{
	Streams_of_Ones[button_id]++;			 // Count a good amount of continuous ONEs to be sure that button is actually released
	if (Streams_of_Ones[button_id] >= 500)
	{
		count[button_id] = 0;		// Reset counter
		Streams_of_Ones[button_id] = 0;
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