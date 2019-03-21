// VerticalMenuItemPercent.h

#ifndef _VERTICALMENUITEMPERCENT_h
#define _VERTICALMENUITEMPERCENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BuildConsts.h"
#include "VerticalMenuItem.h"

class VerticalMenuItemPercent : public VerticalMenuItem
{
public:
	int8_t percent{ 0 };
	int8_t incrementalChange{ 5 };
	int8_t initPercent{ 0 };
	void* tag{ nullptr };

	VerticalMenuItemPercent(const String& name, int8_t percent);
	VerticalMenuItemPercent(const String& name, int8_t percent, int8_t incrementalChange);

	void DrawToScreen(FishLightProgram* program, VerticalMenuScreen* screen, bool isSelected) override;

	void OnPressRight(FishLightProgram* program, VerticalMenuScreen* screen) override;
	void OnPressLeft(FishLightProgram* program, VerticalMenuScreen* screen) override;
	//void OnPressUp(FishLightProgram* program, VerticalMenuScreen* screen) override {};
	//void OnPressDown(FishLightProgram* program, VerticalMenuScreen* screen) override {};
#if FIVE_BUTTON_BUILD
	void OnPressEnter(FishLightProgram* program, VerticalMenuScreen* screen) override {};
#endif
};

#endif

