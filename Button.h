// Button.h
#pragma once

#ifndef _BUTTON_h
#define _BUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

enum class Button
{
	None = 0,
	Left = 1,
	Right = 2,
	Up = 3,
	Down = 4,
#if FIVE_BUTTON_BUILD
	Enter = 5
#endif
};

#endif

