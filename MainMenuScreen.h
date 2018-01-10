// MainMenu.h
#pragma once

#ifndef _MAINMENUSCREEN_h
#define _MAINMENUSCREEN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "MenuScreen.h"
#include "TinyArray.h"
#include "MainMenuItem.h"

// Title 
// [o] [a] [d] [w]
// <-- Goes left and right -->
class MainMenuScreen : MenuScreen
{
	int8_t m_charsLoaded{ 0 };
	uint8_t m_selectedIndex{ 0 };
	TinyArray<MainMenuItem*>* m_items{ new TinyArray<MainMenuItem*>(7) };

public:
	MainMenuScreen() : MenuScreen() {}

	void DrawToScreen(FishLightProgram* program) override;
	void ButtonPressed(Button button) override;
	//void ChangeSelectedItem(int8_t d);
	int8_t GetItemIndex(int8_t index);
	MainMenuItem* GetItem(int8_t index);
	void AddMenuItem(MainMenuItem* menuItem);
};

#endif

