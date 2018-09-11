/*
 * platform.c
 *
 *  Created on: Feb 11, 2015
 *      Author: tB
 */
/*************************************************************************************************/

#include "platform.h"

#include "logicGlobals.h"
#include "debug.h"
#include "leds.h"
#include "buttons.h"
#include "pwms.h"
#include "displays.h"
#include "rtc.h"
#include "adc.h"
#include "parser.h"
#include "temperature_sensor.h"
#include "buzzer.h"
#include "system.h"
#include "general.h"
#include "string.h"

/*************************************************************************************************/

const char * platformName = PLATFORM_NAME;

/*************************************************************************************************/

void Platform_Init(void)
{
	Leds_Init();
	Buttons_Init();
	Pwm_Init();
	Displays_Init();
	Clock_Init();
	Adc_Init();
	TemperatureSensor_Init();
	Buzzer1_Init();
}

/*************************************************************************************************/

const physicalDevice_t physicalDevices[] = { PhysicalDevicesList(PhysicalDevice) };
const u8 physicalDevicesCount = sizeof(physicalDevices)/sizeof(physicalDevice_t);


const padFunction_t physicalDevicesPads[] = { PadsList(PadFunction) };
const u8 physicalDevicesPadsCount = sizeof(physicalDevicesPads)/sizeof(padFunction_t);

/*************************************************************************************************/

void Platform_Intro(cycleBuffer_t * buffer)
{
	// Header
	CycleBuffer_AddString(buffer, (char*)platformName);
	CycleBuffer_Add(buffer, LOGIC_MAPS_COUNT);
	CycleBuffer_AddU16(buffer, LOGIC_MAP_CAPACITY);
	CycleBuffer_Add(buffer, PAD_SIZE*8); // Size to bits count

	// Physical devices list
	CycleBuffer_Add(buffer, physicalDevicesCount);
	for (u8 i=0; i<physicalDevicesCount; i++)
	{
		CycleBuffer_Add(buffer, (u8)physicalDevices[i].family);
		CycleBuffer_AddString(buffer, physicalDevices[i].name);
	}
}

/*************************************************************************************************/
