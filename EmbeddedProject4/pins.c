/*
 * pins.c
 *
 *  Created on: May 11, 2015
 *      Author: tB
 */
/*************************************************************************************************/

#include "pins.h"

#include "stm32f10x.h"

/*************************************************************************************************/

void Pin_Init(pin_t * pin, GPIOMode_TypeDef mode)
{
	RCC_APB2PeriphClockCmd(pin->clock, ENABLE);

	GPIO_InitTypeDef IOConfig;
	IOConfig.GPIO_Pin = pin->pin;
	IOConfig.GPIO_Mode = mode;
	IOConfig.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(pin->gpio, &IOConfig);
}

/*************************************************************************************************/

void Pin_Low(pin_t * pin)
{
	GPIO_WriteBit(pin->gpio, pin->pin, Bit_RESET);
}

/*************************************************************************************************/

void Pin_High(pin_t * pin)
{
	GPIO_WriteBit(pin->gpio, pin->pin, Bit_SET);
}

/*************************************************************************************************/

void Pin_Toggle(pin_t * pin)
{
	GPIO_WriteBit(pin->gpio, pin->pin, 1-GPIO_ReadInputDataBit(pin->gpio, pin->pin));
}

/*************************************************************************************************/

void Pin_Set(pin_t * pin, pinState_t pinState)
{
	switch (pinState)
	{
		case pinState_HIGH: Pin_High(pin); break;
		case pinState_LOW: Pin_Low(pin); break;
	}
}

/*************************************************************************************************/

boolean Pin_IsLow(pin_t * pin)
{
	if (GPIO_ReadInputDataBit(pin->gpio, pin->pin)) return false;
	else return true;
}

/*************************************************************************************************/

boolean Pin_IsHigh(pin_t * pin)
{
	if (!GPIO_ReadInputDataBit(pin->gpio, pin->pin)) return true;
	else return false;
}

/*************************************************************************************************/

