#ifndef _GENERAL_H_
#define _GENERAL_H_



#include "typedefs.h"


#define UNUSED __attribute__((unused))
#define PACKED __attribute__((__packed__))

#define SizeOfArray(array)	(sizeof(array)/sizeof(array[0]))

#define SetBit(reg,bitIndex)	((reg)|=(1<<(bitIndex)))
#define ResetBit(reg,bitIndex)	((reg)&=(~(1<<(bitIndex))))
#define ToggleBit(reg,bitIndex)	((reg)^=(1<<(bitIndex)))
#define IsBitSet(reg, bitIndex) (((reg) & (1<<(bitIndex)))?true:false)
#define IsBitReset(reg, bitIndex) (((reg) & (1<<(bitIndex)))?false:true)


u16 SetBits(u8 from, u8 to);

#define OFFSET(var)		((u32)&var) // get address of value
#define OFFSETOF(type, field)    ((unsigned long) &(((type *) 0)->field))


u8 GetU8AndMove(u8 * array, u16 * pointer);
u16 GetU16AndMove(u8 * array, u16 * pointer);
u32 GetU32AndMove(u8 * array, u16 * pointer);
char * GetStringAndMove(u8 * array, u16 * pointer, char * buffer, u8 bufferCapacityWithZeroChar);

/*
 * TEST ROUTINE:
 *
 * 	u8 temp[10];
	u16 n=0;
	LoadU16AndMove(temp, 0x1234, &n);
	DebugArray(temp, 10);

	Will return:
	Array of 10 bytes: <34><12><00>...
 */
#define LoadU8(array, value)	(*(u8*)(array)=(value)) // little-endian
#define LoadU16(array, value)	(*(u16*)(array)=(value)) // little-endian
#define LoadU32(array, value)	(*(u32*)(array)=(value)) // little-endian
void LoadU8AndMove(u8 * array, u8 value, u16 * pointer); // little-endian
void LoadArrayAndMove(u8 * array, u8 * dataToLoad, u16 dataToLoadSize, u16 * pointer);
void LoadStringAndMove(u8 * array, char * text, u16 * pointer);
void LoadU16AndMove(u8 * array, u16 value, u16 * pointer); // little-endian
void LoadU32AndMove(u8 * array, u32 value, u16 * pointer);
void LoadU16AndMove_BigEndian(u8 * array, u16 value, u16 * pointer); // big-endian

#define GetU16(array, startAt)	((u16)(*(u16*)(array+startAt)))
#define GetU32(array, startAt)	((u32)(*(u32*)(array+startAt)))

void SetOrResetBit(u32 reg, u8 bitIndex, boolean value);
void SetOrReset(boolean * value, u32 flags, u8 bitIndex);

u8 NumberOfDigits(u32 number);

boolean IsPercent(u32 value);

char DigitToChar(u8 digit);


char * CharToString(char c);

void ClearBuffer(u8 * buffer, u16 bufferSize);

u12 PercentToU12(percent_t percent);

u8 DigitOfValue(u16 value, u8 digitIndex);

#endif /* _GENERAL_H_ */
