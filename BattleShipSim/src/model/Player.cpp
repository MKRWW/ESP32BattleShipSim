//
//
//

#include "Player.h"
#include "sea/Sea.h"
#include "ships/Fleet.h"

Player::Player() {
	Serial.println(F("PLAYER: Constructor Start..."));
	this->m_mySea = new Sea;
	this->m_fleet = new Fleet;
	this->m_PlayerState = Player::PLAYER_STATE_ALIVE;
	Serial.println(F("PLAYER: Constructor END!"));

}

Player::~Player() {
	delete this->m_fleet;
	delete this->m_mySea;
}

Sea* const Player::sea(){
	return this->m_mySea;
}

Fleet* const Player::fleet() {
	return this->m_fleet;
}
