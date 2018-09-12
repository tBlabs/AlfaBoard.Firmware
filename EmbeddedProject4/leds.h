/*
 * led.h
 *
 *  Created on: Jan 6, 2015
 *      Author: tB
 */

#ifndef LED_H_
#define LED_H_

/*************************************************************************************************/

#include "typedefs.h"

/*************************************************************************************************/

void Leds_Init(void);

void Led1_Set(u16 ledState); // Led is on when ledState!=0
void Led2_Set(u16 ledState);
void Led3_Set(u16 ledState);
void Led4_Set(u16 ledState);
boolean Led1_Get();
boolean Led2_Get();
boolean Led3_Get();
boolean Led4_Get();

/*** If LED_DEBUG_ENABLE==1 **********************************************************************/

void Leds_Test(void);

/*************************************************************************************************/

#endif /* LED_H_ */
