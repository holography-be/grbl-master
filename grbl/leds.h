#ifndef leds_h
#define leds_h 

void leds_init();
void led_on(uint8_t led);
void led_off(uint8_t led);
void led_toggle(uint8_t led);
void all_led_on();
void all_led_off();
void all_led_toggle();
void led_blinkOn(uint8_t led);
void led_BlinkOff(uint8_t led);

#endif