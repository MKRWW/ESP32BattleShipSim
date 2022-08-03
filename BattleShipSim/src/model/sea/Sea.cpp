//
//
//

#include "Sea.h"

Sea::Sea(uint8_t aSize) {
	Serial.println(F("SEA: Constructor Start..."));
	//some safeguard, so we prevent ram flooding by the following allocation
	uint8_t safeSize = aSize <= 10 ? aSize : 10;
	this->m_Size = safeSize;

	//We allocate the battlefield, so we claim ourselves a big chunk of ram :D
	this->m_Cells = new Cell * [this->m_Size]; //Our rows
	for (int i = 0; i < this->m_Size; i++) {
		this->m_Cells[i] = new Cell[10]; // our columns
	}
	Serial.println(F("SEA: Constructor End!"));
}

Sea::~Sea() {
	//So here we free the memory upon destruction. Who needs garbage collectory and other fancy script kiddie rubish if one can be god over the heap :D
	for (int i = 0; i < this->m_Size; i++) {
		delete[] this->m_Cells[i];
	}
	delete[] this->m_Cells;
}

uint8_t Sea::size() { return this->m_Size; }

Cell** Sea::cells()
{
	return this->m_Cells;
}
