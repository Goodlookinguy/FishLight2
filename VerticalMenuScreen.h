// VerticalMenu.h
#pragma once

#ifndef _VERTICALMENUSCREEN_h
#define _VERTICALMENUSCREEN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "MenuScreen.h"

class VerticalMenuScreen : MenuScreen
{
public:
	VerticalMenuScreen();
	void DrawToScreen(FishLightProgram* program) override;
	void ButtonPressed(FishLightProgram* program, Button button) override;
	void Update(FishLightProgram* program) override;
};


#endif

