/*
 * DISPLAYS.H
 *
 *  Created on: Feb 26, 2015
 *      Author: tB
 */

#ifndef DISPLAYS_H_
#define DISPLAYS_H_

/*************************************************************************************************/

#include "typedefs.h"
#include "display.h"

/*************************************************************************************************/

void Displays_Init(void);
void Display1_Set(u16 value);
void Display2_Set(u16 value);
void Display3_Set(u16 value);
void Display4_Set(u16 value);
void Display1Dot_Set(u16 dot);
void Display2Dot_Set(u16 dot);
void Display3Dot_Set(u16 dot);
void Display4Dot_Set(u16 dot);


/*** If DISPLAYS_DEBUG_ENABLE==1 *****************************************************************/

void Displays_Test(void);

/*************************************************************************************************/

#endif /* DISPLAYS_H_ */
