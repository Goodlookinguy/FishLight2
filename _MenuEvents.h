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
void OnColorMenu_RedChange(FishLightProgram* program, int8_t index);
void OnColorMenu_RedCancel(FishLightProgram* program, int8_t index);
void OnColorMenu_RedConfirm(FishLightProgram* program, int8_t index);
void OnColorMenu_RedStrengthChange(FishLightProgram* program, int8_t index);
void OnColorMenu_RedStrengthCancel(FishLightProgram* program, int8_t index);
void OnColorMenu_RedStrengthConfirm(FishLightProgram* program, int8_t index);
void OnColorMenu_GreenChange(FishLightProgram* program, int8_t index);
void OnColorMenu_GreenCancel(FishLightProgram* program, int8_t index);
void OnColorMenu_GreenConfirm(FishLightProgram* program, int8_t index);
void OnColorMenu_GreenStrengthChange(FishLightProgram* program, int8_t index);
void OnColorMenu_GreenStrengthCancel(FishLightProgram* program, int8_t index);
void OnColorMenu_GreenStrengthConfirm(FishLightProgram* program, int8_t index);
void OnColorMenu_BlueChange(FishLightProgram* program, int8_t index);
void OnColorMenu_BlueCancel(FishLightProgram* program, int8_t index);
void OnColorMenu_BlueConfirm(FishLightProgram* program, int8_t index);
void OnColorMenu_BlueStrengthChange(FishLightProgram* program, int8_t index);
void OnColorMenu_BlueStrengthCancel(FishLightProgram* program, int8_t index);
void OnColorMenu_BlueStrengthConfirm(FishLightProgram* program, int8_t index);
void OnColorMenu_WhiteChange(FishLightProgram* program, int8_t index);
void OnColorMenu_WhiteCancel(FishLightProgram* program, int8_t index);
void OnColorMenu_WhiteConfirm(FishLightProgram* program, int8_t index);

#endif

