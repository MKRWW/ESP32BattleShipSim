// 
// 
// 

#include "GameEngine.h"
#include "src/model/GameData.h"
#include "src/services/FleetArrangerService.h"
#include "src/model/ships/Fleet.h"
#include "src/model/sea/Sea.h"
#include "src/model/sea/Cell.h"

GameEngine::GameEngine() {

}

GameEngine::~GameEngine() {

}

void GameEngine::update(GameData* const aGameData) {
	Player* const playerA = aGameData->playerA();
	Player* const playerB = aGameData->playerB();
	Serial.print(F("GameEngine: updating in current game State: ")); Serial.println(aGameData->currentState());
	switch (aGameData->currentState()){
		case GameData::GAME_STATE_INIT:
			FleetArrangerService::placeShipsForPlayer(aGameData->playerA());
			FleetArrangerService::placeShipsForPlayer(aGameData->playerB());
			aGameData->setCurrentState(GameData::GAME_STATE_PLAYER_A_TURN);
			break;
		case GameData::GAME_STATE_PLAYER_A_TURN: 
			Serial.println(F("GameEngine: PlayerA's turn..."));
			if (isPlayerStillAlive(playerA)) {
				playerHandlesFireResponse(playerA, playerTakesFire(playerB, playerShoots(playerA)));
				aGameData->setCurrentState(GameData::GAME_SATE_PLAYER_B_TURN);
			}
			else {
				aGameData->setCurrentState(GameData::GAME_SATE_FINISHED);
			}
			break;
		case GameData::GAME_SATE_PLAYER_B_TURN:
			Serial.println(F("GameEngine: PlayerB's turn..."));
			if (isPlayerStillAlive(playerB)) {
				playerHandlesFireResponse(playerB,playerTakesFire(playerA, playerShoots(playerB)));
				aGameData->setCurrentState(GameData::GAME_STATE_PLAYER_A_TURN);
			}
			else {
				aGameData->setCurrentState(GameData::GAME_SATE_FINISHED);
			}
			break;
		case GameData::GAME_SATE_FINISHED:
			break;
		default:
			break;
	}
}

bool GameEngine::isPlayerStillAlive(Player* const aPlayer) {
	Serial.println(F("GameEngine: isPlayerStillAlive start...."));
	bool isPlayerAlive = !aPlayer->fleet()->isDestroyed();
	Serial.print(F("GameEngine: isPlayerStillAlive end with result: ")); Serial.println(isPlayerAlive);
	return isPlayerAlive;
}

SingleShot GameEngine::playerShoots(Player* const aSource) {
	Serial.println(F("GameEngine: playerShoots start...."));
	int randomRange = aSource->sea()->size();
	Cell** cells = aSource->sea()->cells();
	int row = random(0, randomRange);
	int col = random(0, randomRange);
	while (cells[row][col].enemyCellState() != Cell::CELL_STATE_UNKNOWN) {
		 row = random(0, randomRange);
		 col = random(0, randomRange);
		 Serial.print(F("GameEngine: calculating shot at row, col: ")); Serial.print(row); Serial.print(","); Serial.println(col);
	}
	Serial.print(F("GameEngine: shooting at row, col: ")); Serial.print(row); Serial.print(","); Serial.println(col);
	Serial.println(F("GameEngine: playerShoots end"));
	return SingleShot(row, col);
}

GameEngine::fireResponse_t GameEngine::playerTakesFire(Player* const destination, SingleShot shot) {
	Serial.println(F("GameEngine: playerTakesFire start...."));
	Serial.print(F("GameEngine: taking fire at row, col: ")); Serial.print(shot.row()); Serial.print(","); Serial.println(shot.col());
	Cell& targetCell = destination->sea()->cells()[shot.row()][shot.col()];
	Cell::cellState_t newCellState = targetCell.ship() == NULL ? Cell::CELL_STATE_MISS : Cell::CELL_STATE_HIT;
	switch (newCellState) {
		case Cell::CELL_STATE_HIT:
			Serial.println(F("GameEngine: playerTakesFire HIT"));
			break;
		case Cell::CELL_STATE_MISS:
			Serial.println(F("GameEngine: playerTakesFire MISS"));
			break;
	}
	targetCell.setCellState(newCellState);
	GameEngine::fireResponse_t retvar;
	retvar.shot = shot;
	retvar.response = newCellState;
	Serial.println(F("GameEngine: playerTakesFire end"));
	return retvar;
}

void GameEngine::playerHandlesFireResponse(Player* const destination, fireResponse_t aFireResponse) {
	Serial.println(F("GameEngine: playerHandlesFireResponse start...."));
	Cell** cells = destination->sea()->cells();
	Cell& targetCell = cells[aFireResponse.shot.row()][aFireResponse.shot.col()];
	targetCell.setEnemyCellState(aFireResponse.response);
	Serial.println(F("GameEngine: playerHandlesFireResponse end"));
}