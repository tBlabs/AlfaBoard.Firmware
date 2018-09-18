/*
 * params.c
 *
 *  Created on: Mar 5, 2015
 *      Author: tB
 */

/*************************************************************************************************/

#include "params.h"

#include "typedefs.h"
#include "extractor.h"
#include "error.h"
#include "frame.h"

/*************************************************************************************************/

#define PARAMS_DEBUG_ENABLE		1


#if (PARAMS_DEBUG_ENABLE==0)
	#define ParamsDebug(str,...)
#else
	#include "debug.h"
	#include "delay.h"
	#define ParamsDebug(str,...) Debug(str,##__VA_ARGS__)
#endif

/*************************************************************************************************/

typedef enum
{
	paramType_U8 = 1,
	paramType_U16,
	paramType_U32,
	paramType_TEXT, // First byte is a text length. There is no ending zero.
}
paramType_t;

typedef u16 paramCode_t; // Remember of changes in all Parsers!

struct
{
	u16 test;
}
config;

typedef enum
{
	accessType_DIRECT, // variable
	accessType_SETTER // function
}
accessType_t;

#include "rtc.h"


// ENUM | VALUE | TYPE | ACCESSOR TYPE | ACCESSOR/VARIABLE
#define ParamsList(param) \
	param(param_RTC,	1,		paramType_U32,		accessType_SETTER,		Clock_Set) \

//param(param_TEST,	2,		paramType_U16,		accessType_DIRECT,		config.test)


#define ParamEnum(e,ev,type,accessType,access) e,
enum { ParamsList(ParamEnum) };




typedef void (*void_F_u32)(u32); // Pointer to function returning void and getting u32

typedef struct PACKED
{
	paramCode_t code;
	paramType_t type:6;
	accessType_t access:2;
	union
	{
		addr_t setter; // Accessor function
		addr_t variable; // Address of variable
	};
}
param_t;

#define Param(e,ev,type,accessType,access) {ev,type,accessType,{(u32)&access}},
 param_t params[] = { ParamsList(Param) };

const u8 paramsCount = sizeof(params)/sizeof(param_t);

#if (PARAMS_DEBUG_ENABLE==1)
void Params_Print(void)
{
	Debug("Params:");
	for (u8 i=0; i<paramsCount; i++)
		Debug("%u. #%u:%u @%u", i, params[i].code, params[i].type, params[i].access);
}
#endif
/*
	Abilities:
					SETTER	DIRECT
	paramType_U8	  -       -
	paramType_U16	  -       -
	paramType_U32	  v       v
	paramType_TEXT	  -       -


*/

/*************************************************************************************************/

boolean Param_Find(paramCode_t paramCode, param_t * param)
{
	for (u16 i = 0; i < paramsCount; i++)
	{
		if (paramCode <= params[i].code) // '<=' to search by param family too (cause params comes with offset from master)
		{
			*param = params[i];
			return true;
		}
	}

	return false;
}

/*************************************************************************************************/

// {paramsCount:8}({code:16}{type:8}{data:0+})
configParseReturn_t Config_Parse(frame_t * frame)
{
	ParamsDebug("Config_Parse()");

	extractor_t extractor;
	paramCode_t extractedParamCode;
	param_t param;
	paramType_t extractedParamType;

	Extractor_Init(&extractor, frame->data, frame->dataSize); // Register pointer and data buffer

	DebugArray(extractor.data, extractor.dataCount);

	u8 paramsCount = 0;
	if (Extractor_GetU8(&extractor, &paramsCount))
	{
		DebugDec(paramsCount);

		if (paramsCount > 0)
		{
			while (Extractor_IsWorking(&extractor))
			{
				if (Extractor_GetU16(&extractor, &extractedParamCode))
				{
					ParamsDebug("extractedParamCode: %u", extractedParamCode);

					if (Param_Find(extractedParamCode, &param))
					{
						if (Extractor_GetU8(&extractor, &extractedParamType))
						{
							ParamsDebug("extractedParamType: %u", extractedParamType);

							if (param.type == extractedParamType)
							{
								switch (param.type)
								{
									case paramType_U32:
										{
											//Debug("paramType_U32");
											u32 u32TempValue = 0;
											if (Extractor_GetU32(&extractor, &u32TempValue))
											{
												ParamsDebug("u32TempValue: %u", u32TempValue);

												switch (param.access)
												{
													case accessType_SETTER:
														{
															void_F_u32 Setter = (void_F_u32)param.setter;
															Setter(u32TempValue);
														}
														break;

													case accessType_DIRECT:
														{
															*(u32*)(param.variable) = u32TempValue; //????????????????
														}
														break;
												}
											}
											//else ParamsDebug("Extraction error");
										}
										break;

									default: break;
								}
							}
							else { Error(error_UNKNOWN_ERROR); goto error; }
						}
					}
					else { Error(error_UNKNOWN_ERROR); goto error; }
				}
			} // while
		} // paramCount != 0
	}

	ParamsDebug("Config_Parse().");

	if (Extractor_Status(&extractor) == extractorStatus_SUCCESS) goto success;
	else goto error;

	success:
		return true;

	error:
		return false;
}

