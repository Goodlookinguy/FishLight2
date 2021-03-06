// VerticalMenuItem.h
#pragma once

#ifndef _VERTICALMENUITEM_h
#define _VERTICALMENUITEM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "FishLightProgram.h"
#include "BuildConsts.h"
//#include "VerticalMenuScreen.h"
#include "VerticalMenuItemType.h"
#include "VerticalMenuFunction.h"
#include "MenuItemFunc.h"

class VerticalMenuItem
{
public:
	String name{ "" };
	MenuItemFunc changeAction{ nullptr };
	MenuItemFunc confirmAction{ nullptr };
	MenuItemFunc cancelAction{ nullptr };

	VerticalMenuItem(const String& name);
	virtual ~VerticalMenuItem(){}

	virtual void DrawToScreen(FishLightProgram* program, VerticalMenuScreen* screen, bool isSelected) {}

	virtual void OnPressRight(FishLightProgram* program, VerticalMenuScreen* screen) {}
	virtual void OnPressLeft(FishLightProgram* program, VerticalMenuScreen* screen) {}
#if FIVE_BUTTON_BUILD
	virtual void OnPressEnter(FishLightProgram* program, VerticalMenuScreen* screen) {}
#endif
};

#endif

