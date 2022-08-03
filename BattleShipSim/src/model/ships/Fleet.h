// Fleet.h

#ifndef _FLEET_h
#define _FLEET_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class Ship;

class Fleet {

	public:
		Fleet(int aSize = 5);
		~Fleet();
		int size();
		Ship* const shipAt(int aIndex);
		bool isDestroyed();
	protected:
	private:

	public:
	protected:
	private:
		Ship** m_fleet;
		int m_Size;

};

#endif

