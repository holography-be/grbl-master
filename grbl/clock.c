#include "grbl.h"

// clock.c
//
// tick every 1ms
//

volatile uint32_t __ticks;

void clock_init()
{
	// init Timer5
	cli();
	TCCR5A = 0;
	TCCR5B = (1 << WGM52) | 0x03;	// CNC, Prescaler 3 (16MHz/64)
	TIMSK5 |= (1 << TOIE1) | (1 << OCIE5A);
	// doit compter jusqu'a 25000
	OCR5A = 25000;
	OCR5B = 0;
	TCNT5 = 0;
	__ticks = 0;
	sei();
}

void clock_start()
{

}

void clock_stop()
{

}

uint32_t getTick()
{
	return __ticks * 100;
}

ISR(TIMER5_COMPA_vect) {
	//PINH = (1 << 3);	// toogle D6
	TCNT5 = 0;
	__ticks++;
}