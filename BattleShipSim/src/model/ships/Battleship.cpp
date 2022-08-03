//
//
//

#include "Battleship.h"

BattleShip::BattleShip() : Ship(4, Ship::BATTLESHIP) {
	Serial.println(F("BattleShip: Constructed!"));
}

BattleShip::~BattleShip() {

}
