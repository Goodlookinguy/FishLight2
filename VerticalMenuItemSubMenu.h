// VerticalMenuItemSubMenu.h

#ifndef _VERTICALMENUITEMSUBMENU_h
#define _VERTICALMENUITEMSUBMENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "VerticalMenuItem.h"

class VerticalMenuItemSubMenu : public VerticalMenuItem
{
private:
	// by storing the screen here, the menu has to be created ahead of time and stored in memory, rethink design if memory overflows
	MenuScreen* m_screen{ nullptr };
public:
	void* tag{ nullptr };

	VerticalMenuItemSubMenu(const String& name, MenuScreen* screen);

	void DrawToScreen(FishLightProgram* program, VerticalMenuScreen* screen, bool isSelected) override;

	void OnPressLeft(FishLightProgram* program, VerticalMenuScreen* screen) override {}
	void OnPressRight(FishLightProgram* program, VerticalMenuScreen* screen) override;
#if FIVE_BUTTON_BUILD
	void OnPressEnter(FishLightProgram* program, VerticalMenuScreen* screen) override;
#endif
};

#endif

