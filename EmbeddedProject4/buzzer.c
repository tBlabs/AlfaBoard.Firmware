/*
 * buzzer.c
 *
 *  Created on: Nov 29, 2015
 *      Author: tB
 */
/*************************************************************************************************/

#include "buzzer.h"

#include <timer7.h>
#include <dac.h>
#include <typedefs.h>
#include <debug.h>

/*************************************************************************************************/

static boolean isEnabled;
static u16 oldFreq;
static u16 oldVolume;

/*************************************************************************************************/

void Buzzer1_Enable(boolean enable)
{
	if (isEnabled != enable)
	{
		if (enable)
		{
			DAC_Initialize();
			Timer7_Init();
			Buzzer1_SetFrequency(oldFreq);
			Buzzer1_SetVolume(oldVolume);
		}
		else
		{
			Timer7_Disable();
			DAC_Disable();
		}

		isEnabled = enable;
	}
}

/*************************************************************************************************/
/*
 * Ta funkcja powinna byæ wywo³ana tylko raz podczas
 * inicjalizowania platformy dlatego domyœlnym stanem
 * buzera jest stan wy³¹czenia.
 */
void Buzzer1_Init(void)
{
	Buzzer1_Enable(true); // Bez tego pojawia siê pisk zaraz po starcie
	Buzzer1_Enable(false);
}

/*************************************************************************************************/

void Buzzer1_SetVolume(percent_t volume)
{
	// Gamma correction = 0.3
	static u12 volumeLookUp[] = {
			0, 1029, 1266, 1430, 1559, 1667, 1761, 1844, 1919, 1989, 2052, 2112, 2168, 2220, 2270, 2318, 2363, 2407, 2448, 2488, 2527, 2564, 2600, 2635, 2669, 2702, 2734, 2765, 2795, 2825, 2854, 2882, 2909, 2936, 2963, 2989, 3014, 3039, 3063, 3087, 3111, 3134, 3157, 3179, 3201, 3223, 3244, 3265, 3286, 3306, 3326, 3346, 3366, 3385, 3404, 3423, 3441, 3460, 3478, 3496, 3513, 3531, 3548, 3565, 3582, 3599, 3615, 3631, 3648, 3664, 3679, 3695, 3711, 3726, 3741, 3756, 3771, 3786, 3801, 3815, 3830, 3844, 3858, 3872, 3886, 3900, 3914, 3927, 3941, 3954, 3968, 3981, 3994, 4007, 4020, 4032, 4045, 4058, 4070, 4083, 4095};

	if (oldVolume != volume)
	{
//		u12 vol = volume * 41;
//
//		if (vol > 0x0FFF) // DAC is 12-bit
//		{
//			vol = 0x0FFF;
//		}
		u12 vol = volumeLookUp[volume];

		Timer7_Dac1Value(vol);

		oldVolume = volume;
	}
}

/*************************************************************************************************/

void Buzzer1_SetFrequency(u16 freq)
{
	if (oldFreq != freq)
	{
		Timer7_SetPeriod(freq);

		oldFreq = freq;
	}
}

/*************************************************************************************************/

void Buzzer1_Test(void)
{
	Buzzer1_Init();

	Buzzer1_SetVolume(75);
	Buzzer1_SetFrequency(1500);
//	u16 i=0;
	while(1)
	{
//		DebugDec(i);
//		Buzzer1_SetFrequency(i);
//		i+=100;
//		if (i>10000) i=1000;
//		DelayMs(50);
	}
}

/*************************************************************************************************/
