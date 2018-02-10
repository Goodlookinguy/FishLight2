// VerticalMenuItemCancelConfirm.h
#pragma once

#ifndef _VERTICALMENUITEMCANCELCONFIRM_h
#define _VERTICALMENUITEMCANCELCONFIRM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "VerticalMenuItem.h"

class VerticalMenuItemCancelConfirm : VerticalMenuItem
{
	bool cancelConfirm{ false };

public:
	VerticalMenuItemCancelConfirm();

	void DrawToScreen(FishLightProgram* program, VerticalMenuScreen* screen, bool isSelected) override;

	void OnPressRight(FishLightProgram* program, VerticalMenuScreen* screen) override;
	void OnPressLeft(FishLightProgram* program, VerticalMenuScreen* screen) override;
#if FIVE_BUTTON_BUILD
	void OnPressEnter(FishLightProgram* program, VerticalMenuScreen* screen) override;
#endif
};

#endif

