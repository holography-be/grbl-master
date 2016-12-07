#include "grbl.h"

void leds_init()
{
	LED_PORT = 0;		// all led OFF
	LED_DDR = LED_MASK;	// all led output
}

void led_on(uint8_t led)
{
	LED_PORT |= (1 << led);
}

void led_off(uint8_t led)
{
	LED_PORT &= ~(1 << led);
}

void led_toggle(uint8_t led)
{
	LED_PIN |= (1 << led);
}

void all_led_on()
{
	LED_PORT = 0xFF;
}

void all_led_off()
{
	LED_PORT = 0;
}

void all_led_toggle()
{
	LED_PIN = 0xFF;
}

void led_blink(uint8_t led) {
	startBlink(led);
}

void led_blinkOff(uint8_t led) {
	stopBlink(led);
}