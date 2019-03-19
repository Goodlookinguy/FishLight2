// _MenuEvents.h
#pragma once

#ifndef __MENUEVENTS_h
#define __MENUEVENTS_h

//#if defined(ARDUINO) && ARDUINO >= 100
//	#include "Arduino.h"
//#else
//	#include "WProgram.h"
//#endif
#include "FishLightProgram.h"

// Main Menu Events
void OnMainMenu_DateTimeEnter(FishLightProgram* program, int8_t index);
void OnMainMenu_DisplayEnter(FishLightProgram* program, int8_t index);
void OnMainMenu_DayLightEnter(FishLightProgram* program, int8_t index);
void OnMainMenu_ColorBalanceEnter(FishLightProgram* program, int8_t index);

// Date Time Menu Events
void OnDateTime_YearChange(FishLightProgram* program, int8_t index);
void OnDateTime_MonthChange(FishLightProgram* program, int8_t index);
void OnDateTime_DayChange(FishLightProgram* program, int8_t index);
void OnDateTime_HourOrMeridiemChange(FishLightProgram* program, int8_t index);
void OnDateTime_MinuteChange(FishLightProgram* program, int8_t index);

// Display Menu Events
void OnDisplay_BacklightChange(FishLightProgram* program, int8_t index);
void OnDisplay_BacklightConfirm(FishLightProgram* program, int8_t index);
void OnDisplay_BacklightCancel(FishLightProgram* program, int8_t index);

// Day Light Events
void OnDayLight_TimeStart(FishLightProgram* program, int8_t index);
void OnDayLight_RedChange(FishLightProgram* program, int8_t index);
void OnDayLight_RedStrengthChange(FishLightProgram* program, int8_t index);
void OnDayLight_GreenChange(FishLightProgram* program, int8_t index);
void OnDayLight_GreenStrengthChange(FishLightProgram* program, int8_t index);
void OnDayLight_BlueChange(FishLightProgram* program, int8_t index);
void OnDayLight_BlueStrengthChange(FishLightProgram* program, int8_t index);

#endif

