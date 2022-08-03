// 
// 
// 

#include "UiEngine.h"
#include "src/model/GameData.h"
#include "src/model/Player.h"
#include "src/model/sea/Sea.h"
#include "src/model/sea/Cell.h"
#include "src/model/ships/Fleet.h"
#include <Adafruit_SSD1306.h>

#define TEXT_SIZE 3
#define TEXT_COLOR WHITE

UIEngine::UIEngine(Adafruit_SSD1306& aPlayerAScreen, Adafruit_SSD1306& aPlayerBScreen) :m_PlayerAScreen(aPlayerAScreen), m_PlayerBScreen(aPlayerBScreen) {
	m_ScreenHeight = m_PlayerAScreen.height();
	m_ScreenWidth = m_PlayerAScreen.width();
	m_OwnSeaStartX = 0;
	m_OwnSeaHeight = m_ScreenHeight;
	m_OwnSeaWidth = m_ScreenHeight;
	m_OpponentSeaStartX = m_OwnSeaStartX + m_OwnSeaWidth;
	m_OpponentSeaHeight = m_ScreenHeight;
	m_OpponentSeaWidth = m_ScreenHeight;

}

UIEngine::~UIEngine() {

}

void UIEngine::render(GameData* const aGameData) {
	this->clearScreen();
	Sea* const playerASea = aGameData->playerA()->sea();
	Sea* const playerBSea = aGameData->playerB()->sea();

	drawField(m_PlayerAScreen, playerASea, false);
	drawField(m_PlayerAScreen, playerASea, true);
	drawField(m_PlayerBScreen, playerBSea, false);
	drawField(m_PlayerBScreen, playerBSea, true);

	this->doDraw();
}

void UIEngine::drawField(Adafruit_SSD1306& aPlayerAScreen, Sea* const aPlayerSea, bool aIsOpponentScreen) {
	int seaSize = aPlayerSea->size();
	int cellUxWidthHeight = m_OwnSeaHeight / seaSize; //as we have a square playfield we only take the height of one playfield to determine the withd/height of a cell in the ux
	int startX = aIsOpponentScreen ? m_OpponentSeaStartX : m_OwnSeaStartX;
	Cell** const playerSeaCells = aPlayerSea->cells();
	aPlayerAScreen.drawRect(startX, 0, m_OwnSeaWidth, m_OwnSeaHeight, WHITE);
	for (int row = 0; row < seaSize; row++) {
		for (int col = 0; col < seaSize; col++) {
			int cellX = (col * cellUxWidthHeight) + startX + 2;
			int cellY = (row * cellUxWidthHeight) + 2;
			drawCell(aPlayerAScreen, playerSeaCells[row][col], cellX, cellY, cellUxWidthHeight, aIsOpponentScreen);
		}
	}
}

void UIEngine::drawCell(Adafruit_SSD1306& aPlayerAScreen, Cell& aCell, int aCellX, int aCellY, int cellUxWidthHeight, bool aIsOpponentScreen) {
	aPlayerAScreen.drawRect(aCellX, aCellY, cellUxWidthHeight, cellUxWidthHeight, WHITE);
	if (!aIsOpponentScreen) {
		if (aCell.ship() != NULL) {
			aPlayerAScreen.fillRect(aCellX, aCellY, cellUxWidthHeight, cellUxWidthHeight, WHITE);
		}
		if (aCell.ship() != NULL && aCell.cellState() == Cell::CELL_STATE_HIT) {
			aPlayerAScreen.fillCircle(aCellX + (cellUxWidthHeight / 2), aCellY + (cellUxWidthHeight / 2), cellUxWidthHeight / 4, BLACK);
		}
		if (aCell.cellState() == Cell::CELL_STATE_MISS) {
			aPlayerAScreen.fillRect(aCellX + 2, aCellY + 2, cellUxWidthHeight - 4, cellUxWidthHeight - 4, WHITE);
		}
	}
	else {
		if (aCell.enemyCellState() == Cell::CELL_STATE_HIT) {
			aPlayerAScreen.fillRect(aCellX, aCellY, cellUxWidthHeight, cellUxWidthHeight, WHITE);
		}
		else if (aCell.enemyCellState() == Cell::CELL_STATE_MISS) {
			aPlayerAScreen.fillRect(aCellX + 2, aCellY + 2, cellUxWidthHeight - 4, cellUxWidthHeight - 4, WHITE);
		}
	}
}

void UIEngine::renderFinalScreen(GameData* const aGameData) {
	clearScreen();
	this->m_PlayerAScreen.setCursor(20, 20);
	this->m_PlayerBScreen.setCursor(20, 20);
	this->m_PlayerAScreen.setTextSize(TEXT_SIZE);
	this->m_PlayerBScreen.setTextSize(TEXT_SIZE);
	this->m_PlayerAScreen.setTextColor(TEXT_COLOR);
	this->m_PlayerBScreen.setTextColor(TEXT_COLOR);
	if (aGameData->playerA()->fleet()->isDestroyed()) {
		this->m_PlayerAScreen.println(F("Loser"));
		this->m_PlayerBScreen.println(F("Winner"));
	}
	else {
		this->m_PlayerAScreen.println(F("Winner"));
		this->m_PlayerBScreen.println(F("Loser"));
	}
	doDraw();
}

void UIEngine::clearScreen() {
	m_PlayerAScreen.clearDisplay();
	m_PlayerBScreen.clearDisplay();
}

void UIEngine::doDraw() {
	m_PlayerAScreen.display();
	m_PlayerBScreen.display();
}

