/*
 * params.h
 *
 *  Created on: Mar 9, 2015
 *      Author: tB
 */

#ifndef PARAMS_H_
#define PARAMS_H_


#include "frame.h"

typedef enum
{
	configParseReturn_OK,
	configParseReturn_EXTRACTION_ERROR, // Not initialized, pointer out of range etc
	configParseReturn_PARAM_ERROR, // Not found, wrong type etc
	configParseReturn_PARSER_ERROR, // Can not extract, unhandled type etc
}
configParseReturn_t;

void Params_Print(void);
configParseReturn_t Config_Parse(frame_t * frame);


#endif /* PARAMS_H_ */
