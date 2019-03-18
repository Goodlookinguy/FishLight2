// Color.h
#pragma once

#ifndef _COLOR_h
#define _COLOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Math.h"

class Color
{
	const double RED_STRENGTH{ 1.0 };
	const double GREEN_STRENGTH{ 0.6 };
	const double BLUE_STRENGTH{ 0.3 };
public:
	double rStr = RED_STRENGTH;
	double gStr = GREEN_STRENGTH;
	double bStr = BLUE_STRENGTH;
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t w;

	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
	{
		Set(r, g, b, w);
	}

	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w, double redStrength, double greenStrength, double blueStrength)
	{
		rStr = redStrength;
		gStr = greenStrength;
		bStr = blueStrength;
		Set(r, g, b, w);
	}

	void Set(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
	{
		SetR(r);
		SetG(g);
		SetB(b);
		this->w = w;
	}

	void SetR(uint8_t r)
	{
		this->r = r * rStr;
	}

	void SetG(uint8_t g)
	{
		this->g = g * gStr;
	}

	void SetB(uint8_t b)
	{
		this->b = b * bStr;
	}

	static Color* White()
	{
		return new Color(0, 0, 0, 255);
	}

	static Color* AliceBlue()
	{
		return new Color(240, 248, 255, 150);
	}
};

#endif

