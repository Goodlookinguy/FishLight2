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

	m_dayColor = new Color(0, 128, 255, 170);
	m_nightColor = new Color(0, 20, 20, 0);

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
	
	const int8_t alreadyInit = EEPROM[0];
	const bool firstRun = alreadyInit == 0;

	if (firstRun)
		initEEPROM();

	//loadSettings();
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

void FishLightProgram::updateLight()
{
	bool bfalse = false;
	auto rtc = this->m_realTimeClock;
	uint8_t hour = rtc->getHour(bfalse, bfalse);
	uint8_t min = rtc->getMinute();
	uint8_t sec = rtc->getSecond();
	
	if ((hour >= 6 && hour <= 7) || (hour >= 20 && hour <= 22))
	{
		// derp
		if (hour == 6 || (hour == 7 && min <= 30 && sec <= 5))
		{
			double p = Math<double>::Clamp((((hour - 6) * 60 * 60) + min * 60 + sec) / (60.0 * 90.0), 0.0, 1.0);
			analogWrite(PIN_WHITE_LEDS, Math<uint8_t>::Lerp(m_nightColor->w, m_dayColor->w, p));
			analogWrite(PIN_RBG_LEDS_RED, Math<uint8_t>::Lerp(m_nightColor->r, m_dayColor->r, p));
			analogWrite(PIN_RBG_LEDS_GREEN, Math<uint8_t>::Lerp(m_nightColor->g, m_dayColor->g, p));
			analogWrite(PIN_RBG_LEDS_BLUE, Math<uint8_t>::Lerp(m_nightColor->b, m_dayColor->b, p));
		}
		else if ((hour == 20 && min >= 30) || hour == 21 || (hour == 22 && min == 0 && sec <= 5))
		{
			double p = Math<double>::Clamp((((hour - 20) * 60 * 60) + (min - 30) * 60 + sec) / (60.0 * 90.0), 0.0, 1.0);
			analogWrite(PIN_WHITE_LEDS, Math<uint8_t>::Lerp(m_dayColor->w, m_nightColor->w, p));
			analogWrite(PIN_RBG_LEDS_RED, Math<uint8_t>::Lerp(m_dayColor->r, m_nightColor->r, p));
			analogWrite(PIN_RBG_LEDS_GREEN, Math<uint8_t>::Lerp(m_dayColor->g, m_nightColor->g, p));
			analogWrite(PIN_RBG_LEDS_BLUE, Math<uint8_t>::Lerp(m_dayColor->b, m_nightColor->b, p));
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

	auto colorAnim = new MenuAnimation(10);
	colorAnim->SetFrame(0, colorA7);
	colorAnim->SetFrame(1, colorA0);
	colorAnim->SetFrame(2, colorA1);
	colorAnim->SetFrame(3, colorA2);
	colorAnim->SetFrame(4, colorA3);
	colorAnim->SetFrame(5, colorA4);
	colorAnim->SetFrame(6, colorA5);
	colorAnim->SetFrame(7, colorA6);
	colorAnim->SetFrame(8, colorA7);
	colorAnim->SetFrame(9, colorA7);
	colorAnim->hertz = 8;
	auto colorItem = new MainMenuItem("Color Balance");
	colorItem->animation = colorAnim;

	// Add items
	mainMenu->AddMenuItem(clockItem);
	mainMenu->AddMenuItem(lcdItem);
	mainMenu->AddMenuItem(sunItem);
	mainMenu->AddMenuItem(colorItem);

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
