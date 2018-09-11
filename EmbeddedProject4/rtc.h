/*
 * rtc.h
 *
 *  Created on: Nov 26, 2015
 *      Author: tB
 */

#ifndef RTC_H_
#define RTC_H_

/*
 * Zegar ustawiany jest w dwojaki sposób:
 * - za pomoc¹ funkcji Clock_Set() która powinna byæ wywo³ana gdzieœ na poziomie
 *   odbierania parametrów (podczas ustawiania zegara z komputera)
 * - za pomoc¹ silnika logiki który pozwala na dodawanie i odejmowanie sekund
 *
 * Zegar nie posiada swojego silnika. Timestamp inkrementuje siê sam sprzêtowo
 * a przeliczenie na wartoœci odczytywalne dla ludzi nastêpuje tylko na ¿¹danie za
 * pomoc¹ getterów (Clock_GetHours/Minutes/etc).
 *
 *
 */

#include <typedefs.h>
#include <clockvalues.h>


void Clock_Init(void);

void Clock_Set(timestamp_t timestamp);
void Clock_AddSeconds(u32 secondsToAdd);
void Clock_SubtractSeconds(u32 secondsToSubtract);

u8 Clock_GetHours(void);
u8 Clock_GetMinutes(void);
u8 Clock_GetSeconds(void);
u8 Clock_GetDayOfWeek(void);
u8 Clock_GetDay(void);
u8 Clock_GetMonth(void);
u16 Clock_GetYear(void);

#endif /* RTC_H_ */
