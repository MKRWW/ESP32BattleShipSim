// FleetArrangerService.h

#ifndef _FLEETARRANGERSERVICE_h
#define _FLEETARRANGERSERVICE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class Player;
class Sea;
class Ship;

class FleetArrangerService {
	public:
		static bool placeShipsForPlayer(Player* const aPlayer);
	protected:
	private:
		static void placeShip(Ship* const aShip, int aRow, int aCol, Sea* const aSea);
		static bool shipDoesFitInSea(Ship* const aShip, int aRow, int aCol, Sea* const aSea);
		static bool shipDoesNotOverlapOtherShip(Ship* const aShip, int aRow, int aCol, Sea* const aSea);

};

#endif
