/*
 * debug.h
 *
 *  Created on: Dec 13, 2013
 *      Author: TomB
 */

#ifndef DEBUG_H_
#define DEBUG_H_

/*************************************************************************************************/

#include "typedefs.h"

/*************************************************************************************************/

char debugBuff[256];

/*************************************************************************************************/

#define DEBUG_ENABLE	0


#if (DEBUG_ENABLE==1)
	#define Debug(str,...)   	Debug_Print(true, str, ##__VA_ARGS__)
	#define DebugNN(str,...)   	Debug_Print(false, str, ##__VA_ARGS__)
#else
	#define Debug(str,...)
	#define DebugNN(str,...)
#endif

/*************************************************************************************************/

void Debug_Print(boolean addNewLineAtEnd, const char *fmt, ...);
void DebugArray(u8 * array, u16 arraySize);

#define Debug_PrintFunctionName()	Debug("%s()", __FUNCTION__)
#define DebugChar(var)		Debug("%s: %c", #var, var)
#define DebugString(var)	Debug("%s: %s", #var, var)
#define DebugDec(var)		Debug("%s: %d", #var, var)
#define DebugSigned(var)	Debug("%s: %i", #var, var)
#define DebugHex(var)		Debug("%s: 0x%x", #var, var)
#define DebugBool(var)		Debug("%s: %s", #var, var==true ? "true" : "false")

/*************************************************************************************************/

#endif /* DEBUG_H_ */
