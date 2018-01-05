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
private:
	//NduinoEvent<ButtonPressedEventArgs>* m_buttonPressed
	//{ new NduinoEvent<ButtonPressedEventArgs> };
protected:
	// He used a 1M Ohm resister and it gives back weird values...
	const int16_t ButtonRanges[10]
	{
		1015, 1023, // idle, none
		5, 20, // left (1)
		65, 80, // right (2)
		116, 131, // up (3)
		165, 180 // down (4)
	};

	uint8_t ButtonPin = -1;
	uint64_t LastButtonPressTime = 0;
	uint64_t LastButtonActivateTime = 0;
	const uint16_t SameButtonRegisterWaitTime = 370; // Should be a fairly low value
	const uint8_t RegisterTime = 6; // Should be a very low value
	Button LastButtonPressed = Button::None;

	static bool InRange(int32_t value, int32_t low, int32_t high);
	Button ButtonPressToButton(int16_t button) const;
	//void UpdateButtonsStatus(NduinoProgram* program);

public:
	// ------
	//uint32_t static UID() { return 1; }
	//Type UpdateType() override { return Type::PreUpdate; }
	void Update(FishLightProgram* program);
	// ------

	void Register4ButtonPin(const uint8_t pin);
	//NduinoEvent<ButtonPressedEventArgs>& ButtonPressed();
};

#endif

