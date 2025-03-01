/*
 * ButtonPress.h
 * Created: 28-02-2025 12:00:14
 * Author : Avinash
 */

#ifndef BUTTON_PRESS_H
#define BUTTON_PRESS_H

#include <avr/io.h>

#ifndef numberOfButtons
	#define numberOfButtons 8		// Define the number of buttons (modify as needed)
#endif

// Global Variables
volatile uint8_t count[numberOfButtons];		// Tracks button press state
uint16_t Stream_of_Zeros[numberOfButtons];		// When button is Pressed, the micro controller button pin goes LOW and generates a streams of few "Zero and Ones" before finally coming to Zero, and
												// creating a stable stream of Zeros until the button is not Released
uint16_t Streams_of_Ones[numberOfButtons];		// When Button is Released, the micro controller button pin goes HIGH and generates a streams of few "Ones and Zeros" before finally coming to ONE, and
												// creating a stable stream of ONnes until the button is Released

/*
 * Function: ButtonPressed
 * -----------------------
 * Detects and de-bounces a button press.
 * 
 * pinofButton:			PIN register corresponding to the button.
 * portBit:				Bit position of the button in the port.
 * confidence_Level:	Threshold count to confirm button press/release.
 *
 * Returns:
 *  1 if the button press is confirmed.
 *  0 otherwise; if the button release is confirmed.
 */
									
char ButtonPressed(uint8_t pinofButton, uint8_t portBit, uint16_t confidence_Level)	
{
	if (  bit_is_clear(pinofButton , portBit) )	// Check if the button is pressed (logic LOW)
	{
		Stream_of_Zeros[portBit]++;				// Count a good amount of continuous ZEROs to be sure that button is actually Pressed
		if (Stream_of_Zeros[portBit] >= confidence_Level)	// Indicator of a good button press
		{
			if(count[portBit] == 0)				// Temp variable to make sure loop executes only once. The count is Reset in else statement to initialize initial state of count =0
			{
				count[portBit] = 1;				// Count is Set to execute this loop exactly once, to get button toggle effect
				Stream_of_Zeros[portBit]= 0;	// Reset to Zero, so a new button press can be evaluated
				return 1;
			}
		}
	}
	else
	{
		Streams_of_Ones[portBit]++;				// Count a good amount of continuous ONEs to be sure that button is actually released
		if (Streams_of_Ones[portBit] >= confidence_Level)		// Confirm button release
		{
			count[portBit] = 0;					// Reset counter
			Streams_of_Ones[portBit] = 0;		// Reset to Zero, so a new button Release can be evaluated
		}
	}
	return 0;
}

#endif	// BUTTON_PRESS_H