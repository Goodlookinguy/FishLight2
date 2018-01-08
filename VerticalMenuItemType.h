// VerticalMenuItemType.h
#pragma once

#ifndef _VERTICALMENUITEMTYPE_h
#define _VERTICALMENUITEMTYPE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

enum class VerticalMenuItemType : uint8_t
{
	None = 0,
};

#endif

