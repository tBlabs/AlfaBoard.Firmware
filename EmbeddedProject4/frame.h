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
    frameType_None,
    frameType_Message, // text message from device
    frameType_Ok, // after: _Ok, _LogicMap, _Hold, _Run
    frameType_Error,
    frameType_Test, // connection test
    frameType_Config,
    frameType_Param, // for virtual parser (one of physical devices)
	frameType_GetValue,
	frameType_SetValue,
	frameType_Update,
}
frameType_t;

/*************************************************************************************************/

#define FRAME_SYNCHRO		((u16)0xAABB) // transmitted as little-endian!

#define FRAME_DATA_CAPACITY 1024

/*************************************************************************************************/


typedef struct PACKED
{
	 u8 type; // could be type of frameType_t but only for transmitted frames
	 u16 dataSize; // real size of data[]
	 u8 data[FRAME_DATA_CAPACITY]; // data buffer
	 crc_t crc;
	 unsigned valid :1;
}
frame_t;

/*************************************************************************************************/

boolean Frame_Parse(frame_t * frame, u8 b);
void Frame_Print(frame_t * frame);
void FrameBufferBuilder_Start(cycleBuffer_t * buffer, frameType_t frameType);
void FrameBufferBuilder_End(cycleBuffer_t * buffer);

/*************************************************************************************************/

#endif /* FRAME_H_ */
