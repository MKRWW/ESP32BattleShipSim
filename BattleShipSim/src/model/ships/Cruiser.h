// Cruiser.h

#ifndef _CRUISER_h
#define _CRUISER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Ship.h"

class Cruiser :public Ship {

	public:
	Cruiser();
	~Cruiser();
};

#endif

