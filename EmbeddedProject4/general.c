#include "general.h"

#include "typedefs.h"
#include "stdlib.h"
#include "string.h"
/*************************************************************************************************/

u16 SetBits(u8 from_included, u8 to_included)
{
	u16 temp = 0;

	for (u8 i=from_included; i<=to_included; i++)
		SetBit(temp, i);

	return temp;
}

/*************************************************************************************************/

u8 GetU8AndMove(u8 * array, u16 * pointer)
{
	u8 temp = ((u8)(*(u8*)(array + *pointer)));
	*pointer += sizeof(u8);

	return temp;
}

u16 GetU16AndMove(u8 * array, u16 * pointer)
{
	u16 temp = ((u16)(*(u16*)(array + *pointer)));
	*pointer += sizeof(u16);

	return temp;
}

u32 GetU32AndMove(u8 * array, u16 * pointer)
{
	u32 temp = ((u32)(*(u32*)(array + *pointer)));
	*pointer += sizeof(u32);

	return temp;
}
#include "debug.h"
char * GetStringAndMove(u8 * array, u16 * pointer, char * buffer, u8 bufferCapacityWithoutZeroChar)
{
	u8 declaredLength = array[*pointer]; // first char is string length
	//Debug("len: %u", declaredLength);
	//u8 i = 0;

	u8 charsToCopy = declaredLength;
	// If declared length is bigger than buffer capacity - copy only chars which can be copied
	if (declaredLength > bufferCapacityWithoutZeroChar) charsToCopy = bufferCapacityWithoutZeroChar; // '-1' for \0 char

	strncpy(buffer, (char*)(array+*pointer+1), charsToCopy);
	buffer[charsToCopy] = 0;
//	while (i<declaredLength)
//		*(buffer++) = array[*pointer+1+i++];
//	*buffer = 0; // Close string

	*pointer += 1 + declaredLength; // 1 for declaredLength (first cell of array)

	return buffer;
}

/*************************************************************************************************/

void LoadU8AndMove(u8 * array, u8 value, u16 * pointer)
{
	LoadU8(array + *pointer, value);
	*pointer += sizeof(u8);
}

void LoadArrayAndMove(u8 * array, u8 * dataToLoad, u16 dataToLoadSize, u16 * pointer)
{
	if (dataToLoadSize > 0)
	{
		memcpy(array + *pointer, dataToLoad, dataToLoadSize);
		*pointer += dataToLoadSize;
	}
}

void LoadStringAndMove(u8 * array, char * text, u16 * pointer)
{
	LoadU8(array + *pointer, (u8)strlen(text));
	memcpy(array + 1 + *pointer, (u8*)text, strlen(text));
	*pointer += 1 + strlen(text);
}

void LoadU16AndMove(u8 * array, u16 value, u16 * pointer)
{
	LoadU16(array + *pointer, value);
	*pointer += sizeof(u16);
}

void LoadU32AndMove(u8 * array, u32 value, u16 * pointer)
{
	LoadU32(array + *pointer, value);
	*pointer += sizeof(u32);
}

void LoadU16AndMove_BigEndian(u8 * array, u16 value, u16 * pointer)
{
	array[*pointer] = (value & 0xFF00) >> 8;
	array[*pointer+1] = (value & 0x00FF);
	*pointer += sizeof(u16);
}

/*************************************************************************************************/

void SetOrResetBit(u32 reg, u8 bitIndex, boolean value)
{
	if (value) reg |= 1 << bitIndex;
	else reg &= 1 << bitIndex;
}

// ex. SetOrReset(&param.value[0], users[selectedUserParamToEditIndex].flags, 0);
void SetOrReset(boolean * value, u32 flags, u8 bitIndex)
{
	if (flags & bitIndex) *value = true;
	else *value = false;
}

/*************************************************************************************************/

u8 NumberOfDigits(u32 number)
{
	u8 i = 1;
	while (number /= 10) i++;

	return i;
}


/*************************************************************************************************/

boolean IsPercent(u32 value)
{
	if ((value>=0) && (value<=100)) return true;

	return false;
}

/*************************************************************************************************/

char DigitToChar(u8 digit)
{
	return digit + 0x30;
}

/*************************************************************************************************/
#include "debug.h"
#include "delay.h"

/*************************************************************************************************/

void ClearBuffer(u8 * buffer, u16 bufferSize)
{
	memset(buffer, 0, bufferSize);
}

/*************************************************************************************************/

char * CharToString(char c)
{
	static char buffer[2];

	buffer[0] = c;
	buffer[1] = 0;

	return buffer;
}


/*************************************************************************************************/

/*************************************************************************************************/

u12 PercentToU12(percent_t percent)
{
	u12 temp = percent * 41;
	if (percent >= 100) temp = 0x0FFF; // Cause 100*41 is 4100 and max value for u12 is 4096

	return temp;
}

/*************************************************************************************************/

u8 DigitOfValue(u16 value, u8 digitIndex)
{
	const u32 dividers[] = { 1, 10, 100, 1000, 10000, 100000 };

	return (value % dividers[digitIndex+1]) / dividers[digitIndex];
}

/*************************************************************************************************/
