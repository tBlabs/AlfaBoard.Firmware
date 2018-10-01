/*
 * host.h
 *
 *  Created on: Jan 11, 2016
 *      Author: tB
 */

#ifndef HOST_H_
#define HOST_H_

#include "error.h"
#include <frame.h>

void SendOk(void);
void SendError(error_t errorCode);
void SendIntro(void);
void LoadMap(frame_t * frame);
void LogicRun(void);
void LogicHold(void);
void HostTask(void);
void SendValue(u8 addr, u32 value);

#endif /* HOST_H_ */
