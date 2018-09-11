/*
 * program.c
 *
 *  Created on: Apr 9, 2014
 *      Author: TomB
 */

/*************************************************************************************************/

#include "program.h"

#include "system.h"
#include "debug.h"
#include "timeout.h"
#include "delay.h"
#include "host.h"
#include "peripherals.h"
#include "platform.h"
#include "clock.h"

/*************************************************************************************************/

void System_Init(void)
{
	Clocks_Init();

	Peripherals_Init();
}

/*************************************************************************************************/

//u8 tab[] =
//{
//	/*  0 */	0, // null
//	/*  1 */	1, // in1
//	/*  2 */	1, // in2
//	/*  3 */	0, // in3
//	/*  4 */	0, // in4
//	/*  5 */	13, // led1 - watchs for map[13] - it's gate output
//	/*  6 */	21, // led2 - watchs for map[21] - it's pulsar toggle output
//	/*  7 */	22, // led3 - watchs for map[22] - it's pulsar pulse output
//	/*  8 */	3, // led4 - watchs for map[3] - it's in3 output
//	/*  9 */	virtualDeviceFamily_GATE,
//	/* 10 */	gate_AND,
//	/* 11 */	1, // padA - watchs for map[1] - it's in1 state
//	/* 12 */	2, // padB - watchs for map[2] - it's in1 state
//	/* 13 */	0, // padQ
//	/* 14 */	virtualDeviceFamily_PULSAR,
//	/* 15,16 */			250, 0, // interval (little-endian)
//	/* 17,18,19,20 */ 	0, 0, 0, 0, // timeKeeper (little-endian)
//	/* 21 */	0, // padQ-toggle
//	/* 22 */	0, // padQ-pulse
//};



/*************************************************************************************************/


/*************************************************************************************************/

void Start(void)
{
	Debug("Initializing platform... (keep Key1 pressed to omit maps restore)");
	Platform_Init();


//	if (Button1_Get() == buttonState_NOT_PRESSED)
//	{
//		Debug("Restoring maps...");
//		Maps_Restore();
//		Debug("Restored.");
//	}
//	else
//	{
//		Debug("Maps resetore omitted.");
//		Display1_Set(1);
//		Display2_Set(2);
//		Display3_Set(3);
//		Display4_Set(4);
//	}

	Debug("Start.");
}

/*************************************************************************************************/

void MainTask(void)
{
	HostTask();
}
