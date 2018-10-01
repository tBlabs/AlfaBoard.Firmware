#include "frame.h"
#include "debug.h"
#include "general.h"
#include "crcCalc.h"
#include "string.h"
#include "cycleBuffer.h"

/*************************************************************************************************/

#define FRAME_PARSE_DEBUG_ENABLE	0


#if (FRAME_PARSE_DEBUG_ENABLE==0)
#define FrameParserDebug(str,...)
#else
#define FrameParserDebug(str,...) Debug(str,##__VA_ARGS__)
#endif

/*************************************************************************************************/

#define GoTo(step)		{ explodeStep = (step); }
#define NextStep()		explodeStep++

enum
{
	Synchro_Byte1,
	// 1 byte
  Synchro_Byte2,
	// 1 byte
  FrameType,
	// 1 byte
  DataSize,
	// 1 byte
  Data,
	// 0..FRAME_DATA_SIZE bytes
  Xor 
}
explodeStep = Synchro_Byte1;

/*************************************************************************************************/
static u8 byteIndex;

void BuildWordClear()
{
	byteIndex = 0;
}

static boolean BuildWord(u8 byte, u32 * OUT_buildedWord)
{

	if (byteIndex == 0) *OUT_buildedWord = 0;

	*OUT_buildedWord |= byte << (byteIndex * 8);
	byteIndex++;

	if (byteIndex == sizeof(u32)) { byteIndex = 0; return true; }

	return false;
}

/*************************************************************************************************/

static boolean BuildHalfWord(u8 byte, u16 * OUT_buildedHalfWord)
{
	static u8 byteIndex;

	if (byteIndex == 0) *OUT_buildedHalfWord = 0;

	*OUT_buildedHalfWord |= byte << (byteIndex * 8);
	byteIndex++;

	if (byteIndex == sizeof(u16)) { byteIndex = 0; return true; }

	return false;
}

/*************************************************************************************************/

void FrameReset(frame_t * frame)
{
	frame->valid = false;
	//	frame->crc = 0;
		frame->xor = 0;
	//Crc32_Reset();
	frame->dataSize = 0;
}

/*************************************************************************************************/

boolean Frame_Parse(frame_t * frame, u8 b)
{
	static u8 dataCounter;
	static u8 xor;
	DebugHex(b);
	if (explodeStep != Xor)
	{
		xor ^= b;
		DebugDec(xor);
	}
	else Debug("xor suspended");
	switch (explodeStep)
	{
	case Synchro_Byte1:	
		if (b == 0xBB) GoTo(Synchro_Byte2);
		break;

	case Synchro_Byte2:	
		if (b == 0xAA)
		{
			NextStep();
			frame->valid = false;
			xor = 0;
			xor ^= 0xBB;
			xor ^= 0xAA;
		}
		else GoTo(Synchro_Byte1);

		break;

	case FrameType:		
		frame->type = b;
		GoTo(DataSize);
		break;

	case DataSize:		
		frame->dataSize = b;
								
		if (frame->dataSize > 0)
		{
			dataCounter = 0;
			GoTo(Data);
		}
		else
		{
			GoTo(Xor);
		}						

		break;

	case Data:		
		frame->data[dataCounter++] = b;

		if (dataCounter >= frame->dataSize)
		{
			GoTo(Xor);
		}

		break;
		
	case Xor:
		GoTo(Synchro_Byte1);
			
		if (xor == b)
		{
			Debug("xor ok");
			return true;
		}
		else
		{
			Debug("xor err", xor, b);
			int dummy = xor;
		}
		
		break;

	default: 
		GoTo(Synchro_Byte1); 
		break;
	} // switch

	return false;
}

/*************************************************************************************************/

void Frame_Print(frame_t * frame)
{
	Debug("--- Frame ----------------------");
	Debug("Type: %u", frame->type);
	Debug("Data count: %u", frame->dataSize);
	DebugArray(frame->data, frame->dataSize);
	//	Debug("CRC: 0x%x", frame->crc);
		Debug("XOR: 0x%x", frame->xor);
	Debug("Valid: %s", frame->valid == true ? "true" : "false");
	Debug("--------------------------------");
}

/*************************************************************************************************/

static u16 startPoint,// dataCountPoint, 
	dataStartPoint;

void FrameBufferBuilder_Start(cycleBuffer_t * buffer, u8 frameType)
{
	startPoint = CycleBuffer_GetCurrentWritePosition(buffer);       // For CRC calculation

	CycleBuffer_Add(buffer, 0xAB);
	CycleBuffer_Add(buffer, frameType);

	dataStartPoint = CycleBuffer_GetCurrentWritePosition(buffer);       // For data count calculation
}

void FrameBufferBuilder_End(cycleBuffer_t * buffer)
{
	// Update data count
	u16 thisPoint = CycleBuffer_GetCurrentWritePosition(buffer);
	//u16 dataSize = CycleBuffer_DistanceBetweenPoints(buffer, dataStartPoint, thisPoint);
	u8 xor = CycleBuffer_Xor(buffer, startPoint, thisPoint);
	CycleBuffer_Add(buffer, xor);
}

/*************************************************************************************************/

