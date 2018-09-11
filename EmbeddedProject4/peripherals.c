/*
 * peripherals.c
 *
 *  Created on: Apr 9, 2014
 *      Author: TomB
 */

/*************************************************************************************************/

#include "peripherals.h"

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "usart2.h"

/*************************************************************************************************/

void Peripherals_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	// Disable JTAG
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); // Without it A14, B3 and B4 pins can not be used as standard IO

	Usart2_Init();
}

/*************************************************************************************************/
