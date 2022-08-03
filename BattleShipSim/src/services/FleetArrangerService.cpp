// 
// 
// 

#include "FleetArrangerService.h"

#include "../model/Player.h"
#include "../model/sea/Sea.h"
#include "../model/sea/Cell.h"
#include "../model/ships/Ship.h"
#include "../model/ships/Fleet.h"
#include "../model/sea/Cell.h"

bool FleetArrangerService::placeShipsForPlayer(Player* const aPlayer) {
	Serial.println(F("FleetArrangerService: placeShipsForPlayer start...."));
	int fleetSize = aPlayer->fleet()->size();

	Ship::shipOrientation_t orientations[10] = { Ship::ORIENTATION_HORIZONTAL, Ship::ORIENTATION_VERTICAL, Ship::ORIENTATION_HORIZONTAL ,Ship::ORIENTATION_VERTICAL ,Ship::ORIENTATION_HORIZONTAL,  Ship::ORIENTATION_VERTICAL, Ship::ORIENTATION_HORIZONTAL ,Ship::ORIENTATION_VERTICAL ,Ship::ORIENTATION_HORIZONTAL, Ship::ORIENTATION_VERTICAL };

	Serial.print(F("FleetArrangerService:: Fleet size: ")); Serial.println(fleetSize);
	for (int i = 0; i < fleetSize;i++) {
		Ship* currentShip = aPlayer->fleet()->shipAt(i);
		Serial.print(F("FleetArrangerService:: Current ship: ")); Serial.println(currentShip->type());
		Ship::shipOrientation_t shipOrientation = orientations[random(0, 10)];
		currentShip->setOrientation(shipOrientation);
		Serial.print(F("FleetArrangerService:: Current ship's orientation: ")); Serial.println(currentShip->orientation());
		Serial.print(F("FleetArrangerService:: Current ship's size: ")); Serial.println(currentShip->size());
		bool shipHasBeenPlaced = false;
		while (!shipHasBeenPlaced) {
			int row = random(0, aPlayer->sea()->size());
			int col = random(0, aPlayer->sea()->size());
			Serial.print(F("FleetArrangerService:: random coordinates row,col: ")); Serial.print(row);Serial.print(",");Serial.println(col);
			if (shipDoesFitInSea(currentShip, row, col, aPlayer->sea()) && shipDoesNotOverlapOtherShip(currentShip, row, col, aPlayer->sea())) {
				placeShip(currentShip, row, col, aPlayer->sea());
				shipHasBeenPlaced = true;
			}
		}
	}
	Serial.println(F("FleetArrangerService: placeShipsForPlayer done!"));
}

void FleetArrangerService::placeShip(Ship* const aShip, int aRow, int aCol, Sea* const aSea) {
	Serial.println(F("FleetArrangerService: placeShip start...."));
	Cell** cells = aSea->cells();
	for (int i = 0; i < aShip->size(); i++) {
		Cell* cell = NULL;
		if (aShip->orientation() == Ship::ORIENTATION_HORIZONTAL) {
			cell = &cells[aRow][aCol + i];
		}
		else {
			cell = &cells[aRow + i][aCol];
		}
		cell->setShip(aShip).addCell(i, cell);
	}
	Serial.println(F("FleetArrangerService: placeShip end!"));
}

bool FleetArrangerService::shipDoesFitInSea(Ship* const aShip, int aRow, int aCol, Sea* const aSea) {
	Serial.println(F("FleetArrangerService: shipDoesFitInSea start...."));
	bool retvar = true;
	if (aShip->orientation() == Ship::ORIENTATION_HORIZONTAL) {
		retvar = aCol + (aShip->size() - 1) < (aSea->size() - 1);
	}
	else {
		retvar = aRow + (aShip->size() - 1) < (aSea->size() - 1);
	}
	Serial.print(F("FleetArrangerService: shipDoesFitInSea result: "));Serial.println(retvar);
	return retvar;
}

bool FleetArrangerService::shipDoesNotOverlapOtherShip(Ship* const aShip, int aRow, int aCol, Sea* const aSea) {
	Serial.println(F("FleetArrangerService: shipDoesNotOverlapOtherShip start...."));
	Cell** cells = aSea->cells();
	bool retvar = true;
	for (int i = 0; i < aShip->size(); i++) {
		if (aShip->orientation() == Ship::ORIENTATION_HORIZONTAL && cells[aRow][aCol + 1].ship() != NULL) {
			return false;
		}
		else if (aShip->orientation() == Ship::ORIENTATION_VERTICAL && cells[aRow + i][aCol].ship() != NULL) {
			return false;
		}
	}
	return true;
}