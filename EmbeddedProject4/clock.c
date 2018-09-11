/*
 * clock.c
 *
 *  Created on: Apr 9, 2014
 *      Author: TomB
 */

/*************************************************************************************************/

#include "clock.h"
#include "stm32f10x.h"
#include <stm32f10x_rcc.h>
#include <stm32f10x_flash.h>

/*************************************************************************************************/
/*
static void HSI_8MHz(void) // High Speed Internal Oscillator
{
	RCC_HSICmd(ENABLE);

	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY)==RESET);

	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	FLASH_SetLatency(FLASH_Latency_0);

	// PERIPHERAL BUS 1: PCLK1 = HCLK (MAX 24MHz)
	RCC_PCLK1Config(RCC_HCLK_Div1);

	// PERIPHERAL BUS 2: PCLK2 = HCLK (MAX 24MHz)
	RCC_PCLK2Config(RCC_HCLK_Div1);
}
*/
/*************************************************************************************************/

static void HSI_24MHz(void) // High Speed Internal Oscillator
{
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_6);
	RCC_PLLCmd(ENABLE);
	// Wait till PLL is ready
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
	{
	}

	// Select PLL as system clock source
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	// Wait till PLL is used as system clock source
	while (RCC_GetSYSCLKSource() != 0x08)
	{
	}

	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	FLASH_SetLatency(FLASH_Latency_2);

	// PERIPHERAL BUS 1: PCLK1 = HCLK (MAX 24MHz)
	RCC_PCLK1Config(RCC_HCLK_Div1);

	// PERIPHERAL BUS 2: PCLK2 = HCLK (MAX 24MHz)
	RCC_PCLK2Config(RCC_HCLK_Div1);
}

/*************************************************************************************************/

void ClockInit(void)
{
	RCC_DeInit(); // common for all init functions

	HSI_24MHz(); // any change at this point is likely to require changes in systick (systick.c)
}

/*************************************************************************************************/


