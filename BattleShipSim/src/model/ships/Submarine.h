// Submarine.h

#ifndef _SUBMARINE_h
#define _SUBMARINE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Ship.h"

class Submarine :public Ship {

	public:
	Submarine();
	~Submarine();
};

#endif

