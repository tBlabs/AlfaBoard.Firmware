/*
 * timer7.h
 *
 *  Created on: Nov 29, 2015
 *      Author: tB
 */

#ifndef TIMER7_H_
#define TIMER7_H_

/*************************************************************************************************/

#include <typedefs.h>

void Timer7_Init(void);
void Timer7_Dac1Value(u12 dacValue);
void Timer7_SetPeriod(u16 period);
void Timer7_Disable(void);

/*************************************************************************************************/

#endif /* TIMER7_H_ */
