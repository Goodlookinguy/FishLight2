// VerticalMenuItemPercent.h

#ifndef _VERTICALMENUITEMPERCENT_h
#define _VERTICALMENUITEMPERCENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "VerticalMenuItem.h"

class VerticalMenuItemPercent : VerticalMenuItem
{
public:
	uint8_t percent{ 0 };

	VerticalMenuItemPercent(const String& name, uint8_t percent);
};

#endif

