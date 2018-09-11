#include "crc.h"

#include "typedefs.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_crc.h"
#include "debug.h"
#include "string.h"

/*************************************************************************************************/

void Crc32_Init(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

	Crc32_Reset();
}

/*************************************************************************************************/

void Crc32_Reset(void)
{
//	Debug("     Crc32_Reset()");

	CRC_ResetDR();
}

/*************************************************************************************************/

u32 Crc32_Add(u32 data)
{
	//Debug("     Crc32_Add(%X)", data);

	CRC->DR = data;

	return (u32)(CRC->DR); // Return the content of the CRC Data Register
}

/*************************************************************************************************/
/*
u32 Crc32Array_Hard(u32 * array, u16 arraySize)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

	CRC_ResetDR();

	u16 i = 0;

		// A loop to compute the CRC of Data Buffer
		for (i = 0; i < arraySize; i++)
		{
			CRC->DR = array[i];
		}

	return (u32)(CRC->DR); // Return the content of the CRC Data Register
}
*/
/*************************************************************************************************/
/*
static u32 Crc32_Soft(u32 initialCrc, u32 inputData)
{
	u8 i = 0;
	u32 crc = 0;


	crc = initialCrc ^ inputData;


		for (i = 0; i < 32; i++)
		{
			if (crc & 0x80000000)
			{
				crc = (crc << 1) ^ 0x04C11DB7;
			}
			else
			{
				crc = (crc << 1);
			}
		}

	return crc;
}
*/
/*************************************************************************************************/
/*
u32 Crc32Array_Soft(u32 * array, u16 arraySize)
{
	u8 i=0;
	u32 crc=0xFFFFFFFF;

	for (i=0; i<arraySize; i++)
		crc = Crc32_Soft(crc, array[i]);

	return crc;
}
*/
/*************************************************************************************************/

/*
 * Always use Crc32Init() before this function call.
 * This function does not clear CRC->DR register.
 */

//u32 CrcOfBuffer(u8 * buffer, u16 start, u16 length)
//{
//	u16 i = start;
//	u32 crc = 0;
//
//	if (start<0) return CRC->DR;
//	if (length<=0) return CRC->DR;
//
//	u16 bytesLeft = start+length;
//
//	while (i<start+length)
//	{
//		u32 b4 = 0;
//
//		bytesLeft = start+length-i;
//
//		if (bytesLeft<4)
//		{
//			u8 temp[4] = { 0,0,0,0 };
//
//			memcpy(temp, buffer+i, bytesLeft);
//
//			b4 = *((u32*)(temp));
//		}
//		else
//		b4 = *((u32*)(buffer+i));
//
//		crc = Crc32_Add(b4);
//		i += 4;
//	}
//
//	return crc;
//}

/*************************************************************************************************/

u32 Crc_OfBuffer(u8 * buffer, u16 start, u16 length)
{
	u16 i = start;
	u32 crc = 0;

	u16 bytesLeft = start+length;

	Crc32_Reset();

	while (i<start+length)
	{
		u32 b4 = 0;

		bytesLeft = start+length-i;

		if (bytesLeft<4)
		{
			u8 temp[4] = { 0,0,0,0 };

			memcpy(temp, buffer+i, bytesLeft);

			b4 = *((u32*)(temp));
		}
		else
		b4 = *((u32*)(buffer+i));

		crc = Crc32_Add(b4);
		i += 4;
	}

	return crc;
}

/*************************************************************************************************/
