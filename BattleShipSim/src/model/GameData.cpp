// 
// 
// 

#include "GameData.h"

GameData::GameData() {
	Serial.println(F("GAMEDATA: Constructor Start..."));
	this->m_PlayerOne = new Player();
	this->m_PlayerTwo = new Player();
	this->m_GameState = GameData::GAME_STATE_INIT;
	Serial.println(F("GAMEDATA: Constructor END!"));
}

GameData::~GameData() {
	delete this->m_PlayerOne;
	delete this->m_PlayerTwo;
}


GameData::gameState_t GameData::currentState() {
	return this->m_GameState;
}

Player* const GameData::playerA() {
	return this->m_PlayerOne;
}

Player* const GameData::playerB() {
	return this->m_PlayerTwo;
}

void GameData::setCurrentState(gameState_t aState) {
	this->m_GameState = aState;
}