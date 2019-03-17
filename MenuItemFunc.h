// MenuItemFunc.h
#pragma once

#ifndef _MENUITEMFUNC_h
#define _MENUITEMFUNC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "FishLightProgram.h"

typedef void(* MenuItemFunc)(FishLightProgram* program, int8_t index);

#endif

