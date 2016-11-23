/*
thermistor.c
*/

#include "grbl.h"

uint8_t thermistor_init() {
	ADCSRA = bit(ADEN);									// turn ADC on
	ADCSRA |= bit(ADPS0) | bit(ADPS1) | bit(ADPS2);  // Prescaler of 128
	ADMUX = bit(REFS1) | bit(REFS0);     // External Ref (AREF)
	return 1;
}

int thermistor_read(uint8_t port) {
	ADMUX = bit(REFS1) | bit(REFS0) | (port & 0x15);
	while (bit_is_set(ADCSRA, ADSC)) {}
	int value = ADC;
	return value;
}

