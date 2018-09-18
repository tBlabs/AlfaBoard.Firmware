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
/*  0 */	err(error_INVALID_FRAME_TYPE) \



#define ErrorEnum(e) e,
typedef enum { ErrorsList(ErrorEnum) ERRORS_COUNT } error_t;


//#define GetName(e) #e,
//extern const char * errorsAsString[];


//void Error(errorType_t errorType, error_t errorCode, char * extraDescription);
void Error(error_t errorCode);

#endif /* _ERROR_H_ */

