/*
 * buzzer.h
 *
 *  Created on: Nov 29, 2015
 *      Author: tB
 */

#ifndef BUZZER_H_
#define BUZZER_H_

/*
 *	Buzer1 a w³aœciwie przetwornik magnetyczny jest pod³¹czony do
 *	pinu A4. Do jego sterowania u¿yty zosta³ DAC (kana³ 1) oraz timer7.
 *
 *
 *
 */

#include <typedefs.h>

void Buzzer1_Init(void);

void Buzzer1_Enable(boolean enable);
void Buzzer1_SetVolume(percent_t volume);
void Buzzer1_SetFrequency(u16 freq);

void Buzzer1_Test(void);

#endif /* BUZZER_H_ */
