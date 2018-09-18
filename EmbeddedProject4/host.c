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
#include "leds.h"
#include "buttons.h"
#include "params.h"
#include <parser.h>
#include "pins.h"

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

void SendValue(u8 addr, u32 value)
{
	FrameBufferBuilder_Start(&usart2TxCycleBuffer, frameType_Update); // Start frame in Tx buffer
	CycleBuffer_Add(&usart2TxCycleBuffer, addr);
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
	switch (ioAddr)
	{
		case ioAddr_Input1: return Button1_Get();
		case ioAddr_Input2: return Button2_Get();
		case ioAddr_Input3: return Button3_Get();
		case ioAddr_Input4: return Button4_Get();
		case ioAddr_Led1: return Led1_Get();
		case ioAddr_Led2: return Led2_Get();
		case ioAddr_Led3: return Led3_Get();
		case ioAddr_Led4: return Led4_Get();
	}
	
	return 0;
}

boolean PeripheralsManager_SetValueByAddr(ioAddr_t ioAddr, u32 value)
{
	switch (ioAddr)
	{
		case ioAddr_Led1: Led1_Set(value); break;
		case ioAddr_Led2: Led2_Set(value); break;
		case ioAddr_Led3: Led3_Set(value); break;
		case ioAddr_Led4: Led4_Set(value); break;
		default: return false;
	}
	
	return true;
}


void FrameParserSwitch(frameType_t frameType, u8 * data, u16 dataSize)
{
	switch (frameType)
	{
		case frameType_Test:
			SendOk();
			break;

//		case frameType_Config:
//			if (Config_Parse(frame))
//			{
//				SendOk();
//			}
//			else
//			{
//				SendError(error_CONFIG_PARSE_PROBLEM);
//			}
//			break;

//		case frameType_Param:
//			if (frame->dataSize == 4)
//			{
//				u16 paramCode = GetU16(frame->data, 0);
//				u16 paramValue = GetU16(frame->data, 2);
//
//				Parser_ParamReceived(paramCode, paramValue);
//
//				SendOk();
//			}
//			else SendError(error_PARAM_FRAME_PROBLEM);
//			break;
		
		case frameType_GetValue:
			if (dataSize == 1)
			{
				ioAddr_t addr = (ioAddr_t)data[0]; // TODO: validate addr range
				
				u32 value = PeripheralsManager_GetValueByAddr(addr);
				
				SendValue(addr, value);
			}	
			else SendError(error_UNKNOWN_ERROR);
	
		case frameType_SetValue:
			if (dataSize == 5)
			{
				ioAddr_t addr = (ioAddr_t)data[0]; // TODO: validate addr range
				u32 value = GetU32(data, 1);
				
				boolean success = PeripheralsManager_SetValueByAddr(addr, value);
				if (!success) SendError(error_UNKNOWN_ERROR);
		
				SendValue(addr, value);
			}	
			else SendError(error_UNKNOWN_ERROR);
			break;
		
		default: 
			SendError(error_INVALID_FRAME_TYPE);
			break;
	}
}

void HostTask(void)
{
	static u8 b;
	static frame_t frame;

	while (CycleBuffer_GetNewByte(&usart2RxCycleBuffer, &b))
	{
		if (Frame_Parse(&frame, b))
		{
			FrameParserSwitch(frame.type, frame.data, frame.dataSize);
		}
	}
}
