#include "program.h"
#include "debug.h"
#include "stm32f10x.h"
#include "timeout.h"
#include "leds.h"
#include "host.h"
#include "buttons.h"
#include "adc.h"

int main(void)
{
	System_Init(); // initialize clocks and peripherals

 	Start(); // user things

	timeout_t repater;

	while (true)
	{
		MainTask();
		
		if (0)
		if (Tick(&repater, 1000))
		{
		//	SendValue(1, 100);
			//Debug("debug");
			Led1_Toggle();
		}
		
		ADCs_Engine();
		
//		if (Button1_Get()==buttonState_PRESSED)
//		{
//			Led2_Toggle();
//		}
	}
}
