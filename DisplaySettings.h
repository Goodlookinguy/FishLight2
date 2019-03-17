// DisplaySettings.h
#pragma once

#ifndef _DISPLAYSETTINGS_h
#define _DISPLAYSETTINGS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "DisplayIdleScreen.h"

class DisplaySettings
{
public:
	int8_t backlight{ 100 };
	DisplayIdleScreen idleScreen{ DisplayIdleScreen::Cat };

	float backlightAsPercent() const
	{
		return (float)backlight / 100.0f;
	}

	int16_t backlightAsPinValue() const
	{
		return backlightAsPercent() * 255.0f;
	}
};

#endif

