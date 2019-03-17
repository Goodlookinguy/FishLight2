// ButtonManager.h
#pragma once

#ifndef _BUTTONMANAGER_h
#define _BUTTONMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Button.h"

class FishLightProgram;

class ButtonManager
{
protected:
#if FIVE_BUTTON_BUILD
	const int16_t ButtonRanges[12]
	{
		1000, 1023, // idle, none
		0, 45, // left (1)
		400, 445, // right (2)
		210, 255, // up (3)
		590, 635, // down (4)
		805, 850 // enter (5)
	};
#else
	const int16_t ButtonRanges[10]
	{
		1000, 1023, // idle, none
		5, 20, // left (1)
		65, 80, // right (2)
		116, 131, // up (3)
		165, 180, // down (4)
	};
#endif
	//Left (0-20), Up (210-230), Right (400-420), Down (590-610), Enter (805-825)

	uint8_t ButtonPin = -1;
	uint64_t m_lastButtonPressTime = 0;
	uint64_t LastButtonActivateTime = 0;
	const uint16_t SameButtonRegisterWaitTime = 370; // Should be a fairly low value
	const uint16_t m_coolDownTime{ 120 };
	const uint8_t RegisterTime = 6; // Should be a very low value
	Button LastButtonPressed = Button::None;

	static bool InRange(int32_t value, int32_t low, int32_t high);
	Button ButtonPressToButton(int16_t button) const;

public:
	// ------
	void Update(FishLightProgram* program);
	// ------
	uint64_t LastButtonPressTime() { return this->m_lastButtonPressTime; }

	void RegisterButtonsPin(const uint8_t pin);
};

#endif

