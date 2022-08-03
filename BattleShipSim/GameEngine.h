// GameEngine.h

#ifndef _GAMEENGINE_h
#define _GAMEENGINE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "src/model/sea/Cell.h"
#include "src/model/weapons/SingleShot.h"

class GameData;
class Player;
class Bullet;

class GameEngine {
	private:
	typedef struct fireResponse {
		SingleShot shot;
		Cell::cellState_t response;
	}fireResponse_t;
	public:
		GameEngine();
		~GameEngine();
		void update(GameData* const aGameData);
	protected:
	private:
		bool isPlayerStillAlive(Player* const aPlayer);
		SingleShot playerShoots(Player* const aSource);
		fireResponse_t playerTakesFire(Player* const destination, SingleShot shot);
		void playerHandlesFireResponse(Player* const destination, fireResponse_t aFireResponse);
};

#endif

