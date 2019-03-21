// 
// 
// 

#include "FishLightProgram.h"
#include "PinConsts.h"
#include "ButtonManager.h"
#include "MainMenuScreen.h"
#include "MenuAnimation.h"
#include "AllAnimations.h"
#include "MenuItemFunc.h"
#include "VerticalMenuScreen.h"
#include "VerticalMenuItem.h"
#include "VerticalMenuItemPercent.h"
#include "VerticalMenuItemCancelConfirm.h"
#include "_MenuEvents.h"
#include <EEPROM.h>
#include "Color.h"
#include <Wire.h>
#include "Math.h"

FishLightProgram::FishLightProgram()
{

}

FishLightProgram::~FishLightProgram()
{
	delete m_controlPanel;
	delete m_realTimeClock;
	delete m_buttonManager;
	delete m_displaySettings;
}

void FishLightProgram::Init()
{
	// first
	pinMode(PIN_BUTTONS, INPUT_PULLUP); // neccessary
	Serial.begin(9600);

	// load up settings from EEPROM
	m_displaySettings = new DisplaySettings();
		//TODO: temp remove
	m_displaySettings->backlight = 50;

	//m_dayColor = new Color(0, 128, 255, 170);
	m_morningColor = new Color(255, 200, 0, 15);
	m_dayColor = new Color(0, 50, 255, 190, 1.0, 1.0, 1.0);
	m_nightColor = new Color(0, 20, 20, 0, 1.0, 1.0, 1.0);

	//auto color = Color(0, 0, 255, 0);
	//color.b = 255;

	//// write from settings
	//analogWrite(PIN_WHITE_LEDS, color.w);
	//analogWrite(PIN_RBG_LEDS_RED, color.r);
	//analogWrite(PIN_RBG_LEDS_GREEN, color.g);
	//analogWrite(PIN_RBG_LEDS_BLUE, color.b);
	analogWrite(PIN_CP_BACKLIGHT, this->m_displaySettings->backlightAsPinValue());
	
	m_controlPanel = new LiquidCrystal(
		PIN_CP_RS, PIN_CP_ENABLE,
		PIN_CP_D0, PIN_CP_D1, PIN_CP_D2, PIN_CP_D3);
	m_controlPanel->begin(16, 2);

	Wire.begin();
	Wire.setClock(400000L);

	m_realTimeClock = new DS3231();
	m_realTimeClock->setClockMode(false);

	m_buttonManager = new ButtonManager();
	m_buttonManager->RegisterButtonsPin(PIN_BUTTONS);

	startTime = millis();
	
	const int8_t alreadyInit = EEPROM[0];
	const bool firstRun = alreadyInit == 0;

	if (firstRun)
		initEEPROM();

	//loadSettings();
	restoreLight();
	makeMainMenu();
	RefreshScreen();
}

void FishLightProgram::Update()
{
	this->m_buttonManager->Update(this);
	this->menuScreenStack->Top()->Update(this);

	if (this->m_popTopScreen)
	{
		this->m_popTopScreen = false;
		MenuScreen* item = this->menuScreenStack->Pop();
		delete item;
		this->RefreshScreen();
	}

	if ((millis() - startTime) % 300 == 0)
		updateLight();

	// run last
	if (this->m_screenNeedsRefresh)
	{
		this->m_screenNeedsRefresh = false;
		menuScreenStack->Top()->DrawToScreen(this);
	}

	// Idling for 2 minutes causes the screen to shut off
	if (!this->m_screenOff &&
		(millis() - this->m_buttonManager->LastButtonPressTime()) > idleTimeToScreenShutoff)
	{
		analogWrite(PIN_CP_BACKLIGHT, 0);
		this->m_screenOff = true;
	}
}

void FishLightProgram::restoreLight()
{
	// 22 <= x <= 6 = night
	// 10 <= x <= 20:30 day
	bool bfalse = false;
	auto rtc = this->m_realTimeClock;
	uint8_t hour = rtc->getHour(bfalse, bfalse);
	uint8_t min = rtc->getMinute();

	if (hour >= 22 || hour < 6)
	{
		analogWrite(PIN_WHITE_LEDS, m_nightColor->W());
		analogWrite(PIN_RBG_LEDS_RED, m_nightColor->R());
		analogWrite(PIN_RBG_LEDS_GREEN, m_nightColor->G());
		analogWrite(PIN_RBG_LEDS_BLUE, m_nightColor->B());
	}
	else if (hour >= 10 || (hour >= 20 && min < 30))
	{
		analogWrite(PIN_WHITE_LEDS, m_dayColor->W());
		analogWrite(PIN_RBG_LEDS_RED, m_dayColor->R());
		analogWrite(PIN_RBG_LEDS_GREEN, m_dayColor->G());
		analogWrite(PIN_RBG_LEDS_BLUE, m_dayColor->B());
	}
}

void FishLightProgram::updateLight()
{
	bool bfalse = false;
	auto rtc = this->m_realTimeClock;
	uint8_t hour = rtc->getHour(bfalse, bfalse);
	
	if ((hour >= 6 && hour <= 10) || (hour >= 20 && hour <= 22))
	{
		uint8_t min = rtc->getMinute();
		uint8_t sec = rtc->getSecond();

		// derp
		if (hour == 6 || (hour == 7 && min < 30))
		{
			double p = Math<double>::Clamp((((hour - 6) * 60 * 60) + min * 60 + sec) / (60.0 * 90.0), 0.0, 1.0);
			analogWrite(PIN_WHITE_LEDS, Math<uint8_t>::Lerp(m_nightColor->W(), m_morningColor->W(), p));
			analogWrite(PIN_RBG_LEDS_RED, Math<uint8_t>::Lerp(m_nightColor->R(), m_morningColor->R(), p));
			analogWrite(PIN_RBG_LEDS_GREEN, Math<uint8_t>::Lerp(m_nightColor->G(), m_morningColor->G(), p));
			analogWrite(PIN_RBG_LEDS_BLUE, Math<uint8_t>::Lerp(m_nightColor->B(), m_morningColor->B(), p));
		}
		else if ((hour == 7 && min >= 30) || hour == 8 || hour == 9 || (hour == 10 && min == 0 && sec <= 5))
		{
			double p = Math<double>::Clamp((((hour - 7) * 60 * 60) + (min - 30) * 60 + sec) / (60.0 * 150.0), 0.0, 1.0);
			analogWrite(PIN_WHITE_LEDS, Math<uint8_t>::Lerp(m_morningColor->W(), m_dayColor->W(), p));
			analogWrite(PIN_RBG_LEDS_RED, Math<uint8_t>::Lerp(m_morningColor->R(), m_dayColor->R(), p));
			analogWrite(PIN_RBG_LEDS_GREEN, Math<uint8_t>::Lerp(m_morningColor->G(), m_dayColor->G(), p));
			analogWrite(PIN_RBG_LEDS_BLUE, Math<uint8_t>::Lerp(m_morningColor->B(), m_dayColor->B(), p));
		}
		else if ((hour == 20 && min >= 30) || hour == 21 || (hour == 22 && min == 0 && sec <= 5))
		{
			double p = Math<double>::Clamp((((hour - 20) * 60 * 60) + (min - 30) * 60 + sec) / (60.0 * 90.0), 0.0, 1.0);
			analogWrite(PIN_WHITE_LEDS, Math<uint8_t>::Lerp(m_dayColor->W(), m_nightColor->W(), p));
			analogWrite(PIN_RBG_LEDS_RED, Math<uint8_t>::Lerp(m_dayColor->R(), m_nightColor->R(), p));
			analogWrite(PIN_RBG_LEDS_GREEN, Math<uint8_t>::Lerp(m_dayColor->G(), m_nightColor->G(), p));
			analogWrite(PIN_RBG_LEDS_BLUE, Math<uint8_t>::Lerp(m_dayColor->B(), m_nightColor->B(), p));
		}
	}
}

void FishLightProgram::OnButtonPressed(Button button)
{
	if (this->m_screenOff)
	{
		delay(5);
		analogWrite(PIN_CP_BACKLIGHT, this->m_displaySettings->backlightAsPinValue());
		this->m_screenOff = false;
		delay(5); // screen acts funky if you don't wait a bit
	}

	this->menuScreenStack->Top()->ButtonPressed(this, button);
	this->RefreshScreen();
}

void FishLightProgram::RefreshScreen()
{
	this->m_screenNeedsRefresh = true;
}

void FishLightProgram::CancelRefreshScreen()
{
	this->m_screenNeedsRefresh = false;
}

void FishLightProgram::RemoveTopScreen()
{
	this->m_popTopScreen = true;
}

void FishLightProgram::RefreshLight()
{
	restoreLight();
	updateLight();
}

void FishLightProgram::makeMainMenu()
{
	auto mainMenu = new MainMenuScreen();

	// Date & Time
	auto clockAnim = new MenuAnimation(4);
	clockAnim->SetFrame(0, clockA0);
	clockAnim->SetFrame(1, clockA1);
	clockAnim->SetFrame(2, clockA2);
	clockAnim->SetFrame(3, clockA3);
	clockAnim->Play();
	auto clockItem = new MainMenuItem("Date & Time");
	clockItem->animation = clockAnim;
	clockItem->enterAction = &OnMainMenu_DateTimeEnter;

	// Display (LCD)
	auto lcdAnim = new MenuAnimation(4);
	lcdAnim->SetFrame(0, screenA0);
	lcdAnim->SetFrame(1, screenA1);
	lcdAnim->SetFrame(2, screenA2);
	lcdAnim->SetFrame(3, screenA3);
	auto lcdItem = new MainMenuItem("Display");
	lcdItem->animation = lcdAnim;
	lcdItem->enterAction = &OnMainMenu_DisplayEnter;

	// Sunlight Settings (LCD)
	auto sunAnim = new MenuAnimation(6);
	sunAnim->SetFrame(0, sunA3);
	sunAnim->SetFrame(1, sunA4);
	sunAnim->SetFrame(2, sunA5);
	sunAnim->SetFrame(3, sunA0);
	sunAnim->SetFrame(4, sunA1);
	sunAnim->SetFrame(5, sunA2);
	sunAnim->hertz = 6;
	auto sunItem = new MainMenuItem("Day Light");
	sunItem->animation = sunAnim;
	sunItem->enterAction = &OnMainMenu_DayLightEnter;

	// Morning Settings
	auto morningAnim = new MenuAnimation(9);
	morningAnim->SetFrame(0, morningA4);
	morningAnim->SetFrame(1, morningA5);
	morningAnim->SetFrame(2, morningA6);
	morningAnim->SetFrame(3, morningA7);
	morningAnim->SetFrame(4, morningA8);
	morningAnim->SetFrame(5, morningA0);
	morningAnim->SetFrame(6, morningA1);
	morningAnim->SetFrame(7, morningA2);
	morningAnim->SetFrame(8, morningA3);
	morningAnim->hertz = 8;
	auto morningItem = new MainMenuItem("Morning");
	morningItem->animation = morningAnim;
	morningItem->enterAction = &OnMainMenu_MorningEnter;

	auto eveningAnim = new MenuAnimation(5);
	eveningAnim->SetFrame(0, eveningA0);
	eveningAnim->SetFrame(1, eveningA1);
	eveningAnim->SetFrame(2, eveningA2);
	eveningAnim->SetFrame(3, eveningA3);
	eveningAnim->SetFrame(4, eveningA4);
	eveningAnim->hertz = 6;
	auto eveningItem = new MainMenuItem("Evening");
	eveningItem->animation = eveningAnim;
	eveningItem->enterAction = &OnMainMenu_EveningEnter;

	auto nightAnim = new MenuAnimation(6);
	nightAnim->SetFrame(0, nightA2);
	nightAnim->SetFrame(1, nightA3);
	nightAnim->SetFrame(2, nightA4);
	nightAnim->SetFrame(3, eveningA4);
	nightAnim->SetFrame(4, nightA0);
	nightAnim->SetFrame(5, nightA1);
	nightAnim->hertz = 9;
	auto nightItem = new MainMenuItem("Night");
	nightItem->animation = nightAnim;
	nightItem->enterAction = &OnMainMenu_NightEnter;

	// Add items
	mainMenu->AddMenuItem(clockItem);
	mainMenu->AddMenuItem(lcdItem);
	mainMenu->AddMenuItem(morningItem);
	mainMenu->AddMenuItem(sunItem);
	mainMenu->AddMenuItem(eveningItem);
	mainMenu->AddMenuItem(nightItem);

	menuScreenStack->Push((MenuScreen*)mainMenu);
}

void FishLightProgram::initEEPROM()
{
	//EEPROM[0] = 1;
	//EEPROM[1] = 50;
	//EEPROM[2] = 1;
}

/*
enum class EEPROMAddr : int16_t
{
	Initialized = 0,
	DisplayBrightness = 1,
	DisplayIdleType = 2,
};
*/

void FishLightProgram::loadSettings()
{
	this->m_displaySettings->backlight = EEPROM[1];
	//this->m_displaySettings->idleScreen = 1;
}

// Based on the vague doc on light modes, maybe something like this
// OptimizedFishColorMode
//  -- nothing specified in doc
//===
// OptimizedPlantGrowthMode
//  -- nothing specified in doc
//===
// ShimmeringMode
//  -- not specified in doc
//===
// BasicDayMode
//  -- Okay, this one has stuff in docs, but it's all vague
// 
//===
// CloudyMode
//  -- nothing specified in doc, but I thought of some things
// rateOfClouds = 0.10
// cloudDarkness = 0.7
// avgCloudLength = 45
// 
// 
// 

// Display Screen
//----------------
//Brightness  100%
//Idle         Cat
//Confirm  ======>
//Cancel   <======

// 5-button multi-element screen concept
// Date 01/08/2018
//      XX XX XXXX
// -> You click enter to focus in on one
// -> You click enter to unfocus if focused
// -> You click up/down while focused to inc/dec value(s)
// Time 06:17:43 PM
//      XX XX XX XX
// 
// Elements would need x coordinate
// hour->x = 5;
// minute->x = 8;
// 
// Cancel   Confirm
// XXXXXX   XXXXXXX
// cancel->x = 0;
// confirm->x = 9;
// ----------------
// Date 01/08/2018
// Time 06:17:43 PM
// Cancel   Confirm
// ----------------
