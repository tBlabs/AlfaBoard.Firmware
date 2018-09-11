/*
 * typedefs.h
 *
 *  Created on: Apr 9, 2014
 *      Author: TomB
 */

#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

/*************************************************************************************************/

#include <stdint.h>

/*************************************************************************************************/

typedef int8_t 		s8;
typedef uint8_t 	u8;
typedef u8 			u4;
typedef int16_t 	s16;
typedef uint16_t 	u16;
typedef u16 		u12;
typedef int32_t 	s32;
typedef uint32_t 	u32;
typedef int64_t 	s64;
typedef uint64_t 	u64;
typedef uint8_t 	bool;
typedef uint8_t 	boolean;
typedef u32 		addr_t;
typedef u8			percent_t;

/*************************************************************************************************/

#define ADDR(var)		((u32)(&var)) // get address of value

#define SizeOfStringsArray(arr)	(sizeof(arr)/sizeof(pointerToConstString_t))

/*************************************************************************************************/

#define true 		1
#define false 		0

/*************************************************************************************************/

#endif /* TYPEDEFS_H_ */
