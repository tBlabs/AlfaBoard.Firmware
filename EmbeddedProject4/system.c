/*
 * system.c
 *
 *  Created on: Jan 4, 2016
 *      Author: tB
 */

#include "system.h"

#include <logics.h>
#include <typedefs.h>
#include <timeout.h>
#include "debug.h"
void System_StoreMaps(u16 store)
{
	static timeout_t lastMapsStoreMoment;
	static u8 lastMapsXor;


	if (store)
	{
		// Nie cz�ciej jak 5 razy na sekund�..
		if (Tick(&lastMapsStoreMoment, 200))
		{
			u8 xor = Maps_Xor();
			Debug("%u", xor);
			// ..o ile mapa si� zmieni..
			if (xor != lastMapsXor)
			{
				lastMapsXor = xor;

				Debug("Storing map..");
				// ..dokonaj zapisu
				Maps_Store();
			}
		}
	}
}
