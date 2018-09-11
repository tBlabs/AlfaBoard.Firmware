/*
 * led.c
 *
 *  Created on: Jan 6, 2015
 *      Author: tB
 */

/*************************************************************************************************/

#include "leds.h"

#include <config.h>
#include <platform.h> // Zawiera definicje I/O zale¿n¹ od typu platformy
#include "typedefs.h"
#include "pins.h"

/*************************************************************************************************/

// ENUM | PIN
#define LedsList(led) \
	led(led_0, PinA8) \
	led(led_1, PinA9) \
	led(led_2, PinA10) \
	led(led_3, PinA11) \

/*************************************************************************************************/

#define LED_DEBUG_ENABLE	1


#if (LED_DEBUG_ENABLE==0)
	#define LedDebug(str,...)
#else
	#include "debug.h"
	#include "delay.h"
	#define LedDebug(str,...) Debug(str,##__VA_ARGS__)
#endif

/*************************************************************************************************/

typedef struct
{
	pin_t pin;
}
led_t;

#define LedEnum(e,pin) e,
enum { LedsList(LedEnum) };

#define Led(e,pin) {pin},
led_t leds[] = { LedsList(Led) };

const u8 ledsCount = sizeof(leds)/sizeof(led_t);

/*************************************************************************************************/

void Leds_Init(void)
{
	for (u8 i=0; i<ledsCount; i++)
	{
		Pin_Init(&leds[i].pin, GPIO_Mode_Out_PP);
	}
}

/*************************************************************************************************/

void Led1_Set(u16 ledState)
{
	Pin_Set(&leds[led_0].pin, (ledState != 0) ? pinState_HIGH : pinState_LOW);
}

/*************************************************************************************************/

void Led2_Set(u16 ledState)
{
	Pin_Set(&leds[led_1].pin, (ledState != 0) ? pinState_HIGH : pinState_LOW);
}

/*************************************************************************************************/

void Led3_Set(u16 ledState)
{
	Pin_Set(&leds[led_2].pin, (ledState != 0) ? pinState_HIGH : pinState_LOW);
}

/*************************************************************************************************/

void Led4_Set(u16 ledState)
{
	Pin_Set(&leds[led_3].pin, (ledState != 0) ? pinState_HIGH : pinState_LOW);
}

/*************************************************************************************************/

#if (LED_DEBUG_ENABLE==1)

void Leds_Test(void)
{
	Leds_Init();

	u8 a=0;
	while (1)
	{
		Led1_Set(a);
		DelayMs(100);
		Led2_Set(a);
		DelayMs(100);
		Led3_Set(a);
		DelayMs(100);
		Led4_Set(a);
		DelayMs(100);

		a = 1 - a;
	}
}

#endif

/*************************************************************************************************/
