/*
 * parser.h
 *
 *  Created on: May 13, 2015
 *      Author: tB
 */

#ifndef PARSER_H_
#define PARSER_H_

/*************************************************************************************************/

#include "typedefs.h"

/*************************************************************************************************/

boolean Parser_GetEvent(void);
u16 Parser_GetParamCode(void);
u16 Parser_GetParamValue(void);
void Parser_ParamReceived(u16 paramCode, u16 paramValue); // Event from SuperLogicCompiler

/*************************************************************************************************/

#endif /* PARSER_H_ */
