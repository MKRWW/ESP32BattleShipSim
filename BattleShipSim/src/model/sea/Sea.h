// Sea.h

#ifndef _SEA_h
#define _SEA_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "Cell.h"
class Sea {
	public:
		Sea(uint8_t aSize = 10);
		virtual ~Sea();
		uint8_t size();
		Cell** cells();
	protected:
	private:

	public:
	protected:
	private:
		uint8_t m_Size;
		Cell** m_Cells;
};

#endif
