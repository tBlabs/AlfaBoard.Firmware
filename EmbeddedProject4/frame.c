/*
 * frame.c
 *
 *  Created on: Mar 21, 2014
 *      Author: TomB
 */

/*************************************************************************************************/

#include "frame.h"

#include "debug.h"
#include "general.h"
#include "crcCalc.h"
#include "string.h"

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
	Synchro_Byte1, // 1 byte
	Synchro_Byte2, // 1 byte
	FrameType, // 1 byte
	DataSize, // 2 bytes
	Data, // 0..FRAME_DATA_SIZE bytes
	Crc // 4 bytes
}
explodeStep = Synchro_Byte1;

/*************************************************************************************************/

//static u8 byteIndex;

//static void BuildWordReset(void)
//{
//	byteIndex=0;
//}

/*************************************************************************************************/
static u8 byteIndex;

void BuildWordClear()
{
	byteIndex=0;
}

static boolean BuildWord(u8 byte, u32 * OUT_buildedWord)
{

	if (byteIndex == 0) *OUT_buildedWord = 0;

	*OUT_buildedWord |= byte << (byteIndex*8);
	byteIndex++;

	if (byteIndex == sizeof(u32)) { byteIndex = 0;  return true; }

	return false;
}

/*************************************************************************************************/

static boolean BuildHalfWord(u8 byte, u16 * OUT_buildedHalfWord)
{
	static u8 byteIndex;

	if (byteIndex == 0) *OUT_buildedHalfWord = 0;

	*OUT_buildedHalfWord |= byte << (byteIndex*8);
	byteIndex++;

	if (byteIndex == sizeof(u16)) { byteIndex = 0; return true; }

	return false;
}

/*************************************************************************************************/

void FrameReset(frame_t * frame)
{
	frame->valid = false;
	frame->crc = 0;
	//Crc32_Reset();
	frame->dataSize = 0;
}

/*************************************************************************************************/


boolean Frame_Parse(frame_t * frame, u8 b)
{
	static u32 computedCrc;
	static u16 dataCounter;

	#if (FRAME_PARSE_DEBUG_ENABLE==1)
		static u16 i;
		FrameParserDebug("%u: <%X>", i++, b);
	#endif


	CrcCalc_Add(b);

	switch (explodeStep)
	{
		case Synchro_Byte1:	if (b==(FRAME_SYNCHRO & 0x00FF)) NextStep();

							break;

		case Synchro_Byte2:	if (b==((FRAME_SYNCHRO & 0xFF00)>>8))
							{
								NextStep();
								FrameReset(frame);
								CrcCalc_Start();
							}
							else GoTo(Synchro_Byte1);

							break;

		case FrameType:		frame->type=b;
							FrameParserDebug("FrameType: %u", frame->type);
							NextStep();

							break;


		case DataSize:		if (BuildHalfWord(b, &frame->dataSize))
							{
								FrameParserDebug("DataSize: %u", frame->dataSize);
								// If frame size is bigger then zero jump to data collecting
								if (frame->dataSize > 0)
								{
									dataCounter = 0;
									NextStep();
								}
								else // If not - jump to CRC calculation
								{

									computedCrc = CrcCalc_End();
									GoTo(Crc);
									BuildWordClear();
								}
							}

							break;

		case Data:			FrameParserDebug("Data (%u/%u): 0x%x", dataCounter, frame->dataSize, b);

							frame->data[dataCounter++] = b;

							if (dataCounter >= frame->dataSize)
							{
								FrameParserDebug("All data collected");
//								if ((frame->dataSize % 4) != 0) // If data count is not dividable by 4
//									computedCrc = Crc32_Add(tempU32);
								computedCrc = CrcCalc_End();
								GoTo(Crc);
								BuildWordClear();
							}


							break;

		case Crc: 			if (BuildWord(b, &frame->crc))
							{
								GoTo(Synchro_Byte1);

								if (computedCrc == frame->crc)
								{
									FrameParserDebug("CRC ok");
									frame->valid = true;
								}
								else
								{
									FrameParserDebug("CRC ERROR: declaredCrc: 0x%x, computedCrc: 0x%X", frame->crc, computedCrc);
									frame->crc = computedCrc;
									frame->valid = false;
								}

								return true;
							}


			break;

		default: GoTo(Synchro_Byte1); break;

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
	Debug("CRC: 0x%x", frame->crc);
	Debug("Valid: %s", frame->valid==true ? "true" : "false");
	Debug("--------------------------------");
}

/*************************************************************************************************/

/*
 * This function loads UART Tx buffer and sends data.
 */

//void Frame_ClearTx(terminal_t * terminal)
//{
//	memset(terminal->TxBuffer, 0, terminal->TxBufferSize);
//	terminal->TxRead = 0;
//	terminal->TxWrite = 0;
//}



//void Frame_Send(terminal_t * terminal, frameType_t type, u8 * data, u16 dataSize)
//{
//	u16 n = 0;
//
//	Frame_ClearTx(terminal);
//
//    // Synchro (little-endian)
//	LoadU16AndMove(terminal->TxBuffer, FRAME_SYNCHRO, &n);
//
//	// Frame Type
//	LoadU8AndMove(terminal->TxBuffer, type, &n);
//
//	// Data Count (little-endian)
//	LoadU16AndMove(terminal->TxBuffer, dataSize, &n);
//
//	// Data
//	if (dataSize > 0)
//		LoadArrayAndMove(terminal->TxBuffer, data, dataSize, &n);
//
//	//DebugArray(terminal->TxBuffer, n);
//	//Debug("CRC: %x", Crc_OfBuffer(terminal->TxBuffer, 2, n-2));
//	// CRC32
//	LoadU32AndMove(terminal->TxBuffer, Crc_OfBuffer(terminal->TxBuffer, 2, n-2), &n);
//
//
//	// ENABLE/RUN TX EMPTY INTERRUPT
//	terminal->TxWrite = n;
//	USART_ITConfig(terminal->usart, USART_IT_TXE, ENABLE);
//}

#include "cycleBuffer.h"

static u16 startPoint, dataCountPoint, dataStartPoint;

void FrameBufferBuilder_Start(cycleBuffer_t * buffer, frameType_t frameType)
{
	startPoint = CycleBuffer_GetCurrentWritePosition(buffer); // For CRC calculation

	// Frame synchro bytes
	CycleBuffer_AddU16(buffer, FRAME_SYNCHRO);

	// Frame type
	CycleBuffer_Add(buffer, frameType);

	// Frame data count
	dataCountPoint = CycleBuffer_GetCurrentWritePosition(buffer); // For data count calculation

	CycleBuffer_AddU16(buffer, 0); // Data count is unknown at this moment..

	dataStartPoint = CycleBuffer_GetCurrentWritePosition(buffer); // For data count calculation
}

void FrameBufferBuilder_End(cycleBuffer_t * buffer)
{
	// Update data count
	u16 thisPoint = CycleBuffer_GetCurrentWritePosition(buffer);
	u16 dataSize = CycleBuffer_DistanceBetweenPoints(buffer, dataStartPoint, thisPoint);
	CycleBuffer_OverrideU16(buffer, dataCountPoint, dataSize);

	crc_t crc = CycleBuffer_Crc(buffer, startPoint+2, thisPoint);
	CycleBuffer_AddU32(buffer, crc);
}

//
//void Frame_Send(frameType_t type, u8 * data, u16 dataSize)
//{
////	u16 start = CycleBuffer_GetCurrentWritePosition(&txBuffer);
////
////    // Synchro
////	CycleBuffer_AddU16(&txBuffer, FRAME_SYNCHRO);
////
////	// Frame Type
////	CycleBuffer_Add(&txBuffer, type);
////
////	// Data Count
////	CycleBuffer_AddU16(&txBuffer, dataSize);
////
////	// Data
////	CycleBuffer_AddArray(&txBuffer, data, dataSize);
////
////	// CRC32
////	u16 end = CycleBuffer_GetCurrentWritePosition(&txBuffer);
////	crc_t crc = CycleBuffer_Crc(&txBuffer, start + sizeof(FRAME_SYNCHRO), end);
////	CycleBuffer_AddU32(&txBuffer, crc);
////
////
////	// SEND
////	Usart2_Send();
//}

/*************************************************************************************************/

