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

// Date Time Menu Events
void OnDateTime_MonthOrYearChange(FishLightProgram* program, int8_t index);

// Display Menu Events
void OnDisplay_BacklightChange(FishLightProgram* program, int8_t index);
void OnDisplay_BacklightConfirm(FishLightProgram* program, int8_t index);
void OnDisplay_BacklightCancel(FishLightProgram* program, int8_t index);

// Day Light Events
void OnDayLight_TimeStart(FishLightProgram* program, int8_t index);

#endif

