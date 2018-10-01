#ifndef FRAME_H_
#define FRAME_H_

/*************************************************************************************************/

#include "typedefs.h"
#include "crc.h"
#include "cycleBuffer.h"
#include "general.h"

/*************************************************************************************************/

typedef enum
{
	frameType_None        = 0,
	frameType_Ping        = 1,
	frameType_Update      = 2,
	frameType_GetValue    = 3,
	frameType_SetValue    = 4,
	frameType_Error       = 5,
	frameType_Pong        = 6,
	frameType_GetAll      = 7,
	frameType_UpdateAll   = 8,
	frameType_PushEnable  = 9,
	frameType_PushDisable = 10,
	frameType_Push        = 11
}
frameType_t;

typedef enum
{
	requestFrameType_Ping = 1,
	requestFrameType_Get,
	requestFrameType_GetAll,
	requestFrameType_Set,
	requestFrameType_PushStateSet,
}
requestFrameType_t;

typedef enum
{
	responseFrameType_Pong = 1,
	responseFrameType_Error,
	responseFrameType_Update,
	responseFrameType_UpdateAll,
	responseFrameType_PushStateUpdate,
}
responseFrameType_t;


/*************************************************************************************************/

#define FRAME_SYNCHRO		((u16)0xAABB) // transmitted as little-endian!

#define FRAME_DATA_CAPACITY 1024

/*************************************************************************************************/


typedef struct //PACKED
{
	u8 type;   // could be type of frameType_t but only for transmitted frames
	u8 dataSize;   // real size of data[]
	u8 data[FRAME_DATA_CAPACITY];   // data buffer
	u8 xor;
	boolean valid;
}
frame_t;

/*************************************************************************************************/

boolean Frame_Parse(frame_t * frame, u8 b);
void Frame_Print(frame_t * frame);
void FrameBufferBuilder_Start(cycleBuffer_t * buffer, frameType_t frameType);
void FrameBufferBuilder_End(cycleBuffer_t * buffer);

/*************************************************************************************************/

#endif /* FRAME_H_ */
