/*
 * temperature_sensor.c
 *
 *  Created on: Sep 21, 2015
 *      Author: tB
 */
/*************************************************************************************************/

#include "temperature_sensor.h"

#include <spi2.h>
#include <typedefs.h>
#include <timeout.h>
#include <debug.h>

/*************************************************************************************************/

void TemperatureSensor_Init(void)
{
	Spi2_Init();
}

/*************************************************************************************************/

temperature_t TemperatureSensor_GetTemperature(void)
{
	static temperature_t temperature;
	static u32 sum;
	static u16 samplesCount;
	static timeout_t readSensorMoment;

	if (Tick(&readSensorMoment, 100))
	{
		u32 temp = 0;

		u16 data = Spi2_Read();

		/*
		 * W TYM MIEJSCU POWINNO BYÆ
		 * SPRAWDZANIE CZY WARTOŒÆ
		 * ULEG£A ZMIANIE
		 *
		 */
		if ((data & 0b100)==0) return 0;
		else
		{
			temp = data >> 3;
			temp *= 625;
			temp /= 1000;
		}

		sum += temp;

		if (samplesCount >= 20)
		{

			temperature = (temperature_t)(sum/samplesCount);
			sum = 0;
			samplesCount = 0;

			//DebugDec(temperature);
		}
		samplesCount++;
		//temperature = temp/10;

	}

	return temperature;
	//return temp/10;
}

/*************************************************************************************************/
