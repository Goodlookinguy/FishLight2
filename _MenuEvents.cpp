// 
// 
// 

#include "_MenuEvents.h"
#include "VerticalMenuScreen.h"
#include "VerticalMenuItemPercent.h"
#include "PinConsts.h"
#include "VerticalMenuItemCancelConfirm.h"
#include "DisplayIdleScreen.h"
#include "VerticalMenuItemOptions.h"

void OnMainMenu_DateTimeEnter(FishLightProgram* program)
{
	
}

void OnMainMenu_DisplayEnter(FishLightProgram* program)
{
	auto dateTimeMenu = new VerticalMenuScreen();

	auto lightItem = new VerticalMenuItemPercent("Backlight", 50);
	lightItem->changeAction = &OnDateTime_BacklightChange;
	lightItem->cancelAction = &OnDateTime_BacklightCancel;
	lightItem->confirmAction = &OnDateTime_BacklightConfirm;

	auto idleScreenItem = new VerticalMenuItemOptions("Idle", 2);
	idleScreenItem->AddOption("Cat", (int8_t)DisplayIdleScreen::Cat);
	idleScreenItem->AddOption("DateTime", (int8_t)DisplayIdleScreen::DateTime);

	auto ccItem = new VerticalMenuItemCancelConfirm();

	dateTimeMenu->AddMenuItem((VerticalMenuItem*)lightItem);
	dateTimeMenu->AddMenuItem((VerticalMenuItem*)idleScreenItem);
	dateTimeMenu->AddMenuItem((VerticalMenuItem*)ccItem);

	program->menuScreenStack->Push((MenuScreen*)dateTimeMenu);
	program->RefreshScreen();
}

void OnDateTime_BacklightChange(FishLightProgram* program)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	int8_t lightPercentAsInt = ((VerticalMenuItemPercent*)menu->SelectedItem())->percent;
	float p = (float)lightPercentAsInt / 100.0f;
	analogWrite(PIN_CP_BACKLIGHT, (int16_t)(p * 255.0f));
}

void OnDateTime_BacklightConfirm(FishLightProgram* program)
{
	VerticalMenuScreen* menu = (VerticalMenuScreen*)program->menuScreenStack->Top();
	const int8_t lightPercentAsInt = ((VerticalMenuItemPercent*)menu->SelectedItem())->percent;
	const float p = (float)lightPercentAsInt / 100.0f;

	program->ControlPanelSettings()->backlight = lightPercentAsInt;
	analogWrite(PIN_CP_BACKLIGHT, (int16_t)(p * 255.0f));
}

void OnDateTime_BacklightCancel(FishLightProgram* program)
{
	const float p = (float)program->ControlPanelSettings()->backlight / 100.0f;
	analogWrite(PIN_CP_BACKLIGHT, (int16_t)(p * 255.0f));
}
