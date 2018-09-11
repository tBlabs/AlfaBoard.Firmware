/*
 * debug.c
 *
 *  Created on: Apr 16, 2014
 *      Author: TomB
 */

/*************************************************************************************************/

#include "debug.h"
#include "stdarg.h"
#include "string.h"
#include "usart2.h"
#include "text.h"

/*************************************************************************************************/

void Debug_Print(boolean addNewLineAtEnd, const char *fmt, ...)
{
	va_list list;
	va_start(list, fmt);
	_String_Format((char *)debugBuff, fmt, list);
	va_end(list);
	if (addNewLineAtEnd)
		strcat(debugBuff, "\n");
	Usart2_SendString(debugBuff);
}

/*************************************************************************************************/

void DebugArray(u8 * array, u16 arraySize)
{
	#if (DEBUG_ENABLE==1)
		if (arraySize > 0)
		{
			DebugNN("Array of %u bytes: ", arraySize);
			for (u16 i=0; i<arraySize; i++)
				DebugNN("<%x>", array[i]);
			Usart2_SendChar('\n');
		}
		else Usart2_SendString("Array is empty");
	#endif
}


/*************************************************************************************************/


