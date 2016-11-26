/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Mega w/ ATmega2560 (Mega 2560), Platform=avr, Package=arduino
*/

#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
#define __AVR_ATmega2560__
#define F_CPU 16000000L
#define ARDUINO 10605
#define ARDUINO_AVR_MEGA2560
#define ARDUINO_ARCH_AVR
#define __cplusplus 201103L
#define __AVR__
#define __inline__
#define __asm__(x)
#define __extension__
//#define __ATTR_PURE__
//#define __ATTR_CONST__
#define __inline__
//#define __asm__ 
#define __volatile__
#define GCC_VERSION 40801
#define volatile(va_arg) 
#define _CONST
typedef void *__builtin_va_list;
#define __builtin_va_start
#define __builtin_va_end
//#define __DOXYGEN__
#define __attribute__(x)
#define NOINLINE __attribute__((noinline))
#define prog_void
#define PGM_VOID_P int
#ifndef __builtin_constant_p
#define __builtin_constant_p __attribute__((__const__))
#endif
#ifndef __builtin_strlen
#define __builtin_strlen  __attribute__((__const__))
#endif
#define NEW_H
/*
#ifndef __ATTR_CONST__
#define __ATTR_CONST__ __attribute__((__const__))
#endif

#ifndef __ATTR_MALLOC__
#define __ATTR_MALLOC__ __attribute__((__malloc__))
#endif

#ifndef __ATTR_NORETURN__
#define __ATTR_NORETURN__ __attribute__((__noreturn__))
#endif

#ifndef __ATTR_PURE__
#define __ATTR_PURE__ __attribute__((__pure__))
#endif            
*/
typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}



#include <arduino.h>
#include <pins_arduino.h> 
#undef F
#define F(string_literal) ((const PROGMEM char *)(string_literal))
#undef PSTR
#define PSTR(string_literal) ((const PROGMEM char *)(string_literal))
#undef cli
#define cli()
#define pgm_read_byte(address_short)
#define pgm_read_word(address_short)
#define pgm_read_word2(address_short)
#define digitalPinToPort(P)
#define digitalPinToBitMask(P) 
#define digitalPinToTimer(P)
#define analogInPinToBit(P)
#define portOutputRegister(P)
#define portInputRegister(P)
#define portModeRegister(P)
#include <..\grbl\grbl.ino>
#include <..\grbl\clock.c>
#include <..\grbl\clock.h>
#include <..\grbl\config.h>
#include <..\grbl\coolant_control.c>
#include <..\grbl\coolant_control.h>
#include <..\grbl\cpu_map.h>
#include <cpu_map\cpu_map_atmega2560.h>
#include <..\grbl\defaults.h>
#include <..\grbl\eeprom.c>
#include <..\grbl\eeprom.h>
#include <..\grbl\gcode.c>
#include <..\grbl\gcode.h>
#include <..\grbl\grbl.h>
#include <..\grbl\laser.c>
#include <..\grbl\laser.h>
#include <..\grbl\leds.c>
#include <..\grbl\leds.h>
#include <..\grbl\limits.c>
#include <..\grbl\limits.h>
#include <..\grbl\main.c>
#include <..\grbl\motion_control.c>
#include <..\grbl\motion_control.h>
#include <..\grbl\nuts_bolts.c>
#include <..\grbl\nuts_bolts.h>
#include <..\grbl\planner.c>
#include <..\grbl\planner.h>
#include <..\grbl\print.c>
#include <..\grbl\print.h>
#include <..\grbl\probe.c>
#include <..\grbl\probe.h>
#include <..\grbl\protocol.c>
#include <..\grbl\protocol.h>
#include <..\grbl\relais.c>
#include <..\grbl\relais.h>
#include <..\grbl\report.c>
#include <..\grbl\report.h>
#include <..\grbl\serial.c>
#include <..\grbl\serial.h>
#include <..\grbl\settings.c>
#include <..\grbl\settings.h>
#include <..\grbl\spindle_control.c>
#include <..\grbl\spindle_control.h>
#include <..\grbl\stepper.c>
#include <..\grbl\stepper.h>
#include <..\grbl\system.c>
#include <..\grbl\system.h>
#include <..\grbl\thermistor.c>
#include <..\grbl\thermistor.h>
#endif
