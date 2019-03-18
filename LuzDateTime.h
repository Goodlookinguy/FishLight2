// DateTime.h
#pragma once

#ifndef _LUZDATETIME_h
#define _LUZDATETIME_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class LuzDateTime
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

	static int16_t StandardTo24Hour(int16_t hour, String timeOfDay);
	static int16_t MilitaryTo12Hour(int16_t hour);

	static uint64_t ToUnixTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hours, uint8_t minutes, uint8_t seconds);
};



#endif

