/*
  laser.c
*/
  
#include "grbl.h"

#define Laser_Temp_PIN		A0 // ANALOG
#define LaserPower_PIN		9  // PWM
#define LaserPWM			OCR2B

//#define LASERLEVEL_DDR	DDRL
//#define LASERLEVEL_PIN	PINL
//#define LASERLEVEL_PORT	PORTL
//#define LASERLEVEL_REQUEST	50	// Send signal to Nano that we wish send datas
//#define LASERLEVEL_STATUS	51	// Signal send by Nano (HIGH = Ready, LOW = Busy)
//#define Laser_Start_Sequence	 Laser_Peltier_PIN,Laser_Driver_PIN,Laser_Diode_PIN
//#define Laser_Stop_Sequence		 Laser_Diode_PIN,Laser_Driver_PIN,Laser_Peltier_PIN
//#define Laser_Emergency_Sequence Laser_Diode_PIN,Laser_Driver_PIN // On laisse le Peltier 
//#define Laser_Delai_Sequence	 2000

const uint8_t _startSequence[3] = { Laser_Start_Sequence };
const uint8_t _stopSequence[3] = { Laser_Stop_Sequence };
const uint8_t _emergencySequence[2] = { Laser_Emergency_Sequence };
const uint8_t _delai = Laser_Delai_Sequence;

volatile uint8_t waiting;

uint8_t laser_init() {
	// init Timer
	cli();
	TIMSK5 = 0;
	TCCR5A = 0;
	TCCR5B = bit(WGM52) | bit(CS50) | bit(CS52);  // 1024 prescaler
	sei();
	BLINK_DDR |= (1 << BLINK_BIT);
	BLINK_PORT &= ~(1 << BLINK_BIT);
	laser_currentPower = 0;
}

uint8_t laser_start() {
	// Coolant must be on
	coolant_run(COOLANT_FLOOD_ENABLE);
	BLINK_PORT |= (1 << BLINK_BIT);
	uint8_t idx;
	for (idx = 0; idx < 3; idx++) {		
		RELAIS_PORT |= (1 << _startSequence[idx]);
		wait(1);
	}
	laserON = 1;
	return 1;
}

uint8_t laser_stop() {
	// coolant must be on
	coolant_run(COOLANT_FLOOD_ENABLE);
	BLINK_PORT &= ~(1 << BLINK_BIT);
	LaserPWM = 0;
	uint8_t idx;
	for (idx = 0; idx < 3; idx++) {
		RELAIS_PORT = ~(1 << _stopSequence[idx]);
		wait(1);
	}
	laserON = 0;
	return 1;
}

uint8_t laser_shutdown() {
	coolant_run(COOLANT_FLOOD_ENABLE);
	BLINK_PORT &= ~(1 << BLINK_BIT);
	LaserPWM = 0;
	uint8_t idx;
	for (idx = 0; idx < 2; idx++) {
		RELAIS_PORT &= ~(1 << _stopSequence[idx]);
	}
	laserON = 0;
	return 1;
}


uint8_t laser_getPower() {
	return OCR_REGISTER;
}

float laser_getTemp() {
	uint8_t temp = thermistor_read(0);
	// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000  // 10K     
	// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   
	// how many samples to take and average, more takes longer
	// but is more 'smooth'
#define NUMSAMPLES 10
	// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
	// the value of the 'other' resistor
#define SERIESRESISTOR 9870   

	static uint8_t i;
	static float average = 0.0;
	static float steinhart = 0.0;

	// take N samples in a row, with a slight delay
	average = 0;
	for (i = 0; i< NUMSAMPLES; i++) {
		average += thermistor_read(0);
		//delay(10);
	}
	average /= NUMSAMPLES;
	average = 1023 / average - 1;
	average = SERIESRESISTOR / average;
	steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
	steinhart = log(steinhart);                  // ln(R/Ro)
	steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
	steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
	steinhart = 1.0 / steinhart;                 // Invert
	steinhart -= 273.15;                         // convert to C
	return steinhart;
}

void wait(unsigned long sec) {
	if (sec > 4) sec = 4;
	TCNT5 = 0;
	OCR5A = 15625 * sec;
	waiting = 1;
	TIMSK5 = bit(OCIE5A);
	while (waiting == 1) {}
	TIMSK5 = 0;
}

ISR(TIMER5_COMPA_vect)
{
	waiting = 0;
}