// LightMenuObject.h

#ifndef _LIGHTMENUOBJECT_h
#define _LIGHTMENUOBJECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Color.h"

class LightMenuTag
{
public:
	Color* Color;
	// store info about where to write to EEPROM here
};

#endif

