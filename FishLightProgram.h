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
#include "DisplaySettings.h"
#include "Color.h"

class FishLightProgram
{
protected:
	LiquidCrystal* m_controlPanel{ nullptr };
	DS3231* m_realTimeClock{ nullptr };
	ButtonManager* m_buttonManager{ nullptr };
	DisplaySettings* m_displaySettings{ nullptr };

	Color* m_morningColor{ nullptr };
	Color* m_dayColor{ nullptr };
	Color* m_eveningColor{ nullptr };
	Color* m_nightColor{ nullptr };

	bool m_popTopScreen{ false };
	bool m_screenNeedsRefresh{ false };
	bool m_screenOff{ false };

	const uint64_t idleTimeToScreenShutoff{ 1000ULL * 60ULL };
	uint64_t startTime{ 0 };

	void makeMainMenu();
	void initEEPROM();
	void loadSettings();

	void updateLight();
	void restoreLight();

public:
	TinyArray<MenuScreen*>* menuScreenStack{ new TinyArray<MenuScreen*>(3, true) };

	FishLightProgram();
	~FishLightProgram();

	LiquidCrystal* ControlPanel() const { return this->m_controlPanel; }
	DS3231* RealTimeClock() const { return this->m_realTimeClock; }
	DisplaySettings* ControlPanelSettings() const { return this->m_displaySettings; }

	Color* MorningColor() { return this->m_morningColor; }
	Color* DayColor() { return this->m_dayColor; }
	Color* EveningColor() { return this->m_eveningColor; }
	Color* NightColor() { return this->m_nightColor; }

	void Init();
	void Update();

	void OnButtonPressed(Button button);
	void RefreshScreen();
	void CancelRefreshScreen();
	void RemoveTopScreen();

	void RefreshLight();

	static FishLightProgram* Instance()
	{
		static FishLightProgram* instance = new FishLightProgram();
		return instance;
	}
};

#endif

