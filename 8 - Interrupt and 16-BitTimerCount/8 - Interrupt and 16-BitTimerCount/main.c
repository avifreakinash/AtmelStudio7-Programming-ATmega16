/*
 * 8 - Interrupt and 16-BitTimerCount.c
 *
 * Created: 09-03-2025 15:41:50
 * Author : avinash
 
  
 The program utilizes 16-bit Timer/Counter (TCNT1) with a prescaler of 64 to create "1-second" interval. The LEDs toggles every second ( 1 sec ON, 1 sec OFF).
 TCNT1 is a 16-Bit Register (Timer/Counter) that can count up to 2^16 or 0-65535.
  
 The Output Compare Register (OCR1A) is 16-bit in size.
 
 CTC (Clear Timer on Compare Match) Mode : The OCR1A Register value is continuously compared with the Counter Value (TCNT1). The match is used to clear (reset) 
 the timer (TCNT1) and generate an output compare interrupt.
 
 TIMSK : ( Timer/Counter Interrupt Mask Register ) contains interrupt control bits for Timer/Counters.
 
 OCIE1A : (Output Compare A Match Interrupt Enable) When this bit is written to one, and the I-flag in the Status Register is set (interrupts globally enabled), 
 the Timer/Counter1 Output Compare A match interrupt is enabled. The corresponding Interrupt Vector is executed when the OCF1A Flag, located in TIFR, is set.
 
 OCF1A : ( Timer/Counter1, Output Compare A Match Flag ) This flag is set in the timer clock cycle after the counter (TCNT1) value matches the Output Compare Register A (OCR1A). 
 OCF1A is automatically cleared when the Output Compare Match A Interrupt Vector is executed. Alternatively, OCF1A can be cleared by writing a logic one to its bit location.
 
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
int main (void)
{
	sei();						// GLOBAL INTERRUPT ENABLE

	DDRD	|=	0b01111111;		// Setting PINS as Output for LEDs
	PORTD	=	0x00;			// Setting LEDs OFF initially
	
	TCCR1B	|=	1<<WGM12 | 1<<CS10 | 1<<CS11;	//	WGM12- CTC MODE 
												//	CS10 and CS11 - Prescaler 64

	TIMSK	|=	1<<OCIE1A;			// TIMER INTERRUPT (OUTPUT CONTROL INTERRUPT ENABLE)
									// ACT AS A SWITCH TO ENABLE THE INTERRUPT WITH OCR1A
	
	OCR1A	=	15625;				// Set Compare Match Value for 1-second interval ; 1000000/64 = 15625

	while(1)
	{
	}
}

ISR(TIMER1_COMPA_vect)         // Timer1 Compare Match Interrupt Service Routine (ISR)
{
	PORTD	^=	0b01111111;
}