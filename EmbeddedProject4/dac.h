/*
 * dac.h
 *
 *  Created on: Nov 29, 2015
 *      Author: tB
 */

#ifndef DAC_H_
#define DAC_H_


#include "typedefs.h"


void DAC_Initialize(void);
void DAC_Disable(void);
void DAC1_Value(u12 value);
void DAC1_Test(void);

#endif /* DAC_H_ */
