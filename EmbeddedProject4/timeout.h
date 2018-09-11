/*
 * timeout.h
 *
 *  Created on: Apr 9, 2014
 *      Author: TomB
 */

#ifndef TIMEOUT_H_
#define TIMEOUT_H_

/*************************************************************************************************/

#include "typedefs.h"

/*************************************************************************************************/

enum
{
	TIMEOUT_1_SECOND = 1000,
	TIMEOUT_3_SECOND = 3000,
	TIMEOUT_5_SECOND = 5000,
	TIMEOUT_30_SECONDS = 30000,
	TIMEOUT_1_MINUTE = 60000,
	TIMEOUT_30_MINUTE = 1800000,
	TIMEOUT_1_HOUR = 3600000,
	TIMEOUT_24_HOURS = 86400000,
};

/*************************************************************************************************/

typedef u32 timeout_t;

/*************************************************************************************************/

void SaveTime(timeout_t * timeKeeper);
bool IsTimeout(timeout_t * timeKeeper, timeout_t timeout);
bool IsTimeoutSlot(timeout_t * timeKeeper, timeout_t timeout, u16 slot);
bool Tick(timeout_t * timeKeeper, timeout_t tickInterval);

/*************************************************************************************************/

#endif /* TIMEOUT_H_ */
