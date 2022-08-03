// 
// 
// 

#include "Cell.h"
#include "../ships/Ship.h"

Cell::Cell() {
	this->m_ship = NULL;
	this->m_CellState = Cell::CELL_STATE_UNKNOWN;
	this->m_EnemyCellState = Cell::CELL_STATE_UNKNOWN;
}

Cell::~Cell() {

}

Ship& Cell::setShip(Ship* const aShip) {
	this->m_ship = aShip;
	return *aShip;
}

Ship* const Cell::ship() {
	return this->m_ship;
}

Cell::cellState_t Cell::cellState() {
	return this->m_CellState;
}

void Cell::setCellState(Cell::cellState_t aCellState) {
	this->m_CellState = aCellState;
}

Cell::cellState_t Cell::enemyCellState() {
	return this->m_EnemyCellState;
}

void Cell::setEnemyCellState(Cell::cellState_t aCellState) {
	this->m_EnemyCellState = aCellState;
}