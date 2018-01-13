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

class VerticalMenuItemPercent : VerticalMenuItem
{
public:
	int8_t percent{ 0 };
	int8_t incrementalChange{ 5 };

	VerticalMenuItemPercent(const String& name, int8_t percent);
	VerticalMenuItemPercent(const String& name, int8_t percent, int8_t incrementalChange);

	void OnPressRight() override;
	void OnPressLeft() override;
	void OnPressUp() override {};
	void OnPressDown() override {};
#if FIVE_BUTTON_BUILD
	void OnPressEnter() override {};
#endif
};

#endif

