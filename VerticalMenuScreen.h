// VerticalMenu.h
#pragma once

#ifndef _VERTICALMENUSCREEN_h
#define _VERTICALMENUSCREEN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Button.h"
#include "FishLightProgram.h"
#include "TinyArray.h"
#include "MenuScreen.h"
#include "VerticalMenuItem.h"

class VerticalMenuScreen : MenuScreen
{
	int8_t m_selectedIndex{ 0 };
	TinyArray<VerticalMenuItem*>* m_items{ new TinyArray<VerticalMenuItem*>(7) };
	int8_t m_delayedAction{ 0 };

public:
	VerticalMenuScreen();
	~VerticalMenuScreen();

	TinyArray<VerticalMenuItem*>* Items() const { return this->m_items; }
	void AddMenuItem(VerticalMenuItem* item);
	VerticalMenuItem* SelectedItem();
	void CancelChanges();
	void ConfirmChanges();

	void DrawToScreen(FishLightProgram* program) override;
	void ButtonPressed(FishLightProgram* program, Button button) override;
	void Update(FishLightProgram* program) override;
};


#endif

