/*
 * timer3.c
 *
 *  Created on: 1 paü 2014
 *      Author: TomB
 */
/*************************************************************************************************/

#include "timer3.h"

#include <config.h>
#include "typedefs.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "pins.h"

/*************************************************************************************************/
/*
 * Timer 3 remap options:
 * - no remap:
 * 		ch1 @A6	<-- used for STM32F103C8_BOARD
 * 		ch2 @A7	<-- used for STM32F103C8_BOARD
 * 		ch3 @B0	<-- used for STM32F103C8_BOARD
 * 		ch4 @B1	<-- used for STM32F103C8_BOARD
 * - partial remap:
 * 		ch1 @B4
 * 		ch2 @B5
 * 		ch3 @B0
 * 		ch4 @B1
 * - full remap:
 *  	ch1 @C6	<-- used for STM32F100RC_BOARD
 *  	ch2 @C7	<-- used for STM32F100RC_BOARD
 *  	ch3 @C8	<-- used for STM32F100RC_BOARD
 *  	ch4 @C9	<-- used for STM32F100RC_BOARD
 *
 */
void Timer3_Init(void)
{
	// ENABLE CLOCK FOR PORT C
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	// ENABLE AFIO (ALTERNATIVE FUNCTIONS) CLOCK
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

#ifdef STM32F100RC_BOARD

	// REMAP TIMER 3 OUTPUTS TO PORTC PIN 6,7,8 AND 9 (CAN NOT REMAP TO ANOTHER PORT OR PIN! /there are only 3 combinations/)
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);

	// OUTPUTS CONFIG
	Pin_Init(&(pin_t)PinC6, GPIO_Mode_AF_PP);
	Pin_Init(&(pin_t)PinC7, GPIO_Mode_AF_PP);
	Pin_Init(&(pin_t)PinC8, GPIO_Mode_AF_PP);
	Pin_Init(&(pin_t)PinC9, GPIO_Mode_AF_PP);

#endif

#ifdef STM32F103C8_BOARD

	// OUTPUTS CONFIG
	Pin_Init(&(pin_t)PinA6, GPIO_Mode_AF_PP);
	Pin_Init(&(pin_t)PinA7, GPIO_Mode_AF_PP);
	Pin_Init(&(pin_t)PinB0, GPIO_Mode_AF_PP);
	Pin_Init(&(pin_t)PinB1, GPIO_Mode_AF_PP);

#endif

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	// ENABLE CLOCK FOR TIMER 3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  	// TIMER 3 CONFIG (MAX CLOCK = APB1 = 24MHz) CORE=8MHz
  	TIM_TimeBaseStructure.TIM_Period = 999; // 2MHz / (999+1) = 2kHz
  	TIM_TimeBaseStructure.TIM_Prescaler = 3; // 8MHz / (3+1) = 2MHz

  	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  	// CHANNEL 1 IN PWM MODE (DUTY CYCLE = 0.0%)
  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_Pulse = 0;
  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  	TIM_OC1Init(TIM3, &TIM_OCInitStructure);

  	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

  	// CHANNEL 2 IN PWM MODE (DUTY CYCLE = 0.0%)
  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_Pulse = 0;
  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  	TIM_OC2Init(TIM3, &TIM_OCInitStructure);

  	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

  	// CHANNEL 3 IN PWM MODE (DUTY CYCLE = 0.0%)
  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_Pulse = 0;
  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  	TIM_OC3Init(TIM3, &TIM_OCInitStructure);

  	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

  	// CHANNEL 4 IN PWM MODE (DUTY CYCLE = 0.0%)
  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_Pulse = 0;
  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  	TIM_OC4Init(TIM3, &TIM_OCInitStructure);

  	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

  	TIM_ARRPreloadConfig(TIM3, ENABLE);

  	TIM_Cmd(TIM3, ENABLE);
}

/*************************************************************************************************/

void Timer3_Enable(void)
{
	// ENABLE TIMER CLOCK
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	// ENABLE TIMER
	TIM_Cmd(TIM3, ENABLE);
}

/*************************************************************************************************/

void Timer3_Disable(void)
{
	// ENABLE TIMER CLOCK
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, DISABLE);

	// ENABLE TIMER
	TIM_Cmd(TIM3, DISABLE);

	// DISABLE PINS REMAP
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, DISABLE);
}

/*************************************************************************************************/

void Timer3Channel1Duty(u16 duty) // Timer 3 (output compare) Channel 1 (pulse) Duty
{
	static u16 oldDuty;

	if (oldDuty != duty)
	{
		TIM_OCInitTypeDef TIM_OCInitStructure;

		TIM_OCInitStructure.TIM_Pulse = duty;

	 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	  	TIM_OC1Init(TIM3, &TIM_OCInitStructure);

	  	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

	  	oldDuty = duty;
	}
}

/*************************************************************************************************/

void Timer3Channel2Duty(u16 duty)
{
	static u16 oldDuty;

	if (oldDuty != duty)
	{
		TIM_OCInitTypeDef TIM_OCInitStructure;

		TIM_OCInitStructure.TIM_Pulse = duty;

	 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	  	TIM_OC2Init(TIM3, &TIM_OCInitStructure);

	  	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

	  	oldDuty = duty;
	}
}

/*************************************************************************************************/

void Timer3Channel3Duty(u16 duty)
{
	static u16 oldDuty;

	if (oldDuty != duty)
	{
		TIM_OCInitTypeDef TIM_OCInitStructure;

		TIM_OCInitStructure.TIM_Pulse = duty;

	 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	  	TIM_OC3Init(TIM3, &TIM_OCInitStructure);

	  	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

	  	oldDuty = duty;
	}
}

/*************************************************************************************************/

void Timer3Channel4Duty(u16 duty)
{
	static u16 oldDuty;

	if (oldDuty != duty)
	{
		TIM_OCInitTypeDef TIM_OCInitStructure;

		TIM_OCInitStructure.TIM_Pulse = duty;

	 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	  	TIM_OC4Init(TIM3, &TIM_OCInitStructure);

	  	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

	  	oldDuty = duty;
	}
}

/*************************************************************************************************/


