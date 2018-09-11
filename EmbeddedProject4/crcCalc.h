/*
 * crcCalc.h
 *
 *  Created on: Feb 3, 2015
 *      Author: tB
 */

#ifndef CRCCALC_H_
#define CRCCALC_H_



#include "crc.h"

struct PACKED
{
	u32 tempU32;
	u8 tempU32byteIndex :3;
	unsigned collectData :1;
}
crcCalc;


void CrcCalc_Start();
void CrcCalc_Add(u8 byte);
void CrcCalc_AddU32(u32 word);
crc_t CrcCalc_End();



#endif /* CRCCALC_H_ */
