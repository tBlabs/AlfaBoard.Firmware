/*
 * display.c
 *
 *  Created on: Jun 9, 2015
 *      Author: TomB
 */

/*************************************************************************************************/

#include "display.h"
#include "pins.h"
#include "general.h"
#include "debug.h"
#include "delay.h"

/*************************************************************************************************/

#define PRINT_LEADING_ZEROS		true

/*
		a           5
	   f b         6 0
	    g			7
	   e c		   4 2
		d  dot		3  1
 */

#define a		(1<<5)
#define b		(1<<0)
#define c		(1<<2)
#define d		(1<<3)
#define e		(1<<4)
#define f		(1<<6)
#define g		(1<<7)
#define DOT		(1<<1)

const u8 digitsDefinitions[] =
{
	a|b|c|d|e|f,	// '0'
	  b|c,			// '1'
	a|b|  d|e|  g,	// '2'
	a|b|c|d|    g,	// '3'
	  b|c|    f|g,	// '4'
	a|  c|d|  f|g,	// '5'
	a|  c|d|e|f|g,	// '6'
	a|b|c,			// '7'
	a|b|c|d|e|f|g,	// '8'
	a|b|c|d|  f|g,	// '9'
};

#define NOTHING		0

#undef a
#undef b
#undef c
#undef d
#undef e
#undef f
#undef g

/*************************************************************************************************/

static void Latch(display_t * display)
{
	Pin_High(&display->latchPin);
	Pin_Low(&display->latchPin);
}

/*************************************************************************************************/

void Display_Clear(display_t * display)
{
	Pin_Low(&display->latchPin); // Latch off
	Pin_Low(&display->dataPin);

	for (u8 i=0; i < (8 * display->width); i++)
	{
		// Clock tick
		Pin_High(&display->clockPin);
		Pin_Low(&display->clockPin);
	}

	Latch(display);
}

/*************************************************************************************************/

void Display_Test(display_t * display)
{
	Pin_Low(&display->latchPin); // Latch off
	Pin_High(&display->dataPin);

	for (u8 i=0; i < (8 * display->width); i++)
	{
		// Clock tick
		Pin_High(&display->clockPin);
		Pin_Low(&display->clockPin);
	}

	Latch(display);
}

/*************************************************************************************************/

void Display_IoTest(display_t * display)
{
	Pin_Low(&display->dataPin);
	Pin_Low(&display->clockPin);
	Pin_Low(&display->latchPin);

	while (true)
	{
		Pin_Toggle(&display->dataPin);
		Pin_Toggle(&display->clockPin);
		Pin_Toggle(&display->latchPin);

		DelayMs(100);
	}
}

/*************************************************************************************************/

static void SendByte(display_t * display, u8 byte)
{
	for (s8 i=7; i>=0; i--) // From 7 to 0
	{
		if (IsBitSet(byte, i)) Pin_High(&display->dataPin);
		else Pin_Low(&display->dataPin);

		// Clock tick
		Pin_High(&display->clockPin);
		Pin_Low(&display->clockPin);

		Pin_High(&display->dataPin);
	}
}

/*************************************************************************************************/

void Display_Init(display_t * display)
{
	Pin_Init(&display->dataPin, GPIO_Mode_Out_PP);
	Pin_Init(&display->clockPin, GPIO_Mode_Out_PP);
	Pin_Init(&display->latchPin, GPIO_Mode_Out_PP);

	//display->oldValue = (-1); // Old/previous value must be "very different" from display values range
}

/*************************************************************************************************/

static void LoadValue(display_t * display, u16 value)
{
	boolean printZeros = PRINT_LEADING_ZEROS;
	u8 d = display->width;
	u8 mask = 0;

	while (d--)
	{
		u8 digit = DigitOfValue(value, d);

		if ((digit == 0) && (printZeros == false) && (d > 0))
		{
			mask = NOTHING;
		}
		else
		{
			if (PRINT_LEADING_ZEROS == false) printZeros = true;

			mask = digitsDefinitions[digit];
		}

		if ((d+1) == display->dot) // d+1 because dot=0 equals 'no dot'
		{
			mask |= DOT;
		}

		SendByte(display, mask);
	}
}

/*************************************************************************************************/

void Display_SetDot(display_t * display, u8 dot)
{
	if ((display->dot != dot) && (dot <= display->width))
	{
		display->dot = dot;

		// Po zmianie kropki konieczne jest prze³adowanie ekranu
		LoadValue(display, display->value);
		Latch(display);
	}
}

/*************************************************************************************************/

void Display_SetValue(display_t * display, u16 value)
{
	if (value != display->value)
	{
		display->value = value;

		LoadValue(display, display->value);
		Latch(display);
	}
}

/*************************************************************************************************/

