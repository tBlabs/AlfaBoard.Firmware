/*
 * systick.c
 *
 *  Created on: Apr 9, 2014
 *      Author: TomB
 */

/*************************************************************************************************/

#include "systick.h"
#include "typedefs.h"
#include "stm32f10x.h"
#include "misc.h"

/*************************************************************************************************/

void SysTick_Handler(void) // interrupt every 1ms
{
	sysTickValue++;
}

/*************************************************************************************************/

bool SysTickInit(void)
{
	// ENABLE SYSTICK INTERRUPT AND LOAD START VALUE (WARNING: THIS FUNCTION OVERRIDES CTRL REGISTER!)
	if (SysTick_Config(3000)) 	// @8MHz/8 = 1MHz/1000 = 1000Hz(=1ms)
								// @24MHz/8 = 3MHz/3000 = 1000Hz(=1ms)
	{
		return false;
	}

	// SYSTICK CLOCK DIVIDER MUST BE SET AFTER SysTick_Config() FUNCTION (CAUSE SysTick_Config() OVERRIDES CTRL REGISTER)
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 	// @8MHz/8 = 1MHz
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	// @24MHz/8 = 3MHz

	return true;
}

/*************************************************************************************************/

