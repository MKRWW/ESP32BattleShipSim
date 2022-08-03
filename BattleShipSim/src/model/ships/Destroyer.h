// Destroyer.h

#ifndef _DESTROYER_h
#define _DESTROYER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Ship.h"

class Destroyer :public Ship {

	public:
	Destroyer();
	~Destroyer();
};

#endif

