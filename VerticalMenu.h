// VerticalMenu.h
#pragma once

#ifndef _VERTICALMENU_h
#define _VERTICALMENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

enum class VerticalMenuItemType : uint8_t
{
	None = 0,
};

class VerticalMenuItem
{
public:
	String name{ "" };
	VerticalMenuItemType type{ VerticalMenuItemType::None };
};

class VerticalMenu
{
	
};

#endif

