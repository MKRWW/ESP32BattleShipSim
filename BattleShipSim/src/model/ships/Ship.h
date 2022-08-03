// Ship.h
// Ship.h

#ifndef _SHIP_h
#define _SHIP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class Cell;
class FleetArrangerService;

class Ship {

public:

	typedef enum shipType {
		CARRIER,
		BATTLESHIP,
		CRUISER,
		SUBMARINE,
		DESTROYER
	}shipType_t;

	typedef enum shipOrientation {
		ORIENTATION_HORIZONTAL,
		ORIENTATION_VERTICAL
	}shipOrientation_t;

public:
  Ship(uint8_t aSize, shipType_t aType);
  virtual ~Ship();
  uint8_t size();
  shipType_t type();
  shipOrientation_t orientation();
  void setOrientation(shipOrientation_t aOrientation);
  static Ship* instantiateShipC(shipType_t aShipType);
  bool isSunk();
protected:
	void addCell(int index, Cell* const cell);

private:
	uint8_t m_size;
	shipOrientation_t m_Orientation;
	shipType_t m_type;
	Cell** m_cellsShipIsIn;
 

public:
	friend class FleetArrangerService;
};

#endif

