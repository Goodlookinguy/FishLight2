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
	static double Lerp(T start, T end, double percent);
	static double LerpOut(T start, T end, double percent);
	static double LerpInOut(T start, T end, double percent);
	static double LerpOutIn(T start, T end, double percent);
	static double QuadraticEaseIn(T start, T end, double percent);
	static double QuadraticEaseOut(T start, T end, double percent);
	static double QuadraticEaseInOut(T start, T end, double percent);
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

template <typename T>
double Math<T>::Lerp(T start, T end, double percent)
{
	return start + (end - start) * percent;
}

template <typename T>
double Math<T>::LerpOut(T start, T end, double percent)
{
	return start + (end - start) * (1.0 - percent);
}

template <typename T>
double Math<T>::LerpInOut(T start, T end, double percent)
{
	return start + (end - start) * (abs(percent - 0.5) * 2.0);
}

template <typename T>
double Math<T>::LerpOutIn(T start, T end, double percent)
{
	return start + (end - start) * (1.0 - abs(percent - 0.5) * 2.0);
}

template <typename T>
double Math<T>::QuadraticEaseIn(T start, T end, double percent)
{
	return start + (end - start) * percent * percent;
}

template <typename T>
double Math<T>::QuadraticEaseOut(T start, T end, double percent)
{
	return start + (end - start) * (1.0 - percent) * (1.0 - percent);
}

template <typename T>
double Math<T>::QuadraticEaseInOut(T start, T end, double percent)
{
	return start + (end - start) * (3.0 * percent * percent - 2.0 * percent * percent * percent);
}

#endif

