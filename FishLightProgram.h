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

class FishLightProgram
{
protected:
	LiquidCrystal* m_controlPanel{ nullptr };
	DS3231* m_realTimeClock{ nullptr };
	ButtonManager* m_buttonManager{ nullptr };
	DisplaySettings* m_displaySettings{ nullptr };

	bool m_popTopScreen{ false };
	bool m_screenNeedsRefresh{ false };
	bool m_screenOff{ false };

	const uint64_t idleTimeToScreenShutoff{ 1000ULL * 60ULL };

	void makeMainMenu();
	void initEEPROM();
	void loadSettings();

public:
	TinyArray<MenuScreen*>* menuScreenStack{ new TinyArray<MenuScreen*>(5, true) };

	FishLightProgram();
	~FishLightProgram();

	LiquidCrystal* ControlPanel() const { return this->m_controlPanel; }
	DS3231* RealTimeClock() const { return this->m_realTimeClock; }
	DisplaySettings* ControlPanelSettings() const { return this->m_displaySettings; }

	void Init();
	void Update();

	void OnButtonPressed(Button button);
	void RefreshScreen();
	void CancelRefreshScreen();
	void RemoveTopScreen();

	static FishLightProgram* Instance()
	{
		static FishLightProgram* instance = new FishLightProgram();
		return instance;
	}
};

#endif

