// LightMenuObject.h

#ifndef _LIGHTMENUOBJECT_h
#define _LIGHTMENUOBJECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Color.h"

// I'll give 16 bytes to each color, even though they only need 7.
// Morning Color = 64-79
// Day Color = 80-95
// Evening Color = 96-111
// Night Color = 112-127

class LightMenuTag
{
public:
	Color* color{ nullptr };
	// store info about where to write to EEPROM here
	uint16_t eepromAddress{ 0 };
	// 3 for RGB
	// 3 for RGB Strength as int8_t
	// 1 for W
	// 7 bytes
};

#endif

