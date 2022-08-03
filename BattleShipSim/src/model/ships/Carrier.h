// Carrier.h

#ifndef _CARRIER_h
#define _CARRIER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Ship.h"

class Carrier:public Ship {

	public:
		Carrier();
		~Carrier();
};

#endif

