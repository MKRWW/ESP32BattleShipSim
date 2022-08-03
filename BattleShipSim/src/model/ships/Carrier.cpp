// 
// 
// 

#include "Carrier.h"

Carrier::Carrier() :Ship(5, Ship::CARRIER) {
	Serial.println(F("Carrier: Constructed!"));

}

Carrier::~Carrier() {

}

