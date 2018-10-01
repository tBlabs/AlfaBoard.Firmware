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
/*  0 */	err(error_UNKNOWN_ERROR) \
/*  1 */	err(error_INVALID_FRAME_TYPE) \
/*  1 */	err(error_INVALID_FRAME_SIZE) \
/*  2 */	err(error_ARG_OUT_OF_RANGE) \



#define ErrorEnum(e) e,
typedef enum { ErrorsList(ErrorEnum) ERRORS_COUNT } error_t;


//#define GetName(e) #e,
//extern const char * errorsAsString[];


//void Error(errorType_t errorType, error_t errorCode, char * extraDescription);
void Error(error_t errorCode);

#endif /* _ERROR_H_ */

