// MenuScreen.h
#pragma once

#ifndef _MENUSCREEN_h
#define _MENUSCREEN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <LiquidCrystal.h>
#include "Button.h"
class FishLightProgram;

class MenuScreen
{
public:
	MenuScreen(){}
	virtual ~MenuScreen(){}
	virtual void DrawToScreen(FishLightProgram* program) {}
	virtual void ButtonPressed(FishLightProgram* program, Button button) {}
	virtual void Update(FishLightProgram* program) {}
};


#endif

