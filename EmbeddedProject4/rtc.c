/*
 * rtc.c
 *
 *  Created on: Nov 26, 2015
 *      Author: tB
 */
#include "rtc.h"

#include "clockvalues.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_bkp.h"
#include "stm32f10x_pwr.h"
#include "debug.h"

/*************************************************************************************************/

clockValues_t clockValues;

#define SystemTimestamp RTC_GetCounter()


/*************************************************************************************************/

void Clock_Set(u32 timestamp)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

	PWR_BackupAccessCmd(ENABLE);
	RTC_WaitForLastTask();

	RTC_SetCounter(timestamp);
	RTC_WaitForLastTask();

	PWR_BackupAccessCmd(DISABLE);
}

void Clock_AddSeconds(u32 secondsToAdd)
{
	if (secondsToAdd > 0)
	{
		Clock_Set(SystemTimestamp + secondsToAdd);
	}
}

void Clock_SubtractSeconds(u32 secondsToSubtract)
{
	if (secondsToSubtract > 0)
	{
		//
		if (SystemTimestamp >= secondsToSubtract) // >= ????
		{
			Clock_Set(SystemTimestamp - secondsToSubtract);
		}
	}
}

/*
 * Systemowy timestamp jest przeliczany na wartoœci
 * odczytywalne dla ludzi dopiero w momencie ich
 * odczytu.
 * Sprawdzenia czy timestamp odpowiada temu co jest
 * w strukturze ClockValues odbywa siê przez porównanie
 * wewnêtrznego timestampa tej struktury z timestampem
 * systemowym.
 */

static void UpdateClockValues(void)
{
	timestamp_t ts = SystemTimestamp;

	if (ts > clockValues.timestamp)
	{
		ClockValues_Add(&clockValues, ts - clockValues.timestamp);

		clockValues.timestamp = ts;
	}
	else
	if (ts < clockValues.timestamp)
	{
		s64 diff = (signed long long)clockValues.timestamp - (signed long long)ts;

		ClockValues_Sub(&clockValues, diff);

		clockValues.timestamp = ts;
	}
}

u8 Clock_GetHours(void)
{
	UpdateClockValues();

	return clockValues.hours;
}

u8 Clock_GetMinutes(void)
{
	UpdateClockValues();

	return clockValues.minutes;
}

u8 Clock_GetSeconds(void)
{
	UpdateClockValues();

	return clockValues.seconds;
}

u8 Clock_GetDayOfWeek(void)
{
	UpdateClockValues();

	return clockValues.dayOfWeek;
}

u8 Clock_GetDay(void)
{
	UpdateClockValues();

	return clockValues.day + 1;
}

u8 Clock_GetMonth(void)
{
	UpdateClockValues();

	return clockValues.month + 1;
}

u16 Clock_GetYear(void)
{
	UpdateClockValues();

	return clockValues.year;
}

static void RTC_Configuration(void)
{
	// Enable PWR and BKP clocks
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

	// Allow access to BKP Domain
	PWR_BackupAccessCmd(ENABLE);

	// Reset Backup Domain
	BKP_DeInit();

	// Enable LSE
	RCC_LSEConfig(RCC_LSE_ON);

	// Wait till LSE is ready
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);

	// Select LSE as RTC Clock Source
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

	// Enable RTC Clock
	RCC_RTCCLKCmd(ENABLE);

	// Wait for RTC registers synchronization
	RTC_WaitForSynchro();

	// Wait until last write operation on RTC registers has finished
	RTC_WaitForLastTask();

	// Enable the RTC Second
	RTC_ITConfig(RTC_IT_SEC, ENABLE);

	// Wait until last write operation on RTC registers has finished
	RTC_WaitForLastTask();

	// Set RTC prescaler: set RTC period to 1sec
	RTC_SetPrescaler(32767); // RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1)

	// Wait until last write operation on RTC registers has finished
	RTC_WaitForLastTask();
}

void Clock_Init(void)
{
	ClockValues_Init(&clockValues);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A9)
	{
		RTC_Configuration();

		RTC_WaitForLastTask();

		RTC_SetCounter(0);

		RTC_WaitForLastTask();

		BKP_WriteBackupRegister(BKP_DR1, 0xA5A9);
	}
	else
	{
		// Check if the Power On Reset flag is set
		if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
		{
			// Power On Reset occurred..
		}
		else
		// Check if the Pin Reset flag is set
		if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
		{
			// External Reset occurred..
		}

		// Wait for RTC registers synchronization
		RTC_WaitForSynchro();

		// Enable the RTC Second
		RTC_ITConfig(RTC_IT_SEC, ENABLE);

		// Wait until last write operation on RTC registers has finished
		RTC_WaitForLastTask();
	}

	// Clear reset flags
	RCC_ClearFlag();
}
