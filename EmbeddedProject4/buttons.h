/*
 * buttons.h
 *
 *  Created on: Jan 17, 2015
 *      Author: tB
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

/*************************************************************************************************/

typedef enum { buttonState_NOT_PRESSED, buttonState_PRESSED } buttonState_t;

/*************************************************************************************************/

void Buttons_Init(void);
buttonState_t Button1_Get(void);
buttonState_t Button2_Get(void);
buttonState_t Button3_Get(void);
buttonState_t Button4_Get(void);

/*************************************************************************************************/

#endif /* BUTTONS_H_ */
