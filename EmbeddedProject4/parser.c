/*
 * parser.c
 *
 *  Created on: May 13, 2015
 *      Author: tB
 */

/*************************************************************************************************/

#include "parser.h"

#include "typedefs.h"

/*************************************************************************************************/

boolean eventOccured;
u16 paramCode;
u16 paramValue;

/*************************************************************************************************/

void Parser_ParamReceived(u16 _paramCode, u16 _paramValue)
{
	paramCode = _paramCode;
	paramValue = _paramValue;
	eventOccured = true;
}

/*************************************************************************************************/

boolean Parser_GetEvent(void)
{
	boolean temp = eventOccured;

	eventOccured = false; // Clear flag after param read

	return temp;
}

/*************************************************************************************************/

u16 Parser_GetParamCode(void)
{
	return paramCode;
}

/*************************************************************************************************/

u16 Parser_GetParamValue(void)
{
	return paramValue;
}

/*************************************************************************************************/
