// DateTime.h
#pragma once

#ifndef _DATETIME_h
#define _DATETIME_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class DateTime
{
	static bool IsLeapYear(uint32_t year);

	// Returns false for AM and true for PM
	static bool TimeOfDay(uint8_t hour);

	static String Meridiem(bool timeOfDay);
	static String Meridiem(uint8_t hour);
};



#endif

