// BuildConsts.h
#pragma once

#ifndef _BUILDCONSTS_h
#define _BUILDCONSTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

////////////////////////////////
// BUILD OPTIONS
#define UNO_BUILD false
#define FIVE_BUTTON_BUILD false

#endif

