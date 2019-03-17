// MenuAnimation.h
#pragma once

#ifndef _MENUANIMATION_h
#define _MENUANIMATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "TinyArray.h"
#include "LiquidCrystal.h"

class MenuAnimation
{
private:
	uint64_t m_startTime{ 0 };
	bool m_active{ false };

public:
	TinyArray<uint8_t*>* frames{ nullptr };
	uint8_t totalFrames;
	int8_t curIndex{ -1 };
	uint16_t hertz{ 4 }; // Updates per second = 1000/hertz
	uint8_t charId{ 0 };

	// Initialize the animation at a specific custom character address (0-7)
	MenuAnimation(const uint8_t totalFrames);
	MenuAnimation(const uint8_t totalFrames, const uint8_t hertz);
	~MenuAnimation();

	void SetFrame(uint8_t id, uint8_t* frameData) const;
	void Play(uint8_t initFrame = 0);
	void Stop();
	void Update(LiquidCrystal* lcdDisplay);
	void LoadCharIntoDisplay(LiquidCrystal* lcdDisplay);
};

#endif

