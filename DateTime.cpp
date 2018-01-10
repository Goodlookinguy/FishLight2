// 
// 
// 

#include "DateTime.h"

bool DateTime::IsLeapYear(uint32_t year)
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


