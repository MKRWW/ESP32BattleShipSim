//
//
//

#include "Ship.h"
#include "Battleship.h"
#include "Carrier.h"
#include "Cruiser.h"
#include "Submarine.h"
#include "Destroyer.h"
#include "../sea/Cell.h"

Ship::Ship(uint8_t aSize, shipType_t aType) {
	this->m_size = aSize;
	this->m_type = aType;
	this->m_Orientation = Ship::ORIENTATION_VERTICAL;
	this->m_cellsShipIsIn = new Cell * [this->m_size];
}

Ship::~Ship() {
	delete[] this->m_cellsShipIsIn;
}

uint8_t Ship::size() { return this->m_size; }

Ship::shipOrientation_t Ship::orientation() {
	return this->m_Orientation;
}

void Ship::setOrientation(shipOrientation_t aOrientation) {
	this->m_Orientation = aOrientation;
}

Ship::shipType_t Ship::type() {
	return this->m_type;
}

void Ship::addCell(int index, Cell* const cell) {
	if (index < this->m_size) {
		this->m_cellsShipIsIn[index] = cell;
	}
}

bool Ship::isSunk() {
	Serial.print(F("Ship: isSunk start for ship type:  ")); Serial.println(this->m_type);
	int destroyedCells = 0;
	for (int i = 0; i < this->m_size; i++) {
		Cell* shipCell = this->m_cellsShipIsIn[i];
		bool isCellHit = shipCell->cellState() == Cell::CELL_STATE_HIT;
		destroyedCells += isCellHit;
	}
	Serial.print(F("Ship: isSunk amount of flooded cells: ")); Serial.print(destroyedCells); Serial.print(F(" of Cells: ")); Serial.println(this->m_size);
	bool isShipSunk = destroyedCells == this->m_size;
	Serial.print(F("Ship: isSunk end with result: ."));Serial.println(isShipSunk);
	return isShipSunk;
}

Ship* Ship::instantiateShipC(Ship::shipType_t aShipType) {
	Serial.print(F("Ship: instantiateShip with type ")); Serial.println(aShipType);
	switch (aShipType) {
		case Ship::BATTLESHIP: {
				Serial.println(F("Ship: creating a Battleship"));
				return new BattleShip();
			}
		case Ship::CARRIER: {
				Serial.println(F("Ship: creating a Carrier"));
				return new Carrier();
			}
		case Ship::CRUISER: {
				Serial.println(F("Ship: creating a Cruiser"));
				return new Cruiser();
			}
		case Ship::SUBMARINE: {
				Serial.println(F("Ship: creating a Submarine"));
				return new Submarine();
			}
		case Ship::DESTROYER: {
				Serial.println(F("Ship: creating a Destroyer"));
				return new Destroyer();
			}
		default: {
				Serial.println(F("Ship: creating nothing"));
				return NULL;
			}
	}
}