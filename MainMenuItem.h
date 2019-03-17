// MainMenuItem.h
#pragma once

#ifndef _MAINMENUITEM_h
#define _MAINMENUITEM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "MenuAnimation.h"
#include "MenuItemFunc.h"

class MainMenuItem
{
public:
	String name{ "" };
	MenuAnimation* animation{ nullptr };
	MenuItemFunc enterAction{ nullptr };

	MainMenuItem(String name);
};

#endif

