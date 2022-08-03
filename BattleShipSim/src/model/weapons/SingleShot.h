// SingleShot.h

#ifndef _SINGLESHOT_h
#define _SINGLESHOT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class SingleShot {
	public:
		SingleShot(int aTargetRow = 0, int aTargetCol = 0);
		~SingleShot();
		int row();
		int col();
	protected:
	private:
		int m_Row, m_Col;

};

#endif

