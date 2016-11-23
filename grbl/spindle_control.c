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


void spindle_init()
{    
  // Configure variable spindle PWM and enable pin, if requried. On the Uno, PWM and enable are
  // combined unless configured otherwise.
  #ifdef VARIABLE_SPINDLE
	// etre certain de mettre la puissance à 0
	OCR_REGISTER = 0;
    SPINDLE_PWM_DDR |= (1<<SPINDLE_PWM_BIT); // Configure as PWM output pin.
  #endif
  //
	TCCRA_REGISTER = (1 << COMB_BIT) | (1 << WAVE1_REGISTER) | (1 << WAVE0_REGISTER);  // compare channel B
	//TCCRB_REGISTER = (TCCRB_REGISTER & B11111000) | 0x02 | (1<<WAVE2_REGISTER) | (1<<WAVE3_REGISTER); // set to 1/8 Prescaler
	TCCRB_REGISTER = (TCCRB_REGISTER & B11111000) | 0x01 | (1 << WAVE2_REGISTER) | (1 << WAVE3_REGISTER);  // set to 1/1 Prescaler (31372.55 Hz)
	OCR4A = 255 * 7; // set the top 16bit value -> pour frequence de 8957 Hz
    spindle_stop();
}


void spindle_stop()
{
  // On the Uno, spindle enable and PWM are shared. Other CPUs have seperate enable pin.
  #ifdef VARIABLE_SPINDLE
	OCR_REGISTER = 0;
    TCCRA_REGISTER &= ~(1<<COMB_BIT); // Disable PWM. Output voltage is zero.
  #endif  
}


void spindle_set_state(uint8_t state, float laserPower)
{
  // Halt or set spindle direction and rpm. 
  if (state == SPINDLE_DISABLE) {

    spindle_stop();

  } else {	
	  if (coolantON == 0) {
		  // laser shutdown 
		  laser_shutdown();
		  bit_true_atomic(sys_rt_exec_alarm, (EXEC_ALARM_COOLANT_OFF | EXEC_CRITICAL_EVENT));
		  return;
	  }
	TCCRA_REGISTER |= (1 << COMB_BIT); // Enable PWM. Output voltage is zero.
    #ifdef VARIABLE_SPINDLE
	if ((int)laserPower == 0) {
		OCR_REGISTER = 0;
		TCCRA_REGISTER &= ~(1 << COMB_BIT); // Disable PWM. Output voltage is zero.
	}
	else {
		OCR_REGISTER = (int)((laserPower * 7.00) / (float)laserPowerSettings);
	}

    #endif

  }
}


void spindle_run(uint8_t state, float laserPower)
{
  if (sys.state == STATE_CHECK_MODE) { return; }
  protocol_buffer_synchronize(); // Empty planner buffer to ensure spindle is set when programmed.  
  spindle_set_state(state, laserPower);
}

void spindel_reinit() {
	//// Laser Power reinit (OCR4A register)
	//if (sys.state == STATE_CHECK_MODE) { return; }
	//protocol_buffer_synchronize(); // Empty planner buffer to ensure spindle is set when programmed.  
	////spindle_stop();
	//OCR4A = 255 * laserPowerSettings; // set the top 16bit value
}