/*
  spindle_control.c - spindle control methods
  Part of Grbl

  Copyright (c) 2012-2015 Sungeun K. Jeon
  Copyright (c) 2009-2011 Simen Svale Skogsrud

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "grbl.h"

uint8_t _spindle_state = SPINDLE_DISABLE;

void spindle_init()
{    
	// Configure variable spindle PWM and enable pin, if requried. On the Uno, PWM and enable are
	// combined unless configured otherwise.
	BLINK_DDR |= (1 << BLINK_BIT);
	BLINK_PORT &= ~(1 << BLINK_BIT);

#ifdef VARIABLE_SPINDLE
	SPINDLE_PWM_DDR |= (1 << SPINDLE_PWM_BIT); // Configure as PWM output pin.
#if defined(CPU_MAP_ATMEGA2560) || defined(USE_SPINDLE_DIR_AS_ENABLE_PIN)
	SPINDLE_ENABLE_DDR |= (1 << SPINDLE_ENABLE_BIT); // Configure as output pin.
#endif     
	// Configure no variable spindle and only enable pin.
#else  
	SPINDLE_ENABLE_DDR |= (1 << SPINDLE_ENABLE_BIT); // Configure as output pin.
#endif

#ifndef USE_SPINDLE_DIR_AS_ENABLE_PIN
	SPINDLE_DIRECTION_DDR |= (1 << SPINDLE_DIRECTION_BIT); // Configure as output pin.
#endif
	spindle_stop();

}


void spindle_stop()
{
	// On the Uno, spindle enable and PWM are shared. Other CPUs have seperate enable pin.
	_spindle_state = SPINDLE_DISABLE;
#ifdef VARIABLE_SPINDLE
	TCCRA_REGISTER &= ~(1 << COMB_BIT); // Disable PWM. Output voltage is zero.
	OCR_REGISTER = 0;
#if defined(CPU_MAP_ATMEGA2560)
#ifdef INVERT_SPINDLE_ENABLE_PIN
	SPINDLE_ENABLE_PORT |= (1 << SPINDLE_ENABLE_BIT);  // Set pin to high
#else
	SPINDLE_ENABLE_PORT &= ~(1 << SPINDLE_ENABLE_BIT); // Set pin to low
#endif
	laserState = LASER_STATE_OFF;
	BLINK_PORT &= ~(1 << BLINK_BIT);
#endif
#endif  
}

uint8_t spindle_get_state() {
	return _spindle_state;
}

void spindle_set_state(uint8_t state, float laserPower)
{

	// Halt or set spindle direction and rpm. 
	if (state == SPINDLE_DISABLE) {

		spindle_stop();

	}
	else {


#ifdef VARIABLE_SPINDLE
		// TODO: Install the optional capability for frequency-based output for servos.
#ifdef CPU_MAP_ATMEGA2560
		if (laserState == LASER_STATE_OFF) {	// si le laser est coup�, on r�init le timer PWM
			//TCCRA_REGISTER &= ~(1 << COMB_BIT); // Disable PWM. Output voltage is zero.
			laserState = LASER_STATE_ON;
			BLINK_PORT |= (1 << BLINK_BIT);
			OCR_REGISTER = 0;
			TCCRA_REGISTER = (1 << WAVE1_REGISTER) | (1 << WAVE0_REGISTER);  // compare channel B
//			TCCRA_REGISTER = (1 << COMB_BIT) | (1 << WAVE1_REGISTER) | (1 << WAVE0_REGISTER);  // compare channel B
			TCCRB_REGISTER = (TCCRB_REGISTER & B11111000) | 0x01 | (1 << WAVE2_REGISTER) | (1 << WAVE3_REGISTER);  // set to 1/1 Prescaler (31372.55 Hz)
			OCR4A = 255 * Timer4Counter; // set the top 16bit value -> pour frequence de 8957 Hz
#ifdef INVERT_SPINDLE_ENABLE_PIN
		SPINDLE_ENABLE_PORT &= ~(1 << SPINDLE_ENABLE_BIT);
#else
		SPINDLE_ENABLE_PORT |= (1 << SPINDLE_ENABLE_BIT);
		_spindle_state = SPINDLE_ENABLE_CW;
#endif
		}
#else
		TCCRA_REGISTER = (1 << COMB_BIT) | (1 << WAVE1_REGISTER) | (1 << WAVE0_REGISTER);
		TCCRB_REGISTER = (TCCRB_REGISTER & 0b11111000) | 0x02; // set to 1/8 Prescaler
#endif
		uint8_t pwm = (int)laserPower;
		if (laserPower > 0) {
			TCCRA_REGISTER |= (1 << COMB_BIT);  // enable PWM
			OCR_REGISTER = ((int)laserPower * Timer4Counter) / laserPowerSettings; // Set PWM pin output
		}
		else {
			TCCRA_REGISTER &= ~(1 << COMB_BIT);	// Disable PWM
		}

#else   
#ifdef INVERT_SPINDLE_ENABLE_PIN
		SPINDLE_ENABLE_PORT &= ~(1 << SPINDLE_ENABLE_BIT);
#else
		SPINDLE_ENABLE_PORT |= (1 << SPINDLE_ENABLE_BIT);
#endif
#endif

	}

}


void spindle_run(uint8_t state, float laserPower)
{
  if (sys.state == STATE_CHECK_MODE) { return; }
  protocol_buffer_synchronize(); // Empty planner buffer to ensure spindle is set when programmed.  
  spindle_set_state(state, laserPower);
}

