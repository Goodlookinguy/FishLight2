// _MenuEvents.h
#pragma once

#ifndef __MENUEVENTS_h
#define __MENUEVENTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include "FishLightProgram.h"

// Main Menu Events
void OnMainMenu_DateTimeEnter(FishLightProgram* program);
void OnMainMenu_DisplayEnter(FishLightProgram* program);

// Date Time Menu Events
void OnDateTime_BacklightChange(FishLightProgram* program);
void OnDateTime_BacklightConfirm(FishLightProgram* program);
void OnDateTime_BacklightCancel(FishLightProgram* program);

#endif

