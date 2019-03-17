// VerticalMenuItemOptions.h
#pragma once

#ifndef _VERTICALMENUITEMOPTIONS_h
#define _VERTICALMENUITEMOPTIONS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "VerticalMenuItem.h"
#include "TinyArray.h"

class VerticalMenuItemOptions : public VerticalMenuItem
{
	int8_t m_selectedIndex{ 0 };
	TinyArray<String>* m_displayValueItems{ nullptr };
	TinyArray<int8_t>* m_valueItems{ nullptr };

public:
	VerticalMenuItemOptions(const String& name, const uint8_t size);
	virtual ~VerticalMenuItemOptions();

	void AddOption(const String& displayValue, int8_t value);
	String Value() { return this->m_displayValueItems->Get(this->m_selectedIndex); }
	int8_t ValueIndex() { return m_selectedIndex; }
	void ValueIndex(int8_t index) { this->m_selectedIndex = index; }

	void DrawToScreen(FishLightProgram* program, VerticalMenuScreen* screen, bool isSelected) override;

	void OnPressLeft(FishLightProgram* program, VerticalMenuScreen* screen) override;
	void OnPressRight(FishLightProgram* program, VerticalMenuScreen* screen) override;
#if FIVE_BUTTON_BUILD
	void OnPressEnter(FishLightProgram* program, VerticalMenuScreen* screen) override {};
#endif
};

#endif
