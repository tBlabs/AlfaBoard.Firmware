/*
 * Korzystnie:
 *
 * Konfiguracja sprzêtowa zdefiniowana jest w pliku platform.h w katalogu Logic.
 * Edycji wymagaj¹:
 * - lista PhysicalDevicesList,
 * - lista PadsList
 * - sta³a PLATFORM_NAME
 * - ewentualnie dla porz¹dku mo¿na nanieœæ zmiany w pins.h
 *
 */

#include "program.h"
#include "debug.h"
#include "stm32f10x.h"

int main(void)
{
	System_Init(); // initialize clocks and peripherals

 	Start(); // user things
//Debug("!!!!++++++++++++++++++++!!!!!!!!!!!!!!!!!!");
// 	u32 rcc = (u32)RCC;
//	Debug("reset register bits 31:24 = %b", rcc >> 24);
//	Debug("reset register = %B", RCC);


//RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
//RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
//
//	// Check if the Power On Reset flag is set
//	if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
//	{
//		Debug("Power On Reset occurred..");
//	}
//	else
//	// Check if the Pin Reset flag is set
//	if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
//	{
//		Debug("External Reset occurred..");
//	}
//	else
//		Debug("other");

	while (true)
	{
		MainTask();
		
		
	}
}
