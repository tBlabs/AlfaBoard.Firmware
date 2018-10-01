/*
 * temperature_sensor.h
 *
 *  Created on: Sep 21, 2015
 *      Author: tB
 */

#ifndef TEMPERATURE_SENSOR_H_
#define TEMPERATURE_SENSOR_H_

#include "typedefs.h"

typedef u16 temperature_t; // centy-celcius value :) ex. 36,6*C = 366

void TemperatureSensor_Init(void);
u32 TemperatureSensor_GetTemperature(void);

#endif /* TEMPERATURE_SENSOR_H_ */
