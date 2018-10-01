/*
 * cycleBuffer.h
 *
 *  Created on: Feb 14, 2015
 *      Author: tB
 */

#ifndef CYCLEBUFFER_H_
#define CYCLEBUFFER_H_

/*************************************************************************************************/

#include "typedefs.h"
#include "crc.h"

/*************************************************************************************************/

typedef struct
{
	u8 * data;
	u16 size;
	volatile u16 write;
	volatile u16 read;
}
cycleBuffer_t;

/*************************************************************************************************/

// Inits
#define CycleBuffer_InitStructure(dataBuffer)	{ dataBuffer, sizeof(dataBuffer), 0, 0 }
void CycleBuffer_Init(cycleBuffer_t * cycleBuffer, u8 * buffer, u16 bufferSize);

// Adds
void CycleBuffer_Add(cycleBuffer_t * cycleBuffer, u8 b);
void CycleBuffer_AddU16(cycleBuffer_t * cycleBuffer, u16 halfWrord);
void CycleBuffer_AddU32(cycleBuffer_t * cycleBuffer, u32 word);
void CycleBuffer_AddArray(cycleBuffer_t * cycleBuffer, u8 * data, u16 dataCount);
void CycleBuffer_AddString(cycleBuffer_t * cycleBuffer, char * string);

// Overrides
void CycleBuffer_OverrideByte(cycleBuffer_t * cycleBuffer, u16 position, u8 b);
void CycleBuffer_OverrideU16(cycleBuffer_t * cycleBuffer, u16 position, u16 halfWord);

// Gets
u8 CycleBuffer_GetByte(cycleBuffer_t * cycleBuffer);
boolean CycleBuffer_IsNewByte(cycleBuffer_t * cycleBuffer);
boolean CycleBuffer_GetNewByte(cycleBuffer_t * cycleBuffer, u8 * newByte);

// Utils
u16 CycleBuffer_GetCurrentWritePosition(cycleBuffer_t * cycleBuffer);
u16 CycleBuffer_DistanceBetweenPoints(cycleBuffer_t * cycleBuffer, u16 start, u16 end);

// Crc32
crc_t CycleBuffer_Crc(cycleBuffer_t * cycleBuffer, u16 start, u16 end);

// Xor
u8 CycleBuffer_Xor(cycleBuffer_t * cycleBuffer, u16 start, u16 end);

/*************************************************************************************************/

#endif /* CYCLEBUFFER_H_ */
