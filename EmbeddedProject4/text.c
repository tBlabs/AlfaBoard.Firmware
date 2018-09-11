/*
 * printf.c
 *
 *  Created on: Mar 9, 2015
 *      Author: tB
 */

/*************************************************************************************************/

#include "text.h"

#include "typedefs.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/*************************************************************************************************/

void itoa(char **buf, unsigned int d, int base)
{
	int div = 1;
	while (d/div >= base)
		div *= base;

	// ADD LEADING '0' FOR HEX VALUES SMALLER THEN 0x0F (PREVENT DISPLAYING 0xB, INSTEAD: 0x0B FOR BETTER LOOK)
	if (base==16)
	{
		if (d<=0x0F) *((*buf)++) = '0';
	}

	while (div != 0)
	{
		int num = d/div;
		d = d%div;
		div /= base;
		if (num > 9)
			*((*buf)++) = (num-10) + 'A';
		else
			*((*buf)++) = num + '0';
	}
}

/*************************************************************************************************/

void ltoa(char **buf, unsigned long d, int base) // by tB
{
	unsigned long div = 1;
	while (d/div >= base)
		div *= base;

	// ADD LEADING '0' FOR HEX VALUES SMALLER THEN 0x0F (PREVENT DISPLAYING 0xB, INSTEAD: 0x0B FOR BETTER LOOK)
	if (base==16)
	{
		if (d<=0x0F) *((*buf)++) = '0';
	}

	while (div != 0)
	{
		unsigned long num = d/div;
		d = d%div;
		div /= base;
		if (num > 9)
			*((*buf)++) = (num-10) + 'A';
		else
			*((*buf)++) = num + '0';
	}
}

/*************************************************************************************************/

/*
 * Pseudo-constructor for array-type objects :)
 * Usage:
 * 		u8 arr[] = "123";
 * 		String_Format(buf, "array: %h", Array(arr, sizeof(arr)));
 * Will print:
 * 		"array: [0x31,0x32,0x33,0x00]"
 */
array_t Array(u8 * data, u16 dataCount)
{
	array_t array;
	array.data = data;
	array.dataCount = dataCount;
	return array;
}

/*************************************************************************************************/
// String_Format(buffer, "%d", value)
// String_AddFormat(buffer, "%d", value)

void str_format(char * buf, const char * fmt, ...)
{
	va_list list;
	va_start(list, fmt);
	_String_Format((char *)buf, fmt, list);
	va_end(list);
}

u16 _String_Format(char * buf, const char * fmt, va_list va)
{
	char *start_buf = buf;

	while(*fmt)
	{
		/* Character needs formating? */
		if (*fmt == '%')
		{
			switch (*(++fmt))
			{
				case 'h': // array_t
					{
						array_t array = va_arg(va, array_t);

						*buf++ = '[';
						for (int i=0; i<array.dataCount; i++)
						{
							*buf++ = '0';
							*buf++ = 'x';
							itoa(&buf, array.data[i], 16);
							if (i != (array.dataCount-1)) *buf++ = ',';
						}
						*buf++ = ']';
					}
					break;

				case 'c':
					*buf++ = va_arg(va, int);
					break;

				case 'd':
				case 'i':
					{
						signed int val = va_arg(va, signed int);
						if (val < 0)
						{
							val *= -1;
							*buf++ = '-';
						}
						itoa(&buf, val, 10);
					}
					break;

				case 's':
					{
						char * arg = va_arg(va, char *);
						while (*arg)
						{
							*buf++ = *arg++;
						}
					}
					break;

				case 'u':
					itoa(&buf, va_arg(va, unsigned int), 10);
					break;

				case 'b': //
					{
						int val = va_arg(va, unsigned int);

						for (int i=7; i>=0; --i)
						{
							if (val & (1<<i)) *buf++ = '1';
							else *buf++ = '0';
						}
					}
					break;

				case 'B':
					{
						int val = va_arg(va, unsigned int);

						for (int i=32-1; i>=0; --i)
						{
							if (val & (1<<i)) *buf++ = '1';
							else *buf++ = '0';
						}
					}
					break;

				case 'D': // by tB
					// double digit value (always two chars, ex: "02" instead of "2")
					{
						int val = va_arg(va, unsigned int);
						if (val<10) *buf++ = '0'; // Add "0" if value is less then 10
						itoa(&buf, val, 10);
					}
					break;

				case '3': // by tB
					// triple digit value (always three chars, ex: "002" instead of "2")
					{
						int val = va_arg(va, unsigned int);
						if (val<100) *buf++ = '0'; // Add "0" if value is less then 100
						if (val<10) *buf++ = '0'; // Add "0" if value is less then 10
						itoa(&buf, val, 10);
					}
					break;

				case 'l': // by tB
					{
						unsigned long val = va_arg(va, unsigned long);
						if (val < 0)
						{
							val *= -1;
							*buf++ = '-';
						}
						ltoa(&buf,val, 10);
					}
					break;

				case 'x':
				case 'X':
					itoa(&buf, va_arg(va, int), 16);
					break;

				case '%':
					*buf++ = '%';
					break;
			}
			fmt++;
		}
		/* Else just copy */
		else
		{
			*buf++ = *fmt++;
		}
	}
	*buf = 0;

	return (int)(buf - start_buf);
}

/*************************************************************************************************/
