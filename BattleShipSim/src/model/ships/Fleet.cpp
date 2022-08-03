// 
// 
// 

#include "Fleet.h"
#include "Ship.h"
#include "Battleship.h"

Fleet::Fleet(int aSize) {
	Serial.println(F("FLEET: Constructor Start..."));
	this->m_Size = aSize;
	this->m_fleet = new Ship*[this->m_Size];
	for (int i = 0; i < this->m_Size; i++) {
		Ship* ship = Ship::instantiateShipC(static_cast<Ship::shipType_t>(i));
		Serial.print(F("FLEET: putting ship into fleet. ship has type:  "));Serial.println(ship->type());
		this->m_fleet[i] = ship;
	}
	Serial.println(F("FLEET: Constructor End!"));
}

Fleet::~Fleet() {
	for (int i = 0; i < this->m_Size; i++) {
		delete this->m_fleet[i];
	}
	delete[] this->m_fleet;
}

int Fleet::size() {
	Serial.print(F("FLEET: size() "));Serial.println(this->m_Size);
	return this->m_Size;
}

Ship* const Fleet::shipAt(int aIndex) {
	Serial.print(F("FLEET: shipAt() "));Serial.println(aIndex);
	if (aIndex < this->m_Size) {
		Ship* retvar =  this->m_fleet[aIndex];
		Serial.print(F("FLEET: shipAt() returns a ship with type "));Serial.println(retvar->type());
		return retvar;
	}
	return NULL;
}

bool Fleet::isDestroyed() {
	Serial.println(F("Fleet: isDestroyed start... "));
	int destroyedShips = 0;
	for (int i = 0; i < this->m_Size; i++) {
		destroyedShips += this->m_fleet[i]->isSunk();
	}
	bool isFleetDestroyed = destroyedShips == this->m_Size;
	Serial.print(F("Fleet: isDestroyed end with result: ")); Serial.println(isFleetDestroyed);
	return isFleetDestroyed;
}
