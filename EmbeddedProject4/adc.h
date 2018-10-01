/*
 * adc.h
 *
 *  Created on: Mar 3, 2015
 *      Author: tB
 */

#ifndef ADC_H_
#define ADC_H_

/*************************************************************************************************/

#include "typedefs.h"

/*************************************************************************************************/

void Adc_Init(void);
bool Temperature(u16 * REF_temper);
void ADCs_Engine(void);
u32 Adc1_Value(void);
u32 Adc2_Value(void);
u16 Thermo1_Value(void); // not working ;/

/*** If ADC_DEBUG_ENABLE==1 **********************************************************************/

void Adc_Test(void);

/*************************************************************************************************/

#endif /* ADC_H_ */
