#ifndef clock_h
#define clock_h 

void clock_init();
void clock_start();
void clock_stop();
uint32_t getTick();
void setBlinkDelay(uint8_t blinkDelay);
void startBlink(uint8_t led);
void stopBlink(uint8_t led);

#endif