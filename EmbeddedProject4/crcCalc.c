/*
 * crcCalc.c
 *
 *  Created on: Feb 3, 2015
 *      Author: tB
 */

#include "crcCalc.h"

#include "stm32f10x_rcc.h"
#include "debug.h"

void CrcCalc_Start()
{
	//Debug("CrcCalc_Start()");
	crcCalc.tempU32 = 0;
	crcCalc.tempU32byteIndex = 0;
	crcCalc.collectData = true;
	Crc32_Init();
}

void CrcCalc_Add(u8 byte)
{
	if (crcCalc.collectData)
	{
		//Debug("CrcCalc_Compute(0x%x)", byte);

		crcCalc.tempU32 |= byte << (crcCalc.tempU32byteIndex*8);
		crcCalc.tempU32byteIndex++;

		if (crcCalc.tempU32byteIndex == sizeof(crc_t))
		{
			Crc32_Add(crcCalc.tempU32);
			crcCalc.tempU32 = 0;
			crcCalc.tempU32byteIndex = 0;
		}
	}
}

void CrcCalc_AddU32(u32 word)
{
	if (crcCalc.collectData)
	{
		Crc32_Add(word);
	}
}

crc_t CrcCalc_End()
{
	//Debug("CrcCalc_End()");

	crcCalc.collectData = false;

	if (crcCalc.tempU32byteIndex > 0)
	{
		Crc32_Add(crcCalc.tempU32);
	}

	return (u32)(CRC->DR);
}
