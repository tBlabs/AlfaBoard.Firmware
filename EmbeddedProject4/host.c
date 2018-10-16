#include "host.h"
#include <frame.h>
#include <usart2.h>
#include <typedefs.h>
#include <string.h>
#include "error.h"
#include "global.h"
#include "leds.h"
#include "buttons.h"
#include "params.h"
#include <parser.h>
#include "pins.h"
#include "timeout.h"
#include "leds.h"
#include "debug.h"
#include "pwms.h"
#include "adc.h"
#include "temperature_sensor.h"
#include "displays.h"
#include "buzzer.h"
#include "dac.h"
#include "rtc.h"


#define SENSORS_COUNT	8

void SendPong(void)
{
	FrameBufferBuilder_Start(&usart2TxCycleBuffer, responseFrameType_Pong);          // Start frame in Tx buffer
	FrameBufferBuilder_End(&usart2TxCycleBuffer);          // Recalculate frame size, crc, etc.
	Usart2_EnableTxInterrupt();          // Send data from usart2RxCycleBuffer
}

void SendError(error_t errorCode)
{
	FrameBufferBuilder_Start(&usart2TxCycleBuffer, responseFrameType_Error);          // Start frame in Tx buffer
	CycleBuffer_Add(&usart2TxCycleBuffer, (u8)errorCode);
	FrameBufferBuilder_End(&usart2TxCycleBuffer);          // Recalculate frame size, crc, etc.
	Usart2_EnableTxInterrupt();          // Send data from usart2RxCycleBuffer
}

void SendPushState(boolean state)
{
	FrameBufferBuilder_Start(&usart2TxCycleBuffer, responseFrameType_PushStateUpdate);          // Start frame in Tx buffer
	CycleBuffer_Add(&usart2TxCycleBuffer, (u8)state);
	FrameBufferBuilder_End(&usart2TxCycleBuffer);          // Recalculate frame size, crc, etc.
	Usart2_EnableTxInterrupt();          // Send data from usart2RxCycleBuffer
}

void SendValue(u8 addr, u32 value)
{
	FrameBufferBuilder_Start(&usart2TxCycleBuffer, responseFrameType_Update);          // Start frame in Tx buffer
	CycleBuffer_Add(&usart2TxCycleBuffer, addr);
	CycleBuffer_AddU32(&usart2TxCycleBuffer, value);
	FrameBufferBuilder_End(&usart2TxCycleBuffer);          // Recalculate frame size, crc, etc.
	Usart2_EnableTxInterrupt();          // Send data from usart2RxCycleBuffer
}

void SendValues(u32 * values)
{
	FrameBufferBuilder_Start(&usart2TxCycleBuffer, responseFrameType_UpdateAll);         // Start frame in Tx buffer
	for(u8 i = 0 ; i < SENSORS_COUNT ; i++)
		CycleBuffer_AddU32(&usart2TxCycleBuffer, values[i]);
	FrameBufferBuilder_End(&usart2TxCycleBuffer);         // Recalculate frame size, crc, etc.
	Usart2_EnableTxInterrupt();         // Send data from usart2RxCycleBuffer
}



typedef enum 
{
	ioAddr_Input1, // 0
	ioAddr_Input2,
	ioAddr_Input3,
	ioAddr_Input4,
	ioAddr_Adc1,
	ioAddr_Adc2,
	ioAddr_Temper1,
	ioAddr_Rtc,	
	ioAddr_RtcSet, // 8
	ioAddr_Led1,
	ioAddr_Led2,
	ioAddr_Led3,
	ioAddr_Led4,
	ioAddr_Pwm1,
	ioAddr_Pwm2,
	ioAddr_Pwm3,
	ioAddr_Pwm4, 
	ioAddr_Display1,
	ioAddr_Display1Dot,
	ioAddr_Display2,
	ioAddr_Display2Dot,
	ioAddr_Display3,
	ioAddr_Display3Dot,
	ioAddr_Display4,
	ioAddr_Display4Dot,
	ioAddr_Buzzer1Volume,
	ioAddr_Buzzer1Freq,
	ioAddr_Dac1Value
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
		case ioAddr_Adc1: return Adc1_Value();
		case ioAddr_Adc2: return Adc2_Value();
		case ioAddr_Temper1: return TemperatureSensor_GetTemperature(); break;
		case ioAddr_Rtc: return Clock_Get(); break;
		
		default: return 0;
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
	case ioAddr_Pwm1: Pwm1_Set(value); break;
	case ioAddr_Pwm2: Pwm2_Set(value); break;
	case ioAddr_Pwm3: Pwm3_Set(value); break;
	case ioAddr_Pwm4: Pwm4_Set(value); break;
	case ioAddr_Display1: Display1_Set(value); break;
	case ioAddr_Display1Dot: Display1Dot_Set(value); break;
	case ioAddr_Display2: Display2_Set(value); break;
	case ioAddr_Display2Dot: Display2Dot_Set(value); break;
	case ioAddr_Display3: Display3_Set(value); break;
	case ioAddr_Display3Dot: Display3Dot_Set(value); break;
	case ioAddr_Display4: Display4_Set(value); break;
	case ioAddr_Display4Dot: Display4Dot_Set(value); break;
	case ioAddr_Buzzer1Volume: Buzzer1_SetVolume(value); break;
	case ioAddr_Buzzer1Freq: Buzzer1_SetFrequency(value); break;
	case ioAddr_Dac1Value: DAC1_Value(value); break;
	case ioAddr_RtcSet: Clock_Set(value); break;
	default: return false;
	}
	
	return true;
}

void ReadAllSensors(u32 * values)
{
	for (u8 i = 0; i < SENSORS_COUNT; i++)
	{
		values[i] = PeripheralsManager_GetValueByAddr(i);
	}
}

boolean push = false;
u8 scanInterval = 20; // ms

void ReadAndSendAllValues()
{
	u32 values[SENSORS_COUNT];
	ReadAllSensors(values);
	SendValues(values);
}

void FrameParserSwitch(requestFrameType_t frameType, u8 * data, u16 dataSize)
{
	switch (frameType)
	{
	case requestFrameType_Ping:
		SendPong();
		break;
		
	case requestFrameType_PushStateSet:
		if (dataSize != 2)
		{
			SendError(error_INVALID_FRAME_SIZE);
			break;
		}
		push = data[0];
		scanInterval = data[1];
		SendPushState(push);		
		break;
		
	case requestFrameType_GetAll:
		ReadAndSendAllValues();
		break;

	case requestFrameType_Get:
		if (dataSize == 1)
		{
			ioAddr_t addr = (ioAddr_t)data[0];          // TODO: validate addr range
				
			u32 value = PeripheralsManager_GetValueByAddr(addr);
				
			SendValue(addr, value);
		}	
		else SendError(error_INVALID_FRAME_SIZE);
		break;
	
	case requestFrameType_Set:
		if (dataSize == 5)
		{
			ioAddr_t addr = (ioAddr_t)data[0];          // TODO: validate addr range
			u32 value = GetU32(data, 1);
				
			boolean success = PeripheralsManager_SetValueByAddr(addr, value);
			if (success)
			{
				SendValue(addr, value);
			}
			else SendError(error_ARG_OUT_OF_RANGE);
		}	
		else SendError(error_INVALID_FRAME_SIZE);
		break;
		
	default: 
		SendError(error_INVALID_FRAME_TYPE);
		break;
	}
}

timeout_t pushTimekeeper;
u32 oldValues[SENSORS_COUNT];


void HostTask(void)
{
	static u8 b;
	static frame_t frame;
	
	if (push)
	{
		if (Tick(&pushTimekeeper, scanInterval))
		{
			u32 values[SENSORS_COUNT];
			ReadAllSensors(values);
			int areEqual = memcmp(values, oldValues, sizeof(values));
			if (areEqual != 0)
			{
				memcpy(oldValues, values, sizeof(values));
				SendValues(values);
			}
		}
	}

	while (CycleBuffer_GetNewByte(&usart2RxCycleBuffer, &b))
	{
		if (Frame_Parse(&frame, b))
		{
			FrameParserSwitch(frame.type, frame.data, frame.dataSize);
		}
	}
}
