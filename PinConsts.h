// PinConsts.h
#pragma once

#ifndef _PINCONSTS_h
#define _PINCONSTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#define UNO_BUILD false

#define PIN_WHITE_LEDS 11 // white strips
#define PIN_RBG_LEDS_GREEN 10 // blue of RGB strips
#define PIN_RBG_LEDS_RED 9 // red of RGB strips
#define PIN_RBG_LEDS_BLUE 6 // green of RGB strips
#define PIN_CP_BACKLIGHT 5

#define PIN_RTC_DATA SDA
#define PIN_RTC_SCLK SCL

#if (UNO_BUILD)
#define PIN_BUTTONS A0

// control panel
#define PIN_CP_RS 7
#define PIN_CP_ENABLE 4
#define PIN_CP_D0 3
#define PIN_CP_D1 2
#define PIN_CP_D2 1
#define PIN_CP_D3 0
#else
#define PIN_BUTTONS A8

// control panel
#define PIN_CP_RS A0
#define PIN_CP_ENABLE A1
#define PIN_CP_D0 A2
#define PIN_CP_D1 A3
#define PIN_CP_D2 A4
#define PIN_CP_D3 A5
#endif

#endif

