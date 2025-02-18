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
void ProcessButtonPressed(int Button_id);
void ProcessButtonReleased(int Button_id);
void Blink_All_LEDs(volatile uint8_t *port);


int LED_Number[2] ;
int Pressed[2];			// Counter to hold the state of LEDs until button is pressed again
int Stream_of_Zeros[2];			// When button is Pressed, the micro controller button pin goes LOW and generates a streams of few "Zero and Ones" before finally coming to Zero, and
								// creating a stable stream of Zeros until the button is not Released
int Streams_of_Ones[2];			// When Button is Released, the micro controller button pin goes HIGH and generates a streams of few "Ones and Zeros" before finally coming to ONE, and
								// creating a stable stream of ONnes until the button is Released
int main(void)
{
		DDRD |= 0b01111111;		// Setting PINS as Output for LEDs
		DDRC |= 0b01111111;

		PORTD	=	 0x00;		// Setting LEDs OFF initially
		PORTC	=	 0x00;

		DDRB	&=	 ~(1<< PINB0) |  ~(1<< PINB1);	// Initialize BUTTON pin
		PORTB	|=	 (1 << PINB0) | (1 << PINB1) ;	// Ensure pin is HIGH (PULLED UP) initially
	
	while (1)
	{				
		if (  bit_is_clear(PINB , 0) )		ProcessButtonPressed(0);		 //  If Button is Pressed on SIDE 1  
		else	ProcessButtonReleased(0);										// if Button is Released 
		 
		if (  bit_is_clear(PINB , 1) )		ProcessButtonPressed(1);		 //  If Button is Pressed on SIDE 2
		else	ProcessButtonReleased(1);										// if Button is Released	
	}
}

void Blink_All_LEDs (volatile uint8_t *port)
{
	for( uint8_t i=0;i<5;i++)
	{
		*port = 0b11111111;
		_delay_ms(100);
		*port = 0b00000000;
		_delay_ms(100);
	}
}


void ProcessButtonPressed(int Button_id)
{
	Stream_of_Zeros[Button_id]++;					// Count a good amount of continuous ZEROs to be sure that button is actually pressed
	if (Stream_of_Zeros[Button_id] >= 500)
	{
		if (Pressed[Button_id] == 0)		// when counter = 0 from previous else call or initially	Pressed[0] == 0
												//															Pressed[1] == 0
		{
			Pressed[Button_id] = 1;			// set counter
			if (Button_id == 0)
			{
				PORTD |=	 1<<LED_Number[Button_id];	// LED_Number[0] 
				LED_Number[Button_id]++;
				if (LED_Number[Button_id] > 6)
				{
					Blink_All_LEDs( &PORTD );
					LED_Number[Button_id] = 0;
				}
			}
			if (Button_id == 1)
			{
				PORTC |=	 1<<LED_Number[Button_id];
				LED_Number[Button_id]++;
				if (LED_Number[Button_id] > 6)
				{
					Blink_All_LEDs( &PORTC );
					LED_Number[Button_id] = 0;
				}
			}
			
			
		}
		Stream_of_Zeros[Button_id] =0;
	}
}

 void ProcessButtonReleased(int Button_id)
 {
	 Streams_of_Ones[Button_id]++;			 // Count a good amount of continuous ONEs to be sure that button is actually released
	 if (Streams_of_Ones[Button_id] >= 500)
	 {
		 Pressed[Button_id] = 0;		// Reset counter
		 Streams_of_Ones[Button_id] = 0;
	 }
 }