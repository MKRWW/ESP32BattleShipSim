// GameData.h

#ifndef _GAMEDATA_h
#define _GAMEDATA_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "Player.h"


class GameData {

	public:
	typedef enum m_GameState {
			GAME_STATE_INIT,
			GAME_STATE_PLAYER_A_TURN,
			GAME_SATE_PLAYER_B_TURN,
			GAME_SATE_FINISHED
		}gameState_t;

	public:
		GameData();
		virtual ~GameData();

		gameState_t currentState();
		void setCurrentState(gameState_t aState);
		Player* const playerA();
		Player* const playerB();

	protected:
	private:

	public:
	protected:
	private:
		Player* m_PlayerOne;
		Player* m_PlayerTwo;
		gameState_t m_GameState;
};
#endif

