/*
 * host.c
 *
 *  Created on: Jan 11, 2016
 *      Author: tB
 */

#include "host.h"

#include <frame.h>
#include <usart2.h>
#include <typedefs.h>
#include "error.h"
#include "global.h"
#include "params.h"
#include <parser.h>


void SendOk(void)
{
	FrameBufferBuilder_Start(&usart2TxCycleBuffer, frameType_Ok); // Start frame in Tx buffer
	FrameBufferBuilder_End(&usart2TxCycleBuffer); // Recalculate frame size, crc, etc.
	Usart2_EnableTxInterrupt(); // Send data from usart2RxCycleBuffer
}

void SendError(error_t errorCode)
{
	FrameBufferBuilder_Start(&usart2TxCycleBuffer, frameType_Error); // Start frame in Tx buffer
	CycleBuffer_Add(&usart2TxCycleBuffer, (u8)errorCode);
	FrameBufferBuilder_End(&usart2TxCycleBuffer); // Recalculate frame size, crc, etc.
	Usart2_EnableTxInterrupt(); // Send data from usart2RxCycleBuffer
}

void SendValue(u32 value)
{
	FrameBufferBuilder_Start(&usart2TxCycleBuffer, frameType_Error); // Start frame in Tx buffer
	CycleBuffer_AddU32(&usart2TxCycleBuffer, value);
	FrameBufferBuilder_End(&usart2TxCycleBuffer); // Recalculate frame size, crc, etc.
	Usart2_EnableTxInterrupt(); // Send data from usart2RxCycleBuffer
}

typedef enum 
{
	ioAddr_Input1,
	ioAddr_Input2,
	ioAddr_Input3,
	ioAddr_Input4,
	ioAddr_Led1,
	ioAddr_Led2,
	ioAddr_Led3,
	ioAddr_Led4,
}
ioAddr_t;

u32 PeripheralsManager_GetValueByAddr(ioAddr_t ioAddr)
{
//	switch (ioAddr)
//	{
//		case ioAddr_Input1: return Led1_GetValue();
//	}
//	
	return 0;
}


void FrameControl(frame_t * frame)
{
	switch (frame->type)
	{
		case frameType_Test:
			SendOk();
			break;

		case frameType_Config:
			if (Config_Parse(frame))
			{
				SendOk();
			}
			else
			{
				SendError(error_CONFIG_PARSE_PROBLEM);
			}
			break;

		case frameType_Param:
			if (frame->dataSize == 4)
			{
				u16 paramCode = GetU16(frame->data, 0);
				u16 paramValue = GetU16(frame->data, 2);

				Parser_ParamReceived(paramCode, paramValue);

				SendOk();
			}
			else SendError(error_PARAM_FRAME_PROBLEM);
			break;
		
		case frameType_GetValue:
			if (frame->dataSize == 1)
			{
				ioAddr_t addr = (ioAddr_t)frame->data[0]; // TODO: validate addr range
				u32 value = PeripheralsManager_GetValueByAddr(addr);
				SendValue(value);
			}	
			else SendError(error_UNHANDLED_ERROR);
			break;
	}
}

void HostTask(void)
{
	static u8 b;
	static frame_t receivedFrame;

	while (CycleBuffer_GetNewByte(&usart2RxCycleBuffer, &b))
	{
		if (Frame_Parse(&receivedFrame, b))
		{
			FrameControl(&receivedFrame);
		}
	}
}
