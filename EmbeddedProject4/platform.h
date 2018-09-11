/*
 * platform.h
 *
 *  Created on: Feb 11, 2015
 *      Author: tB
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

/*************************************************************************************************/

#include <config.h>
//#include "logicGlobals.h"
#include <cycleBuffer.h>
#include <typedefs.h>

/*** CONFIG **************************************************************************************/

#ifdef STM32F103C8_BOARD

// Nazwa platformy
#define PLATFORM_NAME "STM32F103C8 Board"


// ENUM (not used) | CLASS | NAME
#define PhysicalDevicesList(device) \
	device(physicalDevice_BUTTON1,		physicalDeviceFamily_BUTTON,	"Button 1") \
	device(physicalDevice_BUTTON2,		physicalDeviceFamily_BUTTON,	"Button 2") \
	device(physicalDevice_BUTTON3,		physicalDeviceFamily_BUTTON,	"Button 3") \
	device(physicalDevice_BUTTON4,		physicalDeviceFamily_BUTTON,	"Button 4") \
	device(physicalDevice_LED1,			physicalDeviceFamily_LED,		"LED 1") \
	device(physicalDevice_LED2,			physicalDeviceFamily_LED,		"LED 2") \
	device(physicalDevice_LED3,			physicalDeviceFamily_LED,		"LED 3") \
	device(physicalDevice_LED4,			physicalDeviceFamily_LED,		"LED 4") \
	device(physicalDevice_PWM1,			physicalDeviceFamily_PWM,		"PWM 1") \
	device(physicalDevice_PWM2,			physicalDeviceFamily_PWM,		"PWM 2") \
	device(physicalDevice_PWM3,			physicalDeviceFamily_PWM,		"PWM 3") \
	device(physicalDevice_PWM4,			physicalDeviceFamily_PWM,		"PWM 4") \
	device(physicalDevice_DISPLAY1,		physicalDeviceFamily_DISPLAY,	"Display 1") \
	device(physicalDevice_ADC1,			physicalDeviceFamily_ADC,		"ADC 1") \
	device(physicalDevice_ADC2,			physicalDeviceFamily_ADC,		"ADC 2") \
	device(physicalDevice_THERMO1,		physicalDeviceFamily_THERMO,	"*C") \
	device(physicalDevice_RTC,			physicalDeviceFamily_RTC,		"RTC") /* There is only one RTC in the system, thats why there is no index */ \
	device(physicalDevice_PARSER,		physicalDeviceFamily_PARSER,	"Parser") /* There is only one PARSER per system */ \
	device(physicalDevice_SYSTEM,		physicalDeviceFamily_SYSTEM,	"System") \

// PARENT (not used) | PAD TYPE | FUNCTION
#define PadsList(pad) \
	pad(physicalDevice_BUTTON1,		padType_OUT,	Button1_Get) \
	pad(physicalDevice_BUTTON2,		padType_OUT,	Button2_Get) \
	pad(physicalDevice_BUTTON3,		padType_OUT,	Button3_Get) \
	pad(physicalDevice_BUTTON4,		padType_OUT,	Button4_Get) \
	pad(physicalDevice_LED1,		padType_IN,		Led1_Set) \
	pad(physicalDevice_LED2,		padType_IN,		Led2_Set) \
	pad(physicalDevice_LED3,		padType_IN,		Led3_Set) \
	pad(physicalDevice_LED4,		padType_IN,		Led4_Set) \
	pad(physicalDevice_PWM1,		padType_IN,		Pwm1_Set) \
	pad(physicalDevice_PWM2,		padType_IN,		Pwm2_Set) \
	pad(physicalDevice_PWM3,		padType_IN,		Pwm3_Set) \
	pad(physicalDevice_PWM4,		padType_IN,		Pwm4_Set) \
	pad(physicalDevice_DISPLAY1,	padType_IN,		Display1_Set) \
	pad(physicalDevice_DISPLAY1,	padType_IN,		Display1Dot_Set) \
	pad(physicalDevice_ADC1,		padType_OUT,	Adc1_Value) \
	pad(physicalDevice_ADC2,		padType_OUT,	Adc2_Value) \
	pad(physicalDevice_THERMO1,		padType_OUT,	TemperatureSensor_GetTemperature) \
	pad(physicalDevice_RTC,			padType_IN,		Clock_AddSeconds) \
	pad(physicalDevice_RTC,			padType_IN,		Clock_SubtractSeconds) \
	pad(physicalDevice_RTC,			padType_OUT,	Clock_GetHours) \
	pad(physicalDevice_RTC,			padType_OUT,	Clock_GetMinutes) \
	pad(physicalDevice_RTC,			padType_OUT,	Clock_GetSeconds) \
	pad(physicalDevice_RTC,			padType_OUT,	Clock_GetDayOfWeek) \
	pad(physicalDevice_RTC,			padType_OUT,	Clock_GetDay) \
	pad(physicalDevice_RTC,			padType_OUT,	Clock_GetMonth) \
	pad(physicalDevice_RTC,			padType_OUT,	Clock_GetYear) \
	pad(physicalDevice_PARSER,		padType_OUT,	Parser_GetEvent) \
	pad(physicalDevice_PARSER,		padType_OUT,	Parser_GetParamCode) \
	pad(physicalDevice_PARSER,		padType_OUT,	Parser_GetParamValue) \
	pad(physicalDevice_SYSTEM,		padType_IN,		System_StoreMaps) \

#endif

#ifdef STM32F100RC_BOARD

// Nazwa platformy
#define PLATFORM_NAME "STM32F100RC Board"

// ENUM (not used) | CLASS | NAME
#define PhysicalDevicesList(device) \
	device(physicalDevice_BUTTON1,		physicalDeviceFamily_BUTTON,	"Button 1") \
	device(physicalDevice_BUTTON2,		physicalDeviceFamily_BUTTON,	"Button 2") \
	device(physicalDevice_BUTTON3,		physicalDeviceFamily_BUTTON,	"Button 3") \
	device(physicalDevice_BUTTON4,		physicalDeviceFamily_BUTTON,	"Button 4") \
	device(physicalDevice_LED1,			physicalDeviceFamily_LED,		"LED 1") \
	device(physicalDevice_LED2,			physicalDeviceFamily_LED,		"LED 2") \
	device(physicalDevice_LED3,			physicalDeviceFamily_LED,		"LED 3") \
	device(physicalDevice_LED4,			physicalDeviceFamily_LED,		"LED 4") \
	device(physicalDevice_PWM1,			physicalDeviceFamily_PWM,		"PWM 1") \
	device(physicalDevice_PWM2,			physicalDeviceFamily_PWM,		"PWM 2") \
	device(physicalDevice_PWM3,			physicalDeviceFamily_PWM,		"PWM 3") \
	device(physicalDevice_PWM4,			physicalDeviceFamily_PWM,		"PWM 4") \
	device(physicalDevice_DISPLAY1,		physicalDeviceFamily_DISPLAY,	"Display 1") \
	device(physicalDevice_DISPLAY2,		physicalDeviceFamily_DISPLAY,	"Display 2") \
	device(physicalDevice_DISPLAY3,		physicalDeviceFamily_DISPLAY,	"Display 3") \
	device(physicalDevice_DISPLAY4,		physicalDeviceFamily_DISPLAY,	"Display 4") \
	device(physicalDevice_ADC1,			physicalDeviceFamily_ADC,		"ADC 1") \
	device(physicalDevice_ADC2,			physicalDeviceFamily_ADC,		"ADC 2") \
	device(physicalDevice_THERMO1,		physicalDeviceFamily_THERMO,	"*C") \
	device(physicalDevice_RTC,			physicalDeviceFamily_RTC,		"RTC") /* There is only one RTC in the system, thats why there is no index */ \
	device(physicalDevice_PARSER,		physicalDeviceFamily_PARSER,	"Parser") /* There is only one PARSER per system */ \
	device(physicalDevice_BUZZER,		physicalDeviceFamily_BUZZER,	"Buzzer") \
	device(physicalDevice_SYSTEM,		physicalDeviceFamily_SYSTEM,	"System") \

// PARENT (not used) | PAD TYPE | FUNCTION
#define PadsList(pad) \
	pad(physicalDevice_BUTTON1,		padType_OUT,	Button1_Get) \
	pad(physicalDevice_BUTTON2,		padType_OUT,	Button2_Get) \
	pad(physicalDevice_BUTTON3,		padType_OUT,	Button3_Get) \
	pad(physicalDevice_BUTTON4,		padType_OUT,	Button4_Get) \
	pad(physicalDevice_LED1,		padType_IN,		Led1_Set) \
	pad(physicalDevice_LED2,		padType_IN,		Led2_Set) \
	pad(physicalDevice_LED3,		padType_IN,		Led3_Set) \
	pad(physicalDevice_LED4,		padType_IN,		Led4_Set) \
	pad(physicalDevice_PWM1,		padType_IN,		Pwm1_Set) \
	pad(physicalDevice_PWM2,		padType_IN,		Pwm2_Set) \
	pad(physicalDevice_PWM3,		padType_IN,		Pwm3_Set) \
	pad(physicalDevice_PWM4,		padType_IN,		Pwm4_Set) \
	pad(physicalDevice_DISPLAY1,	padType_IN,		Display1_Set) \
	pad(physicalDevice_DISPLAY1,	padType_IN,		Display1Dot_Set) \
	pad(physicalDevice_DISPLAY2,	padType_IN,		Display2_Set) \
	pad(physicalDevice_DISPLAY2,	padType_IN,		Display2Dot_Set) \
	pad(physicalDevice_DISPLAY3,	padType_IN,		Display3_Set) \
	pad(physicalDevice_DIPSLAY3,	padType_IN,		Display3Dot_Set) \
	pad(physicalDevice_DISPLAY4,	padType_IN,		Display4_Set) \
	pad(physicalDevice_DISPLAY4,	padType_IN,		Display4Dot_Set) \
	pad(physicalDevice_ADC1,		padType_OUT,	Adc1_Value) \
	pad(physicalDevice_ADC2,		padType_OUT,	Adc2_Value) \
	pad(physicalDevice_THERMO1,		padType_OUT,	TemperatureSensor_GetTemperature) \
	pad(physicalDevice_RTC,			padType_IN,		Clock_AddSeconds) \
	pad(physicalDevice_RTC,			padType_IN,		Clock_SubtractSeconds) \
	pad(physicalDevice_RTC,			padType_OUT,	Clock_GetHours) \
	pad(physicalDevice_RTC,			padType_OUT,	Clock_GetMinutes) \
	pad(physicalDevice_RTC,			padType_OUT,	Clock_GetSeconds) \
	pad(physicalDevice_RTC,			padType_OUT,	Clock_GetDayOfWeek) \
	pad(physicalDevice_RTC,			padType_OUT,	Clock_GetDay) \
	pad(physicalDevice_RTC,			padType_OUT,	Clock_GetMonth) \
	pad(physicalDevice_RTC,			padType_OUT,	Clock_GetYear) \
	pad(physicalDevice_PARSER,		padType_OUT,	Parser_GetEvent) \
	pad(physicalDevice_PARSER,		padType_OUT,	Parser_GetParamCode) \
	pad(physicalDevice_PARSER,		padType_OUT,	Parser_GetParamValue) \
	pad(physicalDevice_BUZZER,		padType_IN,		Buzzer1_Enable) \
	pad(physicalDevice_BUZZER,		padType_IN,		Buzzer1_SetFrequency) \
	pad(physicalDevice_BUZZER,		padType_IN,		Buzzer1_SetVolume) \
	pad(physicalDevice_SYSTEM,		padType_IN,		System_StoreMaps) \

#endif

/*************************************************************************************************/

typedef enum
{
	physicalDeviceFamily_NONE,
	physicalDeviceFamily_BUTTON, // 1x output pad
	physicalDeviceFamily_LED, // 1x input pad
	physicalDeviceFamily_ADC, // 1x output pad
	physicalDeviceFamily_PWM, // 1x input pad
	physicalDeviceFamily_RTC, // 2x input pad, 7x output pad
	physicalDeviceFamily_DISPLAY, // 1x input pad
	physicalDeviceFamily_THERMO, // 1x input pad
	physicalDeviceFamily_PARSER, // 3x output pad 							// added 13-05-2015
	physicalDeviceFamily_BUZZER, // 3x input pad 							// added 30-11-2015
	physicalDeviceFamily_SYSTEM, // 1x input pad 							// added 4-1-2016
}
physicalDeviceFamily_t;


typedef struct
{
	physicalDeviceFamily_t family; // Device class (index of class from physicalDeviceFamily_t)
	char * name; // Device name (visible in compiler sheet)
}
physicalDevice_t;

#define PhysicalDevice(e,class,name) {class,name},
extern const physicalDevice_t physicalDevices[];;
extern const u8 physicalDevicesCount;

/*************************************************************************************************/

typedef enum { padType_OUT, padType_IN } padType_t;


typedef struct
{
	padType_t type; // == function type (getting or returning value)
	addr_t Function;
}
padFunction_t;

#define PadFunction(e,type,fun) {type,(u32)fun},
extern const padFunction_t physicalDevicesPads[];
extern const u8 physicalDevicesPadsCount;

/*************************************************************************************************/

void Platform_Init(void);
void Platform_Intro(cycleBuffer_t * buffer);

/*************************************************************************************************/

#endif /* PLATFORM_H_ */
