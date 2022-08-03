// Battleship.h

#ifndef _BATTLESHIP_h
#define _BATTLESHIP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include"Ship.h"

class BattleShip:public Ship {
public:
  BattleShip();
  ~BattleShip();

protected:
private:

};

#endif

