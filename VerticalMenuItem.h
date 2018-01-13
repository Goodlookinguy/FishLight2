// VerticalMenuItem.h
#pragma once

#ifndef _VERTICALMENUITEM_h
#define _VERTICALMENUITEM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BuildConsts.h"
#include "VerticalMenuItemType.h"
#include "VerticalMenuFunction.h"

class VerticalMenuItem
{
public:
	String name{ "" };
	VerticalMenuItemType type{ VerticalMenuItemType::None };
	VerticalMenuFunc* changeAction{ nullptr };

	VerticalMenuItem(const String& name);

	virtual void OnPressRight() {}
	virtual void OnPressLeft() {}
	virtual void OnPressUp() {}
	virtual void OnPressDown() {}
#if FIVE_BUTTON_BUILD
	virtual void OnPressEnter() {}
#endif
};

#endif

