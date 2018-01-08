// VerticalMenuItem.h
#pragma once

#ifndef _VERTICALMENUITEM_h
#define _VERTICALMENUITEM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "VerticalMenuItemType.h"

class VerticalMenuItem
{
public:
	String name{ "" };
	VerticalMenuItemType type{ VerticalMenuItemType::None };

};

#endif

