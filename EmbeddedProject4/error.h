#ifndef _ERROR_H_
#define _ERROR_H_

#include "typedefs.h"


// ENUM
#define ErrorsTypesList(errType) \
	errType(errorType_INTERNVAL,	"INTERNAL") \
	errType(errorType_CRITICAL,		"CRITICAL") \
	errType(errorType_FATAL,		"FATAL") \

#define ErrorTypeEnum(e,asText) e,
typedef enum { ErrorsTypesList(ErrorTypeEnum) } errorType_t;

#define ErrorTypeAsString(e,asText) asText,
extern const char * errorTypeAsString[];



// ENUM
#define ErrorsList(err) \
/*  0 */	err(error_UNHANDLED_ERROR) \
/*  1 */	err(error_UNKNOWN_GATE_TYPE) \
/*  2 */	err(error_UNKNOWN_LATCH_TYPE) \
/*  3 */	err(error_UNKNOWN_COMPARATOR_TYPE) \
/*  4 */	err(error_UNKNOWN_CHANGE_DETECTOR_TYPE) \
/*  5 */	err(error_UNKNOWN_MATH_TYPE) \
/*  6 */	err(error_UNKNOWN_DELAY_TYPE) \
/*  7 */	err(error_UNKNOWN_PASSER_TYPE) \
/*  8 */	err(error_UNKNOWN_DEVICE) \
/*  9 */	err(error_OUT_OF_ARRAY_RANGE) \
/* 10 */	err(error_OUT_OF_MAP_RANGE) \
/* 11 */	err(error_CAN_NOT_VALIDATE_DEVICE) \
/* 12 */	err(error_MAP_IS_TOO_BIG) \
/* 13 */	err(error_MAP_VALIDATION_TIMEOUT) \
/* 14 */	err(error_MAP_VALIDATION_ERROR) \
/* 15 */	err(error_INCOMPATIBILITY_OF_TYPES) \
/* 16 */	err(error_PARAM_NOT_FOUND) \
/* 17 */	err(error_CONFIG_PARSE_PROBLEM) \
/* 18 */	err(error_PARAM_FRAME_PROBLEM) \
/* 19 */	err(error_COULD_NOT_CLEAR_MAPS) \



#define ErrorEnum(e) e,
typedef enum { ErrorsList(ErrorEnum) ERRORS_COUNT } error_t;


//#define GetName(e) #e,
//extern const char * errorsAsString[];


//void Error(errorType_t errorType, error_t errorCode, char * extraDescription);
void Error(error_t errorCode);

#endif /* _ERROR_H_ */

