// Cell.h

#ifndef _CELL_h
#define _CELL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
class Ship;
class Cell {
	public:
		typedef enum cellState {
			CELL_STATE_UNKNOWN,
			CELL_STATE_HIT,
			CELL_STATE_MISS
		}cellState_t;

	public:
		Cell();
		~Cell();
		Ship* const ship();
		Ship& setShip(Ship* const aShip);
		cellState_t cellState();
		void setCellState(cellState_t aCellState);
		cellState_t enemyCellState();
		void setEnemyCellState(cellState_t aCellState);
	protected:
	private:

	public:
	protected:
	private:
		Ship* m_ship;
		cellState_t m_CellState;
		cellState_t m_EnemyCellState;
};

#endif

