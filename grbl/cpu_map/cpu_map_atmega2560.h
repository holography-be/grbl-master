/*
  cpu_map_atmega2560.h - CPU and pin mapping configuration file
  Part of Grbl

  Copyright (c) 2012-2015 Sungeun K. Jeon

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

/* This cpu_map file serves as a central pin mapping settings file for AVR Mega 2560 */


#ifdef GRBL_PLATFORM
#error "cpu_map already defined: GRBL_PLATFORM=" GRBL_PLATFORM
#endif


#define GRBL_PLATFORM "Atmega2560"

// Serial port pins
#define SERIAL_RX USART0_RX_vect
#define SERIAL_UDRE USART0_UDRE_vect

// I2C pins
#define I2C_PORT	PORTD
#define I2C_DDR		DDRD
#define I2C_PIN		PIND
#define SDA_PIN	1
#define SCL_PIN	0

// Increase Buffers to make use of extra SRAM
//#define RX_BUFFER_SIZE		256
//#define TX_BUFFER_SIZE		128
//#define BLOCK_BUFFER_SIZE	36
//#define LINE_BUFFER_SIZE	100

// Define step pulse output pins. NOTE: All step bit pins must be on the same port.
#define STEP_DDR      DDRA
#define STEP_PORT     PORTA
#define STEP_PIN      PINA
#define X_STEP_BIT    0 // MEGA2560 Digital Pin 22
#define Y_STEP_BIT    1 // MEGA2560 Digital Pin 23
#define Z_STEP_BIT    2 // MEGA2560 Digital Pin 24
#define A_STEP_BIT    3 // MEGA2560 Digital Pin 25
#define STEP_MASK ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)|(1<<A_STEP_BIT)) // All step bits

// Define step direction output pins. NOTE: All direction pins must be on the same port.
#define DIRECTION_DDR     DDRC
#define DIRECTION_PORT    PORTC
#define DIRECTION_PIN     PINC
#define X_DIRECTION_BIT   7 // MEGA2560 Digital Pin 30
#define Y_DIRECTION_BIT   6 // MEGA2560 Digital Pin 31
#define Z_DIRECTION_BIT   5 // MEGA2560 Digital Pin 32
#define A_DIRECTION_BIT   4 // MEGA2560 Digital Pin 33
#define DIRECTION_MASK ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)|(1<<A_DIRECTION_BIT)) // All direction bits


#define BLINK_DDR   DDRB
#define BLINK_PORT  PORTB
#define BLINK_PIN	PINB
#define BLINK_BIT   7 // MEGA2560 Digital Pin 13

// Define stepper driver enable/disable output pin.
#define STEPPERS_DISABLE_DDR   DDRH
#define STEPPERS_DISABLE_PORT  PORTH
#define STEPPERS_DISABLE_BIT   6 // MEGA2560 Digital Pin 9
#define STEPPERS_DISABLE_MASK (1<<STEPPERS_DISABLE_BIT)

// Define homing/hard limit switch input pins and limit interrupt vectors. 
// NOTE: All limit bit pins must be on the same port
#define LIMIT_DDR       DDRB
#define LIMIT_PORT      PORTB
#define LIMIT_PIN       PINB
#define X_LIMIT_BIT     4 // MEGA2560 Digital Pin 10
#define Y_LIMIT_BIT     5 // MEGA2560 Digital Pin 11
#define Z_LIMIT_BIT     6 // MEGA2560 Digital Pin 12
#define LIMIT_INT       PCIE0  // Pin change interrupt enable pin
#define LIMIT_INT_vect  PCINT0_vect 
#define LIMIT_PCMSK     PCMSK0 // Pin change interrupt register
#define LIMIT_MASK ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits

// Define spindle enable and spindle direction output pins.
#define SPINDLE_ENABLE_DDR      DDRH
#define SPINDLE_ENABLE_PORT     PORTH
#define SPINDLE_ENABLE_BIT      3 // MEGA2560 Digital Pin 6
//#define	INVERT_SPINDLE_ENABLE_PIN 1 // inverse sortie commande laser (0 = relais on, 1 = relais off)
#define SPINDLE_DIRECTION_DDR   DDRE
#define SPINDLE_DIRECTION_PORT  PORTE
#define SPINDLE_DIRECTION_BIT   3 // MEGA2560 Digital Pin 5

// Define flood and mist coolant enable output pins.
// NOTE: Uno analog pins 4 and 5 are reserved for an i2c interface, and may be installed at
// a later date if flash and memory space allows.
#define COOLANT_FLOOD_DDR     DDRH
#define COOLANT_FLOOD_PORT    PORTH
#define COOLANT_FLOOD_BIT     5 // MEGA2560 Digital Pin 8

#ifdef ENABLE_M7 // Mist coolant disabled by default. See config.h to enable/disable.
#define COOLANT_MIST_DDR    DDRH
#define COOLANT_MIST_PORT   PORTH
#define COOLANT_MIST_BIT    6 // MEGA2560 Digital Pin 9
#endif  

// Define user-control CONTROLs (cycle start, reset, feed hold) input pins.
// NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
#define CONTROL_DDR       DDRK
#define CONTROL_PIN       PINK
#define CONTROL_PORT      PORTK
#define RESET_BIT         0  // MEGA2560 Analog Pin 8
#define FEED_HOLD_BIT     1  // MEGA2560 Analog Pin 9
#define CYCLE_START_BIT   2  // MEGA2560 Analog Pin 10
#define SAFETY_DOOR_BIT   3  // MEGA2560 Analog Pin 11
#define CONTROL_INT       PCIE2  // Pin change interrupt enable pin
#define CONTROL_INT_vect  PCINT2_vect
#define CONTROL_PCMSK     PCMSK2 // Pin change interrupt register
#define CONTROL_MASK ((1<<RESET_BIT)|(1<<FEED_HOLD_BIT)|(1<<CYCLE_START_BIT)|(1<<SAFETY_DOOR_BIT))
#define CONTROL_INVERT_MASK CONTROL_MASK // May be re-defined to only invert certain control pins.

// Define probe switch input pin.
#define PROBE_DDR       DDRK
#define PROBE_PIN       PINK
#define PROBE_PORT      PORTK
#define PROBE_BIT       7  // MEGA2560 Analog Pin 15
#define PROBE_MASK      (1<<PROBE_BIT)

// Start of PWM & Stepper Enabled Spindle
#ifdef VARIABLE_SPINDLE
  // Advanced Configuration Below You should not need to touch these variables
  // Set Timer up to use TIMER4B which is attached to Digital Pin 7
  #define PWM_MAX_VALUE      255
  #define TCCRA_REGISTER		TCCR4A
  #define TCCRB_REGISTER		TCCR4B
  #define OCR_REGISTER		OCR4B	// digital port 7
  
  #define COMB_BIT			COM4B1
  #define WAVE0_REGISTER		WGM40
  #define WAVE1_REGISTER		WGM41
  #define WAVE2_REGISTER		WGM42
  #define WAVE3_REGISTER		WGM43
  
  #define SPINDLE_PWM_DDR		DDRH
  #define SPINDLE_PWM_PORT    PORTH
  #define SPINDLE_PWM_BIT		4 // MEGA2560 Digital Pin 7
#endif // End of VARIABLE_SPINDLE

#define Laser_Temp_PIN		ADC0D   // ANALOG 0

// Leds Control
#define LED_DDR			DDRL // D42 -> D49
#define LED_PIN			PINL
#define LED_PORT			PORTL
#define LED1			0	// D49
#define LED2			1	// D48
#define LED3			2	// D47
#define LED4			3	// D46
#define LED5			4	// D45
#define LED6			5	// D44
#define LED7			6   // D43
#define LED8			7	// D42
#define LED_MASK			(B11111111) // Bit set = OUTPUT

#define LED_ALARM				LED1_BIT
#define LED_CONNECTION_ALARM	LED2_BIT
#define LED_LASER				LED3_BIT

//#define FAN1_BIT			RELAIS5_BIT
//#define FAN2_BIT			RELAIS6_BIT
//#define FAN3_BIT			RELAIS7_BIT
//
//#define Laser_Driver_PIN	RELAIS1_BIT
//#define Laser_Peltier_PIN	RELAIS2_BIT
//#define Laser_Diode_PIN		RELAIS3_BIT

//#define LaserPower_PIN		9  // PWM
//#define LaserPWM			OCR2B
//#define LaserMaxTemp		25.0

//#define LASERLEVEL_DDR	DDRL
//#define LASERLEVEL_PIN	PINL
//#define LASERLEVEL_PORT	PORTL
//#define LASERLEVEL_REQUEST	50	// Send signal to Nano that we wish send datas
//#define LASERLEVEL_STATUS	51	// Signal send by Nano (HIGH = Ready, LOW = Busy)
//#define Laser_Start_Sequence	 Laser_Peltier_PIN,Laser_Driver_PIN,Laser_Diode_PIN
//#define Laser_Stop_Sequence		 Laser_Diode_PIN,Laser_Driver_PIN,Laser_Peltier_PIN
//#define Laser_Emergency_Sequence Laser_Diode_PIN,Laser_Driver_PIN // On laisse le Peltier 
//#define Laser_Delai_Sequence	 1500