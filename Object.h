// Object.h

#ifndef _OBJECT_h
#define _OBJECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Object
{
public:
	//Object() {}
	virtual ~Object() {}
};

#endif

