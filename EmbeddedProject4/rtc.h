/*
 * rtc.h
 *
 *  Created on: Nov 26, 2015
 *      Author: tB
 */

#ifndef RTC_H_
#define RTC_H_

/*
 * Zegar ustawiany jest w dwojaki spos�b:
 * - za pomoc� funkcji Clock_Set() kt�ra powinna by� wywo�ana gdzie� na poziomie
 *   odbierania parametr�w (podczas ustawiania zegara z komputera)
 * - za pomoc� silnika logiki kt�ry pozwala na dodawanie i odejmowanie sekund
 *
 * Zegar nie posiada swojego silnika. Timestamp inkrementuje si� sam sprz�towo
 * a przeliczenie na warto�ci odczytywalne dla ludzi nast�puje tylko na ��danie za
 * pomoc� getter�w (Clock_GetHours/Minutes/etc).
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
