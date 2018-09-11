/*
 * global.c
 *
 *  Created on: Feb 14, 2015
 *      Author: tB
 */

#include "global.h"

u8 usart2TxData[1200];
u8 usart2RxData[1200];

cycleBuffer_t usart2TxCycleBuffer = CycleBuffer_InitStructure(usart2TxData);
cycleBuffer_t usart2RxCycleBuffer = CycleBuffer_InitStructure(usart2TxData);
