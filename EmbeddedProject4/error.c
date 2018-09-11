
/*************************************************************************************************/

#include "error.h"


#include "typedefs.h"
#include "debug.h"
#include "general.h"

/*************************************************************************************************/

//const char * errorTypeAsString[] = { ErrorsTypesList(ErrorTypeAsString) };

/*************************************************************************************************/

//void Error(errorType_t errorType, error_t errorCode, char * extraDescription)
//{
//	if (errorCode < ERRORS_COUNT)
//	{
//		Debug("%s ERROR %u (%s)", errorTypeAsString, errorCode, extraDescription);
//
//		switch (errorType)
//		{
//			case errorType_FATAL: Debug("System halted!"); while(1); break;
//			default: break;
//		}
//	}
//	else Error(errorType_INTERNVAL, error_UNHANDLED_ERROR, "Out of errors list range");
//}
void Error(error_t errorCode)
{
	if (errorCode < ERRORS_COUNT)
	{
		Debug("ERROR %u", errorCode);

	}
	else Error(error_UNHANDLED_ERROR);
}

/*************************************************************************************************/
