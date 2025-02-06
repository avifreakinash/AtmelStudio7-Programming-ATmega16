/*
 * BlinkLed.c
 *
 * Created: 06-02-2025 17:16:15
 * Author : avinash
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
		
	DDRD   |=	 (1<< PIND6) ;
	PORTD  &=	~(1<< PIND6) ;
	
	while (1)
	{
		PORTD ^=  1<<PIND6;
		_delay_ms(500);
	}
}
