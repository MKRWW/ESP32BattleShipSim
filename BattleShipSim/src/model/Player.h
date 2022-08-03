// Player.h

#ifndef _PLAYER_h
#define _PLAYER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class Sea;
class Fleet;

class Player {
	public:
	typedef enum playerState {
		PLAYER_STATE_ALIVE,
		PLAYER_STATE_DEAD
	}playerState_t;

public:
  Player();
  virtual ~Player();
  Sea* const sea();
  Fleet* const fleet();
protected:
private:

public:
protected:
private:
  Sea* m_mySea;
  Fleet* m_fleet;
  playerState_t m_PlayerState;
};

#endif

