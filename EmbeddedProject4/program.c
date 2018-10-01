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

void Start(void)
{
	Platform_Init();

	Debug("Start.");
}

/*************************************************************************************************/

void MainTask(void)
{
	HostTask();
}
