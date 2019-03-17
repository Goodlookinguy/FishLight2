// MenuActionType.h
#pragma once

#ifndef _MENUACTIONTYPE_h
#define _MENUACTIONTYPE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

enum class MenuActionType
{
	None = 0,
	ChangeScreen = 1,
	ClickLeft = 2,
};

#endif

