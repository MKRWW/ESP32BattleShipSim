// UiEngine.h

#ifndef _UIENGINE_h
#define _UIENGINE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class GameData;
class Adafruit_SSD1306;
class Sea;
class Cell;

class UIEngine {

	public:
	UIEngine(Adafruit_SSD1306& aPlayerAScreen, Adafruit_SSD1306& aPlayerBScreen);
	~UIEngine();
	void render(GameData* const aGameData);
	void renderFinalScreen(GameData* const aGameData);

	private:
	void drawField(Adafruit_SSD1306& aPlayerAScreen, Sea* const aPlayerSea, bool aIsOpponentScreen);
	void drawCell(Adafruit_SSD1306& aPlayerAScreen, Cell& aCell, int aCellX, int aCellY, int cellUxWidthHeight, bool aIsOpponentScreen);
	void clearScreen();
	void doDraw();


	private:
	Adafruit_SSD1306& m_PlayerAScreen;
	Adafruit_SSD1306& m_PlayerBScreen;
	int m_ScreenHeight, m_ScreenWidth, m_OwnSeaStartX, m_OwnSeaHeight, m_OwnSeaWidth, m_OpponentSeaStartX, m_OpponentSeaHeight, m_OpponentSeaWidth;
};

#endif

