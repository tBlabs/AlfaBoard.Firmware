/*
 * buttons.c
 *
 *  Created on: Jan 17, 2015
 *      Author: tB
 */

/*************************************************************************************************/

#include "buttons.h"

#include "pins.h"

/*************************************************************************************************/

// ENUM | PIN
#define ButtonsList(button) \
	button(button_0, 	PinB8) \
	button(button_1, 	PinB9) \
	button(button_2, 	PinB10) \
	button(button_3, 	PinB11) \

/*************************************************************************************************/

typedef struct
{
	pin_t pin;
}
button_t;

#define ButtonEnum(e,pin) e,
enum { ButtonsList(ButtonEnum) };

#define Button(e,pin) {pin},
button_t buttons[] = { ButtonsList(Button) };

const u8 buttonsCount = sizeof(buttons)/sizeof(button_t);

/*************************************************************************************************/

void Buttons_Init(void)
{
	for (u8 i=0; i<buttonsCount; i++)
	{
		Pin_Init(&buttons[i].pin, GPIO_Mode_IPU);
	}
}

/*************************************************************************************************/

buttonState_t Button1_Get(void)
{
	if (Pin_IsLow(&buttons[button_0].pin)) return buttonState_PRESSED;
	else return buttonState_NOT_PRESSED;
}

/*************************************************************************************************/

buttonState_t Button2_Get(void)
{
	if (Pin_IsLow(&buttons[button_1].pin)) return buttonState_PRESSED;
	else return buttonState_NOT_PRESSED;
}

/*************************************************************************************************/

buttonState_t Button3_Get(void)
{
	if (Pin_IsLow(&buttons[button_2].pin)) return buttonState_PRESSED;
	else return buttonState_NOT_PRESSED;
}

/*************************************************************************************************/

buttonState_t Button4_Get(void)
{
	if (Pin_IsLow(&buttons[button_3].pin)) return buttonState_PRESSED;
	else return buttonState_NOT_PRESSED;
}

/*************************************************************************************************/
