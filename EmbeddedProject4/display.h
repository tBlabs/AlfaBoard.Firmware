/*
 * display.h
 *
 *  Created on: Jun 10, 2015
 *      Author: TomB
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_


/*************************************************************************************************/

#include "typedefs.h"
#include "pins.h"

/*************************************************************************************************/

/*
	Single (2 or 4 displays) board:

       +---------------------------+
	   |                           |-- Vcc (2-6V)
	   |          DISPLAY          |== GND / Data (GND on top, Data on bottom)
       |    	 (top view)  	   |== OE / Clock (OE on top, Clock on bottom)
       |		 	               |-- Latch
       |	 [common cathode]	   |-- GND
       +---------------------------+
*/

typedef struct
{
	u8 width; // number of 7-seg displays
	pin_t dataPin;
	pin_t clockPin;
	pin_t latchPin;
	u8 dot;
	u16 value;
}
display_t;

/*************************************************************************************************/

void Display_Init(display_t * display);
void Display_Clear(display_t * display);
void Display_SetValue(display_t * display, u16 value);
void Display_SetDot(display_t * display, u8 dot);
void Display_IoTest(display_t * display);
void Display_Test(display_t * display);

/*************************************************************************************************/

#endif /* DISPLAY_H_ */
