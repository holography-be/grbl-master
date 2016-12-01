#ifndef clock_h
#define clock_h 

void clock_init();
void clock_start();
void clock_stop();
uint32_t getTick();
void setBlink(uint8_t blinkDelay);

#endif