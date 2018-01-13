// Math.h

#ifndef _MATH_h
#define _MATH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

template <typename T>
class Math
{
public:
	static T Clamp(T value, T low, T high);
};

template <typename T>
T Math<T>::Clamp(T value, T low, T high)
{
	if (value < low)
		return low;
	if (value > high)
		return high;
	return value;
}

#endif

