// DisplayIdleScreen.h
#pragma once

#ifndef _DISPLAYIDLESCREEN_h
#define _DISPLAYIDLESCREEN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

enum class DisplayIdleScreen : int8_t
{
	Cat = 0,
	DateTime = 1
};

#endif

