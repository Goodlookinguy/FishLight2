// 
// 
// 

#include "DateTime.h"

const int16_t DateTime::s_monthsInDays[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };

int16_t DateTime::daysFromCalendarStart(int16_t year, int8_t month, int8_t day)
{
	const int16_t febFix{ month <= 2 };
	
	return 5 +
		(year - 1700) * 365 +
		(year - 1700 - febFix) / 4 -
		(year - 1700 - febFix) / 100 +
		(year - 1600 - febFix) / 400 +
		s_monthsInDays[month - 1] +
		(day - 1);
}

bool DateTime::IsLeapYear(int16_t year)
{
	return (year & 3) == 0 && ((year % 25) != 0 || (year & 15) == 0);
}

bool DateTime::TimeOfDay(uint8_t hour)
{
	return hour >= 12;
}

String DateTime::Meridiem(bool timeOfDay)
{
	if (timeOfDay)
		return "PM";
	return "AM";
}

String DateTime::Meridiem(uint8_t hour)
{
	if (hour >= 12)
		return "PM";
	return "AM";
}

int16_t DateTime::DayOfYear(int16_t year, int8_t month, int8_t day)
{
	return s_monthsInDays[month - 1] + day + 1 * (IsLeapYear(year) && month > 2);
}

int16_t DateTime::DayOfWeek(int16_t year, int8_t month, int8_t day)
{
	return daysFromCalendarStart(year, month, day) % 7;
}

int16_t DateTime::DaysInMonth(int16_t year, int8_t month)
{
	if (month == 2)
		return 28 + 1 * IsLeapYear(year);
	if (month < 8 && (month % 2) == 1 ||
		month > 7 && (month % 2) == 0)
		return 31;
	return 30;
}


