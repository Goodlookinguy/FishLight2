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
#include "DateTime.h"

//TODO: Retrieve values from EEPROM to load up default values otherwise it's like constantly resetting

#define DATETIMEMENU_YEAR 0
#define DATETIMEMENU_MONTH 1
#define DATETIMEMENU_DAY 2
#define DATETIMEMENU_HOUR 3
#define DATETIMEMENU_MINUTE 4
#define DATETIMEMENUs_MERIDIEM 5

// Date & Time Screen
//Year  2018
//Month 1
//Day   8
//Hour     12
//Minute   58
//Meridiem AM
//Cancel  Confirm
void OnMainMenu_DateTimeEnter(FishLightProgram* program)
{
	auto dateTimeMenu = new VerticalMenuScreen();

	auto yearItem = new VerticalMenuItemIntRange("Year ", 2018, 2018, 4000);
	yearItem->changeAction = &OnDateTime_MonthOrYearChange;

	auto monthItem = new VerticalMenuItemIntRange("Month", 1, 1, 12);
	monthItem->changeAction = &OnDateTime_MonthOrYearChange;

	auto dayItem = new VerticalMenuItemIntRange("Day  ", 1, 1, 31);

	auto hourItem = new VerticalMenuItemIntRange("Hour    ", 1, 1, 12);

	auto minuteItem = new VerticalMenuItemIntRange("Minute  ", 0, 0, 59);

	auto meridiemItem = new VerticalMenuItemOptions("Meridiem", 2);
	meridiemItem->AddOption("AM", 0);
	meridiemItem->AddOption("PM", 1);
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

void OnMainMenu_DisplayEnter(FishLightProgram* program)
{
	auto displayMenu = new VerticalMenuScreen();

	auto lightItem = new VerticalMenuItemPercent("Backlight", 50);
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

void OnDateTime_MonthOrYearChange(FishLightProgram* program)
{
	auto menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	auto yearItem = (VerticalMenuItemIntRange*)menu->Items()->Get(DATETIMEMENU_YEAR);
	auto monthItem = (VerticalMenuItemIntRange*)menu->Items()->Get(DATETIMEMENU_MONTH);
	auto dayItem = (VerticalMenuItemIntRange*)menu->Items()->Get(DATETIMEMENU_DAY);

	dayItem->Max( DateTime::DaysInMonth(yearItem->Value(), monthItem->Value()) );
}

void OnDisplay_BacklightChange(FishLightProgram* program)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	int8_t lightPercentAsInt = ((VerticalMenuItemPercent*)menu->SelectedItem())->percent;
	float p = (float)lightPercentAsInt / 100.0f;
	analogWrite(PIN_CP_BACKLIGHT, (int16_t)(p * 255.0f));
}

void OnDisplay_BacklightConfirm(FishLightProgram* program)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	const int8_t lightPercentAsInt = ((VerticalMenuItemPercent*)menu->SelectedItem())->percent;
	const float p = (float)lightPercentAsInt / 100.0f;

	program->ControlPanelSettings()->backlight = lightPercentAsInt;
	analogWrite(PIN_CP_BACKLIGHT, (int16_t)(p * 255.0f));
}

void OnDisplay_BacklightCancel(FishLightProgram* program)
{
	const float p = (float)program->ControlPanelSettings()->backlight / 100.0f;
	analogWrite(PIN_CP_BACKLIGHT, (int16_t)(p * 255.0f));
}
