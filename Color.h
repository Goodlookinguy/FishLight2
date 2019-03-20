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

	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t w;
public:
	double rStr{ RED_STRENGTH };
	double gStr{ GREEN_STRENGTH };
	double bStr{ BLUE_STRENGTH };

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
		this->r = r;
		this->g = g;
		this->b = b;
		this->w = w;
	}

	void SetStrength(uint8_t rStr, uint8_t gStr, uint8_t bStr)
	{
		this->rStr = rStr;
		this->gStr = gStr;
		this->bStr = bStr;
	}

	uint8_t R() { return this->r * this->rStr; }
	uint8_t Red() { return this->r * this->rStr; }

	uint8_t G() { return this->g * this->gStr; }
	uint8_t Green() { return this->g * this->gStr; }

	uint8_t B() { return this->b * this->bStr; }
	uint8_t Blue() { return this->b * this->bStr; }

	uint8_t W() { return this->w; }
	uint8_t White() { return this->w; }

	void SetR(uint8_t r)
	{
		this->r = r;
	}

	void SetG(uint8_t g)
	{
		this->g = g;
	}

	void SetB(uint8_t b)
	{
		this->b = b;
	}

	void SetW(uint8_t w)
	{
		this->w = w;
	}

	static Color* PureWhite()
	{
		return new Color(0, 0, 0, 255);
	}

	static Color* AliceBlue()
	{
		return new Color(240, 248, 255, 150);
	}
};

#endif

