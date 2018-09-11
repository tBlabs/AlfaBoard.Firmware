/*
 * crc.h
 *
 *  Created on: Feb 20, 2014
 *      Author: TomB
 */

#ifndef CRC_H_
#define CRC_H_

#include "typedefs.h"

/*************************************************************************************************/
typedef u32 crc_t;

void Crc32_Init(void); // Hardware
void Crc32_Reset(void);
u32 Crc32_Add(u32 data); // Hardware
//u32 Crc32Array_Hard(u32 * array, u16 arraySize); // Hardware
//u32 Crc32Array_Soft(u32 * array, u16 arraySize); // Software
//u32 CrcOfBuffer(u8 * buffer, u16 start, u16 length); // Hardware (uses CRC32())
u32 Crc_OfBuffer(u8 * buffer, u16 start, u16 length);

/*************************************************************************************************/

#endif /* CRC_H_ */
