/*
 * text.h
 *
 *  Created on: Mar 15, 2015
 *      Author: tB
 */

#ifndef TEXT_H_
#define TEXT_H_

/*************************************************************************************************/

#include "typedefs.h"
#include "stdarg.h"

/*************************************************************************************************/

typedef struct
{
	u8 * data;
	u16 dataCount;
}
array_t;

/*************************************************************************************************/

array_t Array(u8 * data, u16 dataCount);
u16 _String_Format(char * buf, const char * fmt, va_list va);
void str_format(char * buf, const char * fmt, ...);
#define String_Format(buf,fmt,...) str_format((buf),(fmt), ##__VA_ARGS__)

/*************************************************************************************************/

#endif /* TEXT_H_ */
