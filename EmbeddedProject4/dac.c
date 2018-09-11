/*
 * dac.c
 *
 *  Created on: Nov 29, 2015
 *      Author: tB
 */
/*************************************************************************************************/

#include "dac.h"

#include "stm32f10x.h"
#include "stm32f10x_dac.h"
#include "typedefs.h"
#include "pins.h"
#include "debug.h"
#include <delay.h>

/*************************************************************************************************/

/*
 * DAC outputs:
 * DAC1 - A.4 <--- selected
 * DAC2 - A.5
 *
 */

void DAC_Initialize(void)
{
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // Quote from datasheet: "In order to avoid parasitic consumption, the PA4 or PA5 pin should first be configured to analog (AIN)."
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);

	Pin_Init(&(pin_t)PinA4, GPIO_Mode_AIN);

	DAC_InitTypeDef DAC_InitStructure;
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);

	DAC_Cmd(DAC_Channel_1, ENABLE);
	DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);
}

/*************************************************************************************************/

void DAC_Disable(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, DISABLE);
	DAC_Cmd(DAC_Channel_1, DISABLE);
	DAC_SoftwareTriggerCmd(DAC_Channel_1, DISABLE);
}

/*************************************************************************************************/

void DAC1_Value(u12 value)
{
	DAC_SetChannel1Data(DAC_Align_12b_R, value);
	DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);
}

/*************************************************************************************************/
/*
 *         +----------+
 *         |          |     led
 *         |        A4|-----|>|---[100Om]--- (-)
 *         |    uC    |
 */

void DAC1_Test(void)
{
	DAC_Initialize();

	u16 i=0;
	
	while(1)
	{
		DebugDec(i);
		DAC1_Value(i);
		i+=100;
		i%=4000;
		DelayMs(100);
	}
}
