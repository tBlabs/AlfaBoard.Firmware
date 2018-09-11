
/*	Usage:

	Init();
	while(IsWorking())
	{
		GetU16();
		...
		GetText();
	}
	if (Status()==OK) ...
*/

/*************************************************************************************************/

#include "extractor.h"

#include "typedefs.h"
#include "stddef.h"
#include "general.h"

/*************************************************************************************************/

void Extractor_Init(extractor_t * extractor, u8 * data, u16 dataCount)
{
	if ((data != NULL) && (dataCount > 0))
	{
		extractor->pointer = 0;
		extractor->data = data;
		extractor->dataCount = dataCount;
		extractor->status = extractorStatus_STARTED;
		extractor->isInitialized = true;
	}
	else extractor->status = extractorStatus_NOTHING_TO_PARSE;
}

/*************************************************************************************************/

boolean Extractor_GetU8(extractor_t * extractor, u8 * OUT_u8)
{
	if (extractor->isInitialized == false) return false;
	if (extractor->data == NULL) return false;

	if ((extractor->pointer + sizeof(u8)) <= extractor->dataCount)
	{
		*OUT_u8 = GetU8AndMove(extractor->data, &extractor->pointer);
		return true;
	}
	else
	{
		extractor->status = extractorStatus_POINTER_OUT_OF_RANGE;
		return false;
	}
}

/*************************************************************************************************/

boolean Extractor_GetU16(extractor_t * extractor, u16 * OUT_u16)
{
	if (extractor->isInitialized == false) return false;
	if (extractor->data == NULL) return false;

	if ((extractor->pointer + sizeof(u16)) <= extractor->dataCount)
	{
		*OUT_u16 = GetU16AndMove(extractor->data, &extractor->pointer);
		return true;
	}
	else
	{
		extractor->status = extractorStatus_POINTER_OUT_OF_RANGE;
		return false;
	}
}

/*************************************************************************************************/

boolean Extractor_GetU32(extractor_t * extractor, u32 * OUT_u32)
{
	if (extractor->isInitialized == false) return false;
	if (extractor->data == NULL) return false;

	if ((extractor->pointer + sizeof(u32)) <= extractor->dataCount)
	{
		*OUT_u32 = GetU32AndMove(extractor->data, &extractor->pointer);
		return true;
	}
	else
	{
		extractor->status = extractorStatus_POINTER_OUT_OF_RANGE;
		return false;
	}
}

/*************************************************************************************************/

boolean Extractor_IsWorking(extractor_t * extractor)
{
	if ((extractor->status == extractorStatus_STARTED) && (extractor->pointer<extractor->dataCount)) return true;
	else return false;
}

/*************************************************************************************************/

extractorStatus_t Extractor_Status(extractor_t * extractor)
{
	if ((extractor->status == extractorStatus_STARTED) && (extractor->pointer==extractor->dataCount)) return extractorStatus_SUCCESS;
	else
		return extractor->status;
}

/*************************************************************************************************/

