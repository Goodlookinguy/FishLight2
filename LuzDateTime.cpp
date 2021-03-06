// 
// 
// 

#include "LuzDateTime.h"

const int16_t LuzDateTime::s_monthsInDays[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };

int16_t LuzDateTime::daysFromCalendarStart(int16_t year, int8_t month, int8_t day)
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

bool LuzDateTime::IsLeapYear(int16_t year)
{
	return (year & 3) == 0 && ((year % 25) != 0 || (year & 15) == 0);
}

bool LuzDateTime::TimeOfDay(uint8_t hour)
{
	return hour >= 12;
}



String LuzDateTime::Meridiem(bool timeOfDay)
{
	if (timeOfDay)
		return "PM";
	return "AM";
}

String LuzDateTime::Meridiem(uint8_t hour)
{
	if (hour >= 12)
		return "PM";
	return "AM";
}

int16_t LuzDateTime::DayOfYear(int16_t year, int8_t month, int8_t day)
{
	return s_monthsInDays[month - 1] + day + 1 * (IsLeapYear(year) && month > 2);
}

int16_t LuzDateTime::DayOfWeek(int16_t year, int8_t month, int8_t day)
{
	return daysFromCalendarStart(year, month, day) % 7;
}

int16_t LuzDateTime::DaysInMonth(int16_t year, int8_t month)
{
	if (month == 2)
		return 28 + 1 * IsLeapYear(year);
	if (month < 8 && (month % 2) == 1 ||
		month > 7 && (month % 2) == 0)
		return 31;
	return 30;
}

int16_t LuzDateTime::StandardTo24Hour(int16_t hour, String timeOfDay)
{
	if (hour == 12)
		hour = 0;

	if (timeOfDay == "AM")
	{
		return hour;
	}

	return hour + 12;
}

int16_t LuzDateTime::MilitaryTo12Hour(int16_t hour)
{
	auto stdHour = hour % 12;
	if (stdHour == 0)
		return 12;
	return stdHour;
}

uint64_t LuzDateTime::ToUnixTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hours, uint8_t minutes, uint8_t seconds)
{
	const uint64_t Jan112019 = 1546300800;
	auto yearDiff = year - 2019;
	auto monDiff = month - 1;
	auto dayDiff = day - 1;
	int8_t extraDays = 0;

	for (int16_t i = 2019; i <= year; ++i)
	{
		if (month > 2)
		{
			if (IsLeapYear(i))
				++extraDays;
		}
	}

	uint64_t unixTime = Jan112019;
	unixTime += yearDiff * 365UL * 24UL * 60UL * 60UL;
	unixTime += s_monthsInDays[monDiff] * 24UL * 60UL * 60UL;
	unixTime += dayDiff * 24UL * 60UL * 60UL;
	unixTime += hours * 60UL * 60UL;
	unixTime += minutes * 60UL;
	unixTime += seconds;

	return unixTime;
}


