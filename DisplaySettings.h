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

struct DisplaySettings
{
	float brightness{ 1.0f };
	DisplayIdleScreen idleScreen{ DisplayIdleScreen::Cat };
};

#endif

