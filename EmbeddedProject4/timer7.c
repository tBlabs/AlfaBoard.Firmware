/*
 * timer7.c
 *
 *  Created on: Nov 29, 2015
 *      Author: tB
 */

/*************************************************************************************************/

#include "timer7.h"

#include "dac.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "debug.h"
#include "global.h"
#include "general.h"

/*************************************************************************************************/

static u16 dac1Value = 0;
static boolean isInitialised = false;

/*************************************************************************************************/

void Timer7_Dac1Value(u12 dacValue)
{
	dac1Value = dacValue;
}

/*************************************************************************************************/

void TIM7_IRQHandler(void)
{
	static u8 toggle = 1;

	if(TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);

		if ((toggle = 1-toggle))
		{
			DAC1_Value(dac1Value);
		}
		else
		{
			DAC1_Value(0);
		}
	}
}

/*************************************************************************************************/

void Timer7_Disable(void)
{
	if (isInitialised)
	{
		TIM_ITConfig(TIM7, TIM_IT_Update, DISABLE);
		TIM_Cmd(TIM7, DISABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, DISABLE);

		isInitialised = false;
	}
}

/*************************************************************************************************/

void Timer7_SetPeriod(u16 period)
{
	if (period == 0)
	{
		// Wy³¹czenie timera
	//	Timer7_Disable();
	}
	else
	{
		Timer7_Init(); // Uruchomi siê tylko jeœli zajdzie potrzeba

		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_TimeBaseStructure.TIM_Prescaler = 12-1; // 24MHz / 12 = 2MHz
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseStructure.TIM_Period = (u16)(1000000UL/(u32)period)-1;
		TIM_TimeBaseStructure.TIM_ClockDivision = 0;

		TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
	}
}

/*************************************************************************************************/

void Timer7_Init(void)
{
	if (isInitialised == false)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

		NVIC_Init(&NVIC_InitStructure);

		// Interrupt enable
		TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);

		// Enable counter
		TIM_Cmd(TIM7, ENABLE);

		isInitialised = true;
	}
}

/*************************************************************************************************/
