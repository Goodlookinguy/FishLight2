// FishLightProgram.h
#pragma once

#ifndef _FISHLIGHTPROGRAM_h
#define _FISHLIGHTPROGRAM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <LiquidCrystal.h>
#include <DS3231.h>
#include "ButtonManager.h"
#include "TinyArray.h"
#include "MenuScreen.h"

class FishLightProgram
{
protected:
	LiquidCrystal* m_controlPanel{ nullptr };
	DS3231* m_realTimeClock{ nullptr };
	ButtonManager* m_buttonManager{ nullptr };
	TinyArray<MenuScreen*>* m_menuScreenStack{ new TinyArray<MenuScreen*>(5, true) };

	bool m_screenNeedsRefresh{ false };
	bool m_screenOff{ false };

	const uint64_t idleTimeToScreenShutoff{ 1000ULL * 60ULL };

	void makeMainMenu();

public:
	FishLightProgram();
	~FishLightProgram();

	LiquidCrystal* ControlPanel() const { return this->m_controlPanel; }
	DS3231* RealTimeClock() const { return this->m_realTimeClock; }

	void Init();
	void Update();

	void OnButtonPressed(Button button);
	void RefreshScreen();

	static FishLightProgram* Instance()
	{
		static FishLightProgram* instance = new FishLightProgram();
		return instance;
	}
};

#endif

