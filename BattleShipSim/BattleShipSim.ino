/*
 Name:		BattleShipSim.ino
 Created:	01.08.2022 21:10:07
 Author:	markus
*/
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>

#include "src/model/Player.h"
#include "src/model/GameData.h"
#include "UiEngine.h"
#include "GameEngine.h"
#include "src/services/FleetArrangerService.h"

#define I2C_SECONDARY_BUS_SDA_PIN 18
#define I2C_SECONDARY_BUS_SCL_PIN 19
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C
#define OLED_RESET_PIN -1

Adafruit_SSD1306 displayPlayerA(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire,
                                SCREEN_ADDRESS);
Adafruit_SSD1306 displayPlayerB(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1,
                                SCREEN_ADDRESS);

long lastDataUpdateTimeStamp = 0l;


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  Serial.println(F("BATTLESHIP: Booting Simulator"));
  if (!Wire.begin()) {
    Serial.println(F("I2C Bus 1 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  if (!Wire1.begin(I2C_SECONDARY_BUS_SDA_PIN, I2C_SECONDARY_BUS_SCL_PIN)) {
    Serial.println(F("I2C Bus 1 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!displayPlayerA.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("PlayerA display allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  if (!displayPlayerB.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("PlayerB display allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  displayPlayerA.display();
  displayPlayerB.display();
  delay(2000); // Pause for 2 seconds to enjoy the beauty of the splash screen
  lastDataUpdateTimeStamp = millis();
}

// the loop function runs over and over again until power down or reset
void loop() {
    GameData* gameData = new GameData();
    GameEngine* engine = new GameEngine();
    UIEngine* uiEngine = new UIEngine(displayPlayerA, displayPlayerB);
    
    //the main Game loop
    while (gameData->currentState() != GameData::GAME_SATE_FINISHED) {
        uiEngine->render(gameData);
        //all two Seconds we update the gamestate
        if (millis() - lastDataUpdateTimeStamp > 250) {
            engine->update(gameData);
            lastDataUpdateTimeStamp = millis();
        }
    }
    uiEngine->render(gameData);//render final Screen
    delay(1000);
    uiEngine->renderFinalScreen(gameData);
    delay(2500);

    delete gameData;
    delete engine;
    delete uiEngine;
    delay(2000);//two seconds pause then start over
}
