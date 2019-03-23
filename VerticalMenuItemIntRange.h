// VerticalMenuItemIntRange.h
#pragma once

#ifndef _VERTICALMENUITEMINTRANGE_h
#define _VERTICALMENUITEMINTRANGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "VerticalMenuItem.h"
#include "LuzMath.h"

class VerticalMenuItemIntRange : public VerticalMenuItem
{
	int16_t m_initValue{ 0 };
	int16_t m_value{ 0 };
	int16_t m_min{ 0 };
	int16_t m_max{ 0 };
public:
	int8_t incrementalChange{ 1 };
	void* tag{ nullptr };

	VerticalMenuItemIntRange(const String& name, int16_t initValue, int16_t min, int16_t max);

	int16_t Min() const { return this->m_min; }
	void Min(int16_t min)
	{
		this->m_min = min;
		this->m_value = Math<int16_t>::Clamp(this->m_value, this->m_min, this->m_max);
	}

	int16_t Max() const { return this->m_max; }
	void Max(int16_t max)
	{
		this->m_max = max;
		this->m_value = Math<int16_t>::Clamp(this->m_value, this->m_min, this->m_max);
	}

	int16_t Value() const { return this->m_value; }
	void Value(int16_t value)
	{
		this->m_value = Math<int16_t>::Clamp(value, this->m_min, this->m_max);
	}

	int16_t InitValue() const { return this->m_initValue; }
	void InitValue(int16_t initValue)
	{
		this->m_initValue = Math<int16_t>::Clamp(initValue, this->m_min, this->m_max);
	}

	void DrawToScreen(FishLightProgram* program, VerticalMenuScreen* screen, bool isSelected) override;

	void OnPressLeft(FishLightProgram* program, VerticalMenuScreen* screen) override;
	void OnPressRight(FishLightProgram* program, VerticalMenuScreen* screen) override;
#if FIVE_BUTTON_BUILD
	void OnPressEnter(FishLightProgram* program, VerticalMenuScreen* screen) override {};
#endif
};

#endif

