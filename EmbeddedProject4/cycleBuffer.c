/*
 * cycleBuffer.c
 *
 *  Created on: Jan 20, 2015
 *      Author: tB
 */

#include "cycleBuffer.h"

#include "crcCalc.h"
#include "string.h"

/*
 * Ex.
 * u8 usart2_txBuffer[1024];
 * cycleBuffer_t txBuffer;
 * CycleBuffer_Init(&txBuffer, usart2_txBuffer, sizeof(usart2_txBuffer));
 *
 */
void CycleBuffer_Init(cycleBuffer_t * cycleBuffer, u8 * buffer, u16 bufferSize)
{
	cycleBuffer->data = buffer;
	cycleBuffer->size = bufferSize;
}

void CycleBuffer_Add(cycleBuffer_t * cycleBuffer, u8 b)
{
	cycleBuffer->data[cycleBuffer->write++] = b;
	cycleBuffer->write %= cycleBuffer->size;
}

void CycleBuffer_AddU16(cycleBuffer_t * cycleBuffer, u16 halfWord)
{
	CycleBuffer_Add(cycleBuffer, halfWord & 0x00FF);
	CycleBuffer_Add(cycleBuffer, (halfWord & 0xFF00) >> 8);
}

void CycleBuffer_AddU32(cycleBuffer_t * cycleBuffer, u32 word)
{
	CycleBuffer_Add(cycleBuffer,  word & 0x000000FF);
	CycleBuffer_Add(cycleBuffer, (word & 0x0000FF00) >> 8);
	CycleBuffer_Add(cycleBuffer, (word & 0x00FF0000) >> 16);
	CycleBuffer_Add(cycleBuffer, (word & 0xFF000000) >> 24);
}

void CycleBuffer_AddArray(cycleBuffer_t * cycleBuffer, u8 * data, u16 dataCount)
{
	for (u16 i=0; i<dataCount; i++)
		CycleBuffer_Add(cycleBuffer, data[i]);
}

void CycleBuffer_AddString(cycleBuffer_t * cycleBuffer, char * string)
{
	CycleBuffer_Add(cycleBuffer, strlen(string));
	CycleBuffer_AddArray(cycleBuffer, (u8*)string, strlen(string));
}

void CycleBuffer_OverrideByte(cycleBuffer_t * cycleBuffer, u16 position, u8 b)
{
	cycleBuffer->data[position] = b;
}

void CycleBuffer_OverrideU16(cycleBuffer_t * cycleBuffer, u16 position, u16 halfWord)
{
	CycleBuffer_OverrideByte(cycleBuffer, position, halfWord & 0x00FF);
	position += 1;
	position %= cycleBuffer->size;
	CycleBuffer_OverrideByte(cycleBuffer, position, (halfWord & 0xFF00) >> 8);
}

u16 CycleBuffer_GetCurrentWritePosition(cycleBuffer_t * cycleBuffer)
{
	return cycleBuffer->write;
}

u8 CycleBuffer_GetByte(cycleBuffer_t * cycleBuffer)
{
	u8 temp = cycleBuffer->data[cycleBuffer->read++];
	cycleBuffer->read %= cycleBuffer->size;
	return temp;
}

boolean CycleBuffer_IsNewByte(cycleBuffer_t * cycleBuffer)
{
	if (cycleBuffer->write != cycleBuffer->read) return true;
	else return false;
}

boolean CycleBuffer_GetNewByte(cycleBuffer_t * cycleBuffer, u8 * newByte)
{
	if (CycleBuffer_IsNewByte(cycleBuffer))
	{
		*newByte = CycleBuffer_GetByte(cycleBuffer);
		return true;
	}
	else return false;
}

u16 CycleBuffer_DistanceBetweenPoints(cycleBuffer_t * cycleBuffer, u16 start, u16 end)
{
	if (end != start)
		return start < end ? end - start : cycleBuffer->size - start + end;
	else return 0;
}



crc_t CycleBuffer_Crc(cycleBuffer_t * cycleBuffer, u16 start, u16 end)
{
	CrcCalc_Start();
	u16 p = start;

	while (p!=end)
	{
		CrcCalc_Add(cycleBuffer->data[p++]);
		p %= cycleBuffer->size;
	}

	return CrcCalc_End();
}

u8 CycleBuffer_Xor(cycleBuffer_t * cycleBuffer, u16 start, u16 end)
{
	u8 xor = 0;
	u16 p = start;

	while (p!=end)
	{
		xor ^= cycleBuffer->data[p++];
		p %= cycleBuffer->size;
	}

	return xor;
}
