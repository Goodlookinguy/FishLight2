// 
// 
// 

#include "_MenuEvents.h"
#include "VerticalMenuScreen.h"
#include "VerticalMenuItemPercent.h"
#include "VerticalMenuItemIntRange.h"
#include "PinConsts.h"
#include "VerticalMenuItemCancelConfirm.h"
#include "DisplayIdleScreen.h"
#include "VerticalMenuItemOptions.h"
#include "LuzDateTime.h"
#include "Object.h"
#include "LightMenuTag.h"

//TODO: Retrieve values from EEPROM to load up default values otherwise it's like constantly resetting

#define DATETIMEMENU_YEAR 0
#define DATETIMEMENU_MONTH 1
#define DATETIMEMENU_DAY 2
#define DATETIMEMENU_HOUR 3
#define DATETIMEMENU_MINUTE 4
#define DATETIMEMENU_MERIDIEM 5

// Date & Time Screen
//Year  2018
//Month 1
//Day   8
//Hour     12
//Minute   58
//Meridiem AM
//Cancel  Confirm
void OnMainMenu_DateTimeEnter(FishLightProgram* program, int8_t index)
{
	bool bfalse = false; // stupid
	// DS3231 programmer is a shitty programmer
	auto rtc = program->RealTimeClock();

	auto dateTimeMenu = new VerticalMenuScreen();

	auto yearItem = new VerticalMenuItemIntRange("Year ", rtc->getYear() + 2000, 2018, 4000);
	yearItem->changeAction = &OnDateTime_YearChange;

	auto monthItem = new VerticalMenuItemIntRange("Month", rtc->getMonth(bfalse), 1, 12);
	monthItem->changeAction = &OnDateTime_MonthChange;

	auto dayItem = new VerticalMenuItemIntRange("Day  ", rtc->getDate(), 1, 31);
	dayItem->changeAction = &OnDateTime_DayChange;

	auto hourItem = new VerticalMenuItemIntRange("Hour    ", LuzDateTime::MilitaryTo12Hour(rtc->getHour(bfalse, bfalse)), 1, 12);
	hourItem->changeAction = &OnDateTime_HourOrMeridiemChange;

	auto minuteItem = new VerticalMenuItemIntRange("Minute  ", rtc->getMinute(), 0, 59);
	minuteItem->changeAction = &OnDateTime_MinuteChange;
	
	auto meridiemItem = new VerticalMenuItemOptions("Meridiem", 2);
	meridiemItem->changeAction = &OnDateTime_HourOrMeridiemChange;
	meridiemItem->AddOption("AM", 0);
	meridiemItem->AddOption("PM", 1);
	if (rtc->getHour(bfalse, bfalse) > 12)
		meridiemItem->ValueIndex(1);
	//lightItem->changeAction = &OnDisplay_BacklightChange;
	//lightItem->cancelAction = &OnDisplay_BacklightCancel;
	//lightItem->confirmAction = &OnDisplay_BacklightConfirm;

	//auto idleScreenItem = new VerticalMenuItemOptions("Idle", 2);
	//idleScreenItem->AddOption("Cat", (int8_t)DisplayIdleScreen::Cat);
	//idleScreenItem->AddOption("DateTime", (int8_t)DisplayIdleScreen::DateTime);

	auto ccItem = new VerticalMenuItemCancelConfirm();

	dateTimeMenu->AddMenuItem((VerticalMenuItem*)yearItem);
	dateTimeMenu->AddMenuItem((VerticalMenuItem*)monthItem);
	dateTimeMenu->AddMenuItem((VerticalMenuItem*)dayItem);
	dateTimeMenu->AddMenuItem((VerticalMenuItem*)hourItem);
	dateTimeMenu->AddMenuItem((VerticalMenuItem*)minuteItem);
	dateTimeMenu->AddMenuItem((VerticalMenuItem*)meridiemItem);
	dateTimeMenu->AddMenuItem((VerticalMenuItem*)ccItem);

	program->menuScreenStack->Push((MenuScreen*)dateTimeMenu);
	program->RefreshScreen();
}

void OnMainMenu_DisplayEnter(FishLightProgram* program, int8_t index)
{
	auto displayMenu = new VerticalMenuScreen();

	auto lightItem = new VerticalMenuItemPercent("Backlight", program->ControlPanelSettings()->backlight);
	lightItem->changeAction = &OnDisplay_BacklightChange;
	lightItem->cancelAction = &OnDisplay_BacklightCancel;
	lightItem->confirmAction = &OnDisplay_BacklightConfirm;

	auto idleScreenItem = new VerticalMenuItemOptions("Idle", 2);
	idleScreenItem->AddOption("Cat", (int8_t)DisplayIdleScreen::Cat);
	idleScreenItem->AddOption("DateTime", (int8_t)DisplayIdleScreen::DateTime);

	auto ccItem = new VerticalMenuItemCancelConfirm();

	displayMenu->AddMenuItem((VerticalMenuItem*)lightItem);
	displayMenu->AddMenuItem((VerticalMenuItem*)idleScreenItem);
	displayMenu->AddMenuItem((VerticalMenuItem*)ccItem);

	program->menuScreenStack->Push((MenuScreen*)displayMenu);
	program->RefreshScreen();
}

void OnMainMenu_MorningEnter(FishLightProgram* program, int8_t index)
{
	auto tag = new LightMenuTag();
	tag->color = program->MorningColor();
	tag->eepromAddress = 64;
	CreateLightColorMenu(program, tag);
}

void OnMainMenu_DayLightEnter(FishLightProgram* program, int8_t index)
{
	auto tag = new LightMenuTag();
	tag->color = program->DayColor();
	tag->eepromAddress = 80;
	CreateLightColorMenu(program, tag);
}

void OnMainMenu_EveningEnter(FishLightProgram * program, int8_t index)
{
	auto tag = new LightMenuTag();
	tag->color = program->EveningColor();
	tag->eepromAddress = 96;
	CreateLightColorMenu(program, tag);
}

void OnMainMenu_NightEnter(FishLightProgram * program, int8_t index)
{
	auto tag = new LightMenuTag();
	tag->color = program->NightColor();
	tag->eepromAddress = 112;
	CreateLightColorMenu(program, tag);
}

void CreateLightColorMenu(FishLightProgram* program, LightMenuTag* tag)
{
	auto dayLightMenu = new VerticalMenuScreen();
	dayLightMenu->tag = (Object*)tag;

	//auto timeStartHourItem = new VerticalMenuItemIntRange("Hour Start", 0, 0, 23);
	//auto timeStartMinItem = new VerticalMenuItemIntRange("Min Start", 0, 0, 59);
	auto redItem = new VerticalMenuItemIntRange("Red", tag->color->R(), 0, 255);
	redItem->changeAction = &OnColorMenu_RedChange;

	auto redStrItem = new VerticalMenuItemPercent("Red Str", tag->color->rStr * 100, 1);
	redStrItem->changeAction = &OnColorMenu_RedStrengthChange;

	auto greenItem = new VerticalMenuItemIntRange("Green", tag->color->G(), 0, 255);
	greenItem->changeAction = &OnColorMenu_GreenChange;

	auto greenStrItem = new VerticalMenuItemPercent("Green Str", tag->color->gStr * 100, 1);
	greenStrItem->changeAction = &OnColorMenu_GreenStrengthChange;

	auto blueItem = new VerticalMenuItemIntRange("Blue", tag->color->B(), 0, 255);
	blueItem->changeAction = &OnColorMenu_BlueChange;

	auto blueStrItem = new VerticalMenuItemPercent("Blue Str", tag->color->bStr * 100, 1);
	blueStrItem->changeAction = &OnColorMenu_BlueStrengthChange;

	auto whiteItem = new VerticalMenuItemIntRange("White", tag->color->W(), 0, 255);
	whiteItem->changeAction = &OnColorMenu_WhiteChange;
	whiteItem->cancelAction = &OnColorMenu_WhiteCancel;
	whiteItem->confirmAction = &OnColorMenu_WhiteConfirm;

	auto ccItem = new VerticalMenuItemCancelConfirm();

	dayLightMenu->AddMenuItem((VerticalMenuItem*)redItem);
	dayLightMenu->AddMenuItem((VerticalMenuItem*)redStrItem);
	dayLightMenu->AddMenuItem((VerticalMenuItem*)greenItem);
	dayLightMenu->AddMenuItem((VerticalMenuItem*)greenStrItem);
	dayLightMenu->AddMenuItem((VerticalMenuItem*)blueItem);
	dayLightMenu->AddMenuItem((VerticalMenuItem*)blueStrItem);
	dayLightMenu->AddMenuItem((VerticalMenuItem*)whiteItem);
	dayLightMenu->AddMenuItem((VerticalMenuItem*)ccItem);

	program->menuScreenStack->Push((MenuScreen*)dayLightMenu);
	program->RefreshScreen();
}

void OnDateTime_YearChange(FishLightProgram* program, int8_t index)
{
	auto menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto yearItem = (VerticalMenuItemIntRange*)menu->Items()->Get(DATETIMEMENU_YEAR);

	program->RealTimeClock()->setYear(yearItem->Value() - 2000);
}

void OnDateTime_MonthChange(FishLightProgram* program, int8_t index)
{
	auto menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto monthItem = (VerticalMenuItemIntRange*)menu->Items()->Get(DATETIMEMENU_MONTH);
	program->RealTimeClock()->setMonth(monthItem->Value());
}

void OnDateTime_DayChange(FishLightProgram* program, int8_t index)
{
	bool stupid = false;
	auto rtc = program->RealTimeClock();
	auto menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto dayItem = (VerticalMenuItemIntRange*)menu->Items()->Get(DATETIMEMENU_DAY);
	dayItem->Max(LuzDateTime::DaysInMonth(rtc->getYear() + 2000, rtc->getMonth(stupid)));
	rtc->setDate(dayItem->Value());
}

void OnDateTime_HourOrMeridiemChange(FishLightProgram* program, int8_t index)
{
	auto menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto hourItem = (VerticalMenuItemIntRange*)menu->Items()->Get(DATETIMEMENU_HOUR);
	auto merItem = (VerticalMenuItemOptions*)menu->Items()->Get(DATETIMEMENU_MERIDIEM);
	program->RealTimeClock()->setHour(LuzDateTime::StandardTo24Hour(hourItem->Value(), merItem->Value()));
}

void OnDateTime_MinuteChange(FishLightProgram* program, int8_t index)
{
	auto menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto minItem = (VerticalMenuItemIntRange*)menu->Items()->Get(DATETIMEMENU_MINUTE);
	program->RealTimeClock()->setMinute(minItem->Value());
}

void OnDisplay_BacklightChange(FishLightProgram* program, int8_t index)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	int8_t lightPercentAsInt = ((VerticalMenuItemPercent*)menu->SelectedItem())->percent;
	int16_t p = (int16_t)(((float)lightPercentAsInt / 100.0f) * 255.0f);
	analogWrite(PIN_CP_BACKLIGHT, p);
}

void OnDisplay_BacklightConfirm(FishLightProgram* program, int8_t index)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	const int8_t lightPercentAsInt = ((VerticalMenuItemPercent*)menu->Items()->Get(index))->percent;
	auto cpSettings = program->ControlPanelSettings();
	
	cpSettings->backlight = lightPercentAsInt;
	analogWrite(PIN_CP_BACKLIGHT, cpSettings->backlightAsPinValue());
}

void OnDisplay_BacklightCancel(FishLightProgram* program, int8_t index)
{
	analogWrite(PIN_CP_BACKLIGHT, program->ControlPanelSettings()->backlightAsPinValue());
}

void OnColorMenu_RedChange(FishLightProgram* program, int8_t index)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto item = (VerticalMenuItemIntRange*)menu->Items()->Get(index);
	((LightMenuTag*)menu->tag)->color->SetR(item->Value());
	program->RefreshLight();
}

void OnColorMenu_RedCancel(FishLightProgram * program, int8_t index)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto item = (VerticalMenuItemIntRange*)menu->Items()->Get(index);
	((LightMenuTag*)menu->tag)->color->SetR(item->InitValue());
	program->RefreshLight();
}

void OnColorMenu_RedConfirm(FishLightProgram * program, int8_t index)
{
}

void OnColorMenu_RedStrengthChange(FishLightProgram* program, int8_t index)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto item = (VerticalMenuItemPercent*)menu->Items()->Get(index);
	((LightMenuTag*)menu->tag)->color->rStr = item->percent / 100.0;
	program->RefreshLight();
}

void OnColorMenu_RedStrengthCancel(FishLightProgram * program, int8_t index)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto item = (VerticalMenuItemPercent*)menu->Items()->Get(index);
	((LightMenuTag*)menu->tag)->color->rStr = item->initPercent / 100.0;
	program->RefreshLight();
}

void OnColorMenu_RedStrengthConfirm(FishLightProgram * program, int8_t index)
{
}

void OnColorMenu_GreenChange(FishLightProgram* program, int8_t index)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto item = (VerticalMenuItemIntRange*)menu->Items()->Get(index);
	((LightMenuTag*)menu->tag)->color->SetG(item->Value());
	program->RefreshLight();
}

void OnColorMenu_GreenCancel(FishLightProgram * program, int8_t index)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto item = (VerticalMenuItemIntRange*)menu->Items()->Get(index);
	((LightMenuTag*)menu->tag)->color->SetG(item->InitValue());
	program->RefreshLight();
}

void OnColorMenu_GreenConfirm(FishLightProgram * program, int8_t index)
{
}

void OnColorMenu_GreenStrengthChange(FishLightProgram* program, int8_t index)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto item = (VerticalMenuItemPercent*)menu->Items()->Get(index);
	((LightMenuTag*)menu->tag)->color->gStr = item->percent / 100.0;
	program->RefreshLight();
}

void OnColorMenu_GreenStrengthCancel(FishLightProgram * program, int8_t index)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto item = (VerticalMenuItemPercent*)menu->Items()->Get(index);
	((LightMenuTag*)menu->tag)->color->gStr = item->initPercent / 100.0;
	program->RefreshLight();
}

void OnColorMenu_GreenStrengthConfirm(FishLightProgram * program, int8_t index)
{
}

void OnColorMenu_BlueChange(FishLightProgram* program, int8_t index)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto item = (VerticalMenuItemIntRange*)menu->Items()->Get(index);
	((LightMenuTag*)menu->tag)->color->SetB(item->Value());
	program->RefreshLight();
}

void OnColorMenu_BlueCancel(FishLightProgram * program, int8_t index)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto item = (VerticalMenuItemIntRange*)menu->Items()->Get(index);
	((LightMenuTag*)menu->tag)->color->SetB(item->InitValue());
	program->RefreshLight();
}

void OnColorMenu_BlueConfirm(FishLightProgram * program, int8_t index)
{
}

void OnColorMenu_BlueStrengthChange(FishLightProgram* program, int8_t index)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto item = (VerticalMenuItemPercent*)menu->Items()->Get(index);
	((LightMenuTag*)menu->tag)->color->bStr = item->percent / 100.0;
	program->RefreshLight();
}

void OnColorMenu_BlueStrengthCancel(FishLightProgram * program, int8_t index)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto item = (VerticalMenuItemPercent*)menu->Items()->Get(index);
	((LightMenuTag*)menu->tag)->color->bStr = item->initPercent / 100.0;
	program->RefreshLight();
}

void OnColorMenu_BlueStrengthConfirm(FishLightProgram * program, int8_t index)
{
}

void OnColorMenu_WhiteChange(FishLightProgram* program, int8_t index)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto item = (VerticalMenuItemIntRange*)menu->Items()->Get(index);
	((LightMenuTag*)menu->tag)->color->SetW(item->Value());
	program->RefreshLight();
}

void OnColorMenu_WhiteCancel(FishLightProgram* program, int8_t index)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto item = (VerticalMenuItemIntRange*)menu->Items()->Get(index);
	((LightMenuTag*)menu->tag)->color->SetW(item->InitValue());
	program->RefreshLight();
}

void OnColorMenu_WhiteConfirm(FishLightProgram* program, int8_t index)
{
	//VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	//auto item = (VerticalMenuItemIntRange*)menu->Items()->Get(index);
	// write to EEPROM
}
