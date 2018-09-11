/*
 * ClockValues.c
 *
 *  Created on: Nov 26, 2015
 *      Author: tB
 */
/*************************************************************************************************/

#include "clockvalues.h"

#include <debug.h>

/*************************************************************************************************/

#if (TIMESTAMP_START_YEAR==2015)
	#define FIRST_DAY_OF_WEEK	Thursday
#elif (TIMESTAMP_START_YEAR==2000)
	#define FIRST_DAY_OF_WEEK	Saturday
#elif (TIMESTAMP_START_YEAR==1970)
	#define FIRST_DAY_OF_WEEK	Thursday
#else
	#error "First day-of-week of year TIMESTAMP_START_YEAR is unknown"
#endif

/*************************************************************************************************/


#define SECONDS_PER_DAY 86400 // 24 * 60 * 60

enum // not for humans! don't use in humanReadableClockValues_t!
{
	January = 0,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December
};

static u32 DaysFromSeconds(u32 seconds)
{
	return seconds / SECONDS_PER_DAY;
}

static boolean IsLeapYear(u16 year)
{
	if ((year % 4)==0) return true;

	return false;
}

static u8 DaysInMonth(u8 month, u16 year)
{
	switch (month)
	{
		case January: return 31;
		case February: if (IsLeapYear(year)) return 29; else return 28;
		case March: return 31;
		case April: return 30;
		case May: return 31;
		case June: return 30;
		case July: return 31;
		case August: return 31;
		case September: return 30;
		case October: return 31;
		case November: return 30;
		case December: return 31;
	}

	return 0;
}

static void DayPlus(clockValues_t * ClockValues)
{
	ClockValues->day++;

	ClockValues->dayOfWeek++;
	ClockValues->dayOfWeek %= DAYS_OF_WEEK_COUNT;

	if (ClockValues->day >= DaysInMonth(ClockValues->month, ClockValues->year))
	{
		ClockValues->day = 0;

		ClockValues->month++;

		if (ClockValues->month > 11)
		{
			ClockValues->month = 0;
			ClockValues->year++;
		}
	}
}

static void ClockValues_AddDays(clockValues_t * ClockValues, u32 days)
{
	while (days--)
	{
		DayPlus(ClockValues);
	}
}

static void ClockValues_AddSeconds(clockValues_t * ClockValues, u32 secondsToAdd)
{
	if (secondsToAdd > 0)
	{
		while (secondsToAdd--)
		{
			ClockValues->seconds++;

			if (ClockValues->seconds > 59)
			{
				ClockValues->seconds = 0;
				ClockValues->minutes++;

				if (ClockValues->minutes > 59)
				{
					ClockValues->minutes = 0;
					ClockValues->hours++;

					if (ClockValues->hours > 23)
					{
						ClockValues->hours = 0;

						DayPlus(ClockValues);
					}
				}
			}
		}
	}
}

void ClockValues_Init(clockValues_t * clockValues)
{
	clockValues->timestamp = 0;
	clockValues->hours = 0;
	clockValues->minutes = 0;
	clockValues->seconds = 0;
	clockValues->day = 0;
	clockValues->dayOfWeek = FIRST_DAY_OF_WEEK;
	clockValues->month = 0;
	clockValues->year = TIMESTAMP_START_YEAR;
}

void ClockValues_Add(clockValues_t * clockValues, u32 seconds)
{
	// Okreœlamy liczbê dni na podstawie sekund
	u32 days = DaysFromSeconds(seconds);

	// A nastêpnie updejtujemy strukturê t¹ liczb¹
	ClockValues_AddDays(clockValues, days);

	// Po dodaniu dni dodajemy godziny, minuty i sekundy
	ClockValues_AddSeconds(clockValues, seconds % SECONDS_PER_DAY); // <=> seconds - days*SECONDS_PER_DAY
}

void ClockValues_Sub(clockValues_t * clockValues, u32 seconds)
{
	if (seconds > 0)
	{
		while (seconds--)
		{
			clockValues->seconds--;
			if (clockValues->seconds < 0)
			{
				clockValues->seconds = 59;

				clockValues->minutes--;
				if (clockValues->minutes < 0)
				{
					clockValues->minutes = 59;

					clockValues->hours--;
					if (clockValues->hours < 0)
					{
						clockValues->hours = 23;

						clockValues->dayOfWeek--;
						if (clockValues->dayOfWeek < 0) clockValues->dayOfWeek = DAYS_OF_WEEK_COUNT - 1;

						clockValues->day--;
						if (clockValues->day < 0)
						{
							clockValues->month--;

							if (clockValues->month < 0)
							{
								clockValues->month = 11;
								clockValues->year--;
							}

							clockValues->day = DaysInMonth(clockValues->month, clockValues->year) - 1; // Minus 1 poniewa¿ dni liczymy od zera
						}
					}
				}
			}
		}
	}
}
