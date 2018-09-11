/*
 * displays.c
 *
 *  Created on: Feb 26, 2015
 *      Author: tB
 */
/*************************************************************************************************/

#include "displays.h"
#include "display.h"

#include <config.h>
#include <debug.h>
#include <text.h>
#include <stm32f10x.h>
#include <general.h>
#include <pins.h>

/*************************************************************************************************/

#define DISPLAYS_DEBUG_ENABLE	1


#if (DISPLAYS_DEBUG_ENABLE==0)
	#define DisplayDebug(str,...)
#else
	#include "debug.h"
	#include "delay.h"
	#define DisplayDebug(str,...) Debug(str,##__VA_ARGS__)
#endif

/*************************************************************************************************/

#ifdef STM32F100RC_BOARD

// ENUM | WIDTH | DATA PIN | CLOCK PIN | LATCH PIN
#define DisplaysList(display) \
	display(display_0, 4, PinB5,  PinB6,  PinB7) \
	display(display_1, 4, PinC1,  PinC2,  PinC3) \
	display(display_2, 4, PinB0,  PinB1,  PinB2) \
	display(display_3, 4, PinA13, PinA14, PinA15) \

#endif

#ifdef STM32F103C8_BOARD

// ENUM | WIDTH | DATA PIN | CLOCK PIN | LATCH PIN
#define DisplaysList(display) \
	display(display_0, 4, PinB5,  PinB6,  PinB7) \

#endif

/*************************************************************************************************/

#define DisplayEnum(e,width,dataPin,clockPin,latchPin) e,
enum { DisplaysList(DisplayEnum) };

#define Display(e,width,dataPin,clockPin,latchPin) {width,dataPin,clockPin,latchPin,(-1)},
display_t displays[] = { DisplaysList(Display) };

const u8 displaysCount = sizeof(displays)/sizeof(display_t);

/*************************************************************************************************/

void Displays_Init(void)
{
	for (u8 i=0; i<displaysCount; i++)
	{
		Display_Init(&displays[i]);
	}
}

/*************************************************************************************************/

void Display1_Set(u16 value)
{
	Display_SetValue(&displays[0], value);
}

void Display1Dot_Set(u16 dot)
{
	Display_SetDot(&displays[0], dot);
}

/*************************************************************************************************/

void Display2_Set(u16 value)
{
/*
 * UWAGA! To ¿e displays[1] nie istnieje (z powodu innej platformy)
 * nie oznacza ¿e taka konstrukcja nie mo¿e istnieæ. Obszar
 * display+1 i tak nie bêdzie u¿ywany.
 */
	Display_SetValue(&displays[1], value);
}

void Display2Dot_Set(u16 dot)
{
	Display_SetDot(&displays[1], dot);
}

/*************************************************************************************************/

void Display3_Set(u16 value)
{
	Display_SetValue(&displays[2], value);
}

void Display3Dot_Set(u16 dot)
{
	Display_SetDot(&displays[2], dot);
}

/*************************************************************************************************/

void Display4_Set(u16 value)
{
	Display_SetValue(&displays[3], value);
}

void Display4Dot_Set(u16 dot)
{
	Display_SetDot(&displays[3], dot);
}

/*************************************************************************************************/

#if (DISPLAYS_DEBUG_ENABLE==1)

void Displays_Test(void)
{
	Displays_Init();

	u16 val = 0;
	while (1)
	{
		Display1_Set(val++);
		Display2_Set(val++);
		Display3_Set(val++);
		Display4_Set(val++);

		DelayMs(250);
	}
}

#endif

/*************************************************************************************************/
