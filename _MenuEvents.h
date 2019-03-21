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
#include "LightMenuTag.h"

// Main Menu Events
void OnMainMenu_DateTimeEnter(FishLightProgram* program, int8_t index);
void OnMainMenu_DisplayEnter(FishLightProgram* program, int8_t index);
void OnMainMenu_MorningEnter(FishLightProgram* program, int8_t index);
void OnMainMenu_DayLightEnter(FishLightProgram* program, int8_t index);

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

// Light Events
void CreateLightColorMenu(FishLightProgram* program, LightMenuTag* tag);
void OnDayLight_TimeStart(FishLightProgram* program, int8_t index);
void OnRedChange(FishLightProgram* program, int8_t index);
void OnRedStrengthChange(FishLightProgram* program, int8_t index);
void OnGreenChange(FishLightProgram* program, int8_t index);
void OnGreenStrengthChange(FishLightProgram* program, int8_t index);
void OnBlueChange(FishLightProgram* program, int8_t index);
void OnBlueStrengthChange(FishLightProgram* program, int8_t index);
void OnWhiteChange(FishLightProgram* program, int8_t index);

#endif

