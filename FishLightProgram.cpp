// 
// 
// 

#include "FishLightProgram.h"
#include "PinConsts.h"
#include "ButtonManager.h"
#include "MainMenuScreen.h"
#include "MenuAnimation.h"
#include "AllAnimations.h"

FishLightProgram::FishLightProgram()
{

}

FishLightProgram::~FishLightProgram()
{
	delete m_controlPanel;
	delete m_realTimeClock;
	delete m_buttonManager;
}

void FishLightProgram::Init()
{
	pinMode(PIN_BUTTONS, INPUT_PULLUP); // neccessary
	analogWrite(PIN_WHITE_LEDS, (uint8_t)(0.25f * 255));
	analogWrite(PIN_RBG_LEDS_BLUE, (uint8_t)(0.50f * 255));
	analogWrite(PIN_RBG_LEDS_RED, (uint8_t)(0.75f * 255));
	analogWrite(PIN_RBG_LEDS_GREEN, (uint8_t)(1.0f * 255));
	analogWrite(PIN_CP_BACKLIGHT, 127);

	m_controlPanel = new LiquidCrystal(
		PIN_CP_RS, PIN_CP_ENABLE,
		PIN_CP_D0, PIN_CP_D1, PIN_CP_D2, PIN_CP_D3);
	m_controlPanel->begin(16, 2);

	m_realTimeClock = new DS3231(PIN_RTC_DATA, PIN_RTC_SCLK);
	m_realTimeClock->begin();

	m_buttonManager = new ButtonManager();
	m_buttonManager->RegisterButtonsPin(PIN_BUTTONS);

	Serial.begin(9600);
	//delay(200);

	makeMainMenu();
	RefreshScreen();
}

void FishLightProgram::Update()
{
	this->m_buttonManager->Update(this);
	this->m_menuScreenStack->Top()->Update(this);

	// run last
	if (this->m_screenNeedsRefresh)
	{
		this->m_screenNeedsRefresh = false;
		m_menuScreenStack->Top()->DrawToScreen(this);
	}

	// Idling for 2 minutes causes the screen to shut off
	if (!this->m_screenOff &&
		(millis() - this->m_buttonManager->LastButtonPressTime()) > idleTimeToScreenShutoff)
	{
		analogWrite(PIN_CP_BACKLIGHT, 0);
		this->m_screenOff = true;
	}
}

void FishLightProgram::OnButtonPressed(Button button)
{
	if (this->m_screenOff)
	{
		analogWrite(PIN_CP_BACKLIGHT, 255);
		this->m_screenOff = false;
		delay(20); // screen acts funky if you don't wait a bit
	}

	this->m_menuScreenStack->Top()->ButtonPressed(this, button);
	this->RefreshScreen();
}

void FishLightProgram::RefreshScreen()
{
	this->m_screenNeedsRefresh = true;
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

	// Display (LCD)
	auto lcdAnim = new MenuAnimation(4);
	lcdAnim->SetFrame(0, screenA0);
	lcdAnim->SetFrame(1, screenA1);
	lcdAnim->SetFrame(2, screenA2);
	lcdAnim->SetFrame(3, screenA3);
	auto lcdItem = new MainMenuItem("Display");
	lcdItem->animation = lcdAnim;

	// Add items
	mainMenu->AddMenuItem(clockItem);
	mainMenu->AddMenuItem(lcdItem);

	m_menuScreenStack->Push((MenuScreen*)mainMenu);
}

// Display Screen
//----------------
//Brightness  100%
//Idle         Cat
//Confirm  ======>
//Cancel   <======

// Date & Time Screen
//Year  2018
//Month 1
//Day   8
//Hour     12
//Minute   58
//Meridiem AM
//Confirm  ==>
//Cancel   ==>

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

