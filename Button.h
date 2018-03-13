// Button.h
#pragma once

#ifndef _BUTTON_h
#define _BUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BuildConsts.h"

enum class Button : uint8_t
{
	None = 0,
	Left = 1,
	Right = 2,
	Up = 3,
	Down = 4,
	// Tactile Button 0
	TB0 = 1,
	TB1 = 2,
	TB2 = 3,
	TB3 = 4,
#if FIVE_BUTTON_BUILD
	Enter = 5,
	TB4 = 5,
#endif
};

#endif

