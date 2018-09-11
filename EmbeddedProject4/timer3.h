/*
 * timer3.h
 *
 *  Created on: 1 paü 2014
 *      Author: TomB
 */

#ifndef TIMER3_H_
#define TIMER3_H_

/*************************************************************************************************/

#include "typedefs.h"

/*************************************************************************************************/

void Timer3_Init(void);
void Timer3_Enable(void);
void Timer3_Disable(void);
void Timer3Channel1Duty(u16 duty);
void Timer3Channel2Duty(u16 duty);
void Timer3Channel3Duty(u16 duty);
void Timer3Channel4Duty(u16 duty);

/*************************************************************************************************/

#endif /* TIMER3_H_ */
