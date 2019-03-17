// PinConsts.h
#pragma once

#ifndef _PINCONSTS_h
#define _PINCONSTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BuildConsts.h"

/////////////////////////////////
// PINS MAPPING

#if (UNO_BUILD)
#define PIN_WHITE_LEDS 11 // white strips
#define PIN_RBG_LEDS_GREEN 10 // blue of RGB strips
#define PIN_RBG_LEDS_RED 9 // red of RGB strips
#define PIN_RBG_LEDS_BLUE 6 // green of RGB strips
#define PIN_CP_BACKLIGHT 5

#define PIN_RTC_DATA SDA
#define PIN_RTC_SCLK SCL

#define PIN_BUTTONS A0

// control panel
#define PIN_CP_RS 7
#define PIN_CP_ENABLE 4
#define PIN_CP_D0 3
#define PIN_CP_D1 2
// pin 0 & 1 are off limits, he screwed up UNO version
#define PIN_CP_D2 1 
#define PIN_CP_D3 0
#elif (FIVE_BUTTON_BUILD)
#define PIN_WHITE_LEDS 5 // white strips
#define PIN_RBG_LEDS_GREEN 6 // blue of RGB strips
#define PIN_RBG_LEDS_RED 9 // red of RGB strips
#define PIN_RBG_LEDS_BLUE 10 // green of RGB strips
#define PIN_CP_BACKLIGHT 11

#define PIN_RTC_DATA PIN_WIRE_SDA
#define PIN_RTC_SCLK PIN_WIRE_SCL

#define PIN_BUTTONS A8

// control panel
#define PIN_CP_RS PIN_A5
#define PIN_CP_ENABLE PIN_A4
#define PIN_CP_D0 PIN_A3
#define PIN_CP_D1 PIN_A2
#define PIN_CP_D2 PIN_A1
#define PIN_CP_D3 PIN_A0
#else
#define PIN_WHITE_LEDS 11 // white strips
#define PIN_RBG_LEDS_GREEN 10 // blue of RGB strips
#define PIN_RBG_LEDS_RED 9 // red of RGB strips
#define PIN_RBG_LEDS_BLUE 6 // green of RGB strips
#define PIN_CP_BACKLIGHT 5

#define PIN_RTC_DATA PIN_WIRE_SDA
#define PIN_RTC_SCLK PIN_WIRE_SCL

#define PIN_BUTTONS PIN_A8

// control panel
#define PIN_CP_RS PIN_A0
#define PIN_CP_ENABLE PIN_A1
#define PIN_CP_D0 PIN_A2
#define PIN_CP_D1 PIN_A3
#define PIN_CP_D2 PIN_A4
#define PIN_CP_D3 PIN_A5
#endif

#endif
