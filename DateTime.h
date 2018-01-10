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
private:
	const static int16_t s_monthsInDays[];
	static int16_t daysFromCalendarStart(int16_t year, int8_t month, int8_t day);

public:
	static bool IsLeapYear(int16_t year);

	// Returns false for AM and true for PM
	static bool TimeOfDay(uint8_t hour);

	static String Meridiem(bool timeOfDay);
	static String Meridiem(uint8_t hour);

	static int16_t DayOfYear(int16_t year, int8_t month, int8_t day);
	static int16_t DayOfWeek(int16_t year, int8_t month, int8_t day);

	static int16_t DaysInMonth(int16_t year, int8_t month);
};



#endif

