#include "pwms.h"
#include "timer3.h"
#include "general.h"
#include "stm32f10x.h"
#include "typedefs.h"

/*************************************************************************************************/
/*
 *
 * Wyj�� PWM nale�y szuka� w ustawieniach timera 3
 *
 *
 *  * Timer 3 remap options:
 * - no remap:
 * 		ch1 @A6	<-- used for STM32F103C8_BOARD
 * 		ch2 @A7	<-- used for STM32F103C8_BOARD
 * 		ch3 @B0	<-- used for STM32F103C8_BOARD
 * 		ch4 @B1	<-- used for STM32F103C8_BOARD
 * - partial remap:
 * 		ch1 @B4
 * 		ch2 @B5
 * 		ch3 @B0
 * 		ch4 @B10
 * 		ch4 @B1
 * - full remap:
 *  	ch1 @C6	<-- used for STM32F100RC_BOARD
 *  	ch2 @C7	<-- used for STM32F100RC_BOARD
 *  	ch3 @C8	<-- used for STM32F100RC_BOARD
 *  	ch4 @C9	<-- used for STM32F100RC_BOARD
 *
 */

/*************************************************************************************************/

void Pwm_Init(void)
{
	Timer3_Init();
}

/*************************************************************************************************/

void Pwm1_Set(u16 value)
{
	Timer3Channel1Duty(value); 
}

/*************************************************************************************************/

void Pwm2_Set(u16 value)
{
	Timer3Channel2Duty(value);
}

/*************************************************************************************************/

void Pwm3_Set(u16 value)
{
	Timer3Channel3Duty(value);
}

/*************************************************************************************************/

void Pwm4_Set(u16 value)
{
	Timer3Channel4Duty(value); 
}

/*************************************************************************************************/
