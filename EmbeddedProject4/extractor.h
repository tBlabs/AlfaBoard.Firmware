/*
 * extractor.h
 *
 *  Created on: Mar 9, 2015
 *      Author: tB
 */

#ifndef EXTRACTOR_H_
#define EXTRACTOR_H_

/*************************************************************************************************/

#include "typedefs.h"
#include "general.h"

/*************************************************************************************************/

typedef enum
{
	/*  0 */ extractorStatus_STARTED,
	/*  1 */ extractorStatus_NOTHING_TO_PARSE,
	/*  2 */ extractorStatus_NOT_INITIALIZED,
	/*  3 */ extractorStatus_INCOMPLETE,
	/*  4 */ extractorStatus_POINTER_OUT_OF_RANGE,
	/*  5 */ extractorStatus_SUCCESS,
}
extractorStatus_t;

typedef struct PACKED
{
	u16 pointer;
	u8 * data;
	u16 dataCount;
	extractorStatus_t status:7;
	unsigned isInitialized:1;
}
extractor_t;

/*************************************************************************************************/

void Extractor_Init(extractor_t * extractor, u8 * data, u16 dataCount);
boolean Extractor_GetU8(extractor_t * extractor, u8 * OUT_u8);
boolean Extractor_GetU16(extractor_t * extractor, u16 * OUT_u16);
boolean Extractor_GetU32(extractor_t * extractor, u32 * OUT_u32);
boolean Extractor_IsWorking(extractor_t * extractor);
extractorStatus_t Extractor_Status(extractor_t * extractor);

/*************************************************************************************************/

#endif /* EXTRACTOR_H_ */
