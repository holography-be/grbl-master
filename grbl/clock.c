#include "grbl.h"

// clock.c
//
// tick every 1/10 s
//

volatile uint32_t __ticks;
volatile uint8_t __blink;
volatile uint8_t __blinkDelay = 5;
volatile uint8_t __ledBlinking = 0;

void clock_init()
{
	// init Timer5
	cli();
	TCCR5A = 0;
	TCCR5B = (1 << WGM52) | B0000100;	// CTC, Prescaler 3 (4000 Hz)
	TCCR5C = 0;
	TIMSK5 = 0;
	OCR5A = 6250;	// 1/10 sec
	TCNT5 = 0;
	__ticks = 0;
	__blink = 0;
	sei();
}



void clock_start()
{
	__ticks = 0;
	__blink = 0;
	TIMSK5 = (1 << OCIE5A);
}

void clock_stop()
{
	TIMSK5 = 0;		// disable all Timer 5 interrupts
}

uint32_t getTick()
{
	return __ticks * 100;
}

void setBlinkDelay(uint8_t blinkDelay) {
	__blinkDelay = blinkDelay;  // in 1/10th of second
	__blink = 0;	// reset blinking
}

void startBlink(uint8_t led) {
	__ledBlinking |= (1 << led);
}

void stopBlink(uint8_t led) {
	__ledBlinking &= ~(1 << led);
}

ISR(TIMER5_COMPA_vect) {
	__ticks++;
	if (__blink++ == 5) {
		LED_PIN = __ledBlinking;	// toogle leds
		__blink = 0;
	}
}