#include <Arduino.h>
#include <LiquidCrystal.h>
#include "ir_remote.h"
#include "characters.h"
#include "utils.h"

#pragma once

int currentObstacle = 0;

class ObstaclesScreen
{
private:
  static void handleShowLcd(LiquidCrystal lcd);
  static void handleRemote(LiquidCrystal lcd, IRRemote remote, int *currentScreen);

public:
  static void handle(LiquidCrystal lcd, IRRemote remote, int *currentScreen);
};

void ObstaclesScreen::handle(LiquidCrystal lcd, IRRemote remote, int *currentScreen)
{
  handleShowLcd(lcd);
  handleRemote(lcd, remote, currentScreen);
}

void ObstaclesScreen::handleShowLcd(LiquidCrystal lcd)
{
  // ________________
  // | RUNNING GAME |
  // | <   Play   > |
  // ----------------
  lcd.setCursor(Utils::getCenteredPosition(Characters::obstacleNames[currentObstacle].length()), 0);
  lcd.print(Characters::obstacleNames[currentObstacle]);

  lcd.setCursor(0, 1);
  lcd.print("<");

  lcd.setCursor(7, 1);
  Characters::renderCharacter(lcd, currentObstacle + 4);

  lcd.setCursor(15, 1);
  lcd.print(">");
}

void ObstaclesScreen::handleRemote(LiquidCrystal lcd, IRRemote remote, int *currentScreen)
{
  IRRemoteCommand command = remote.getCommand();

  switch (command)
  {
  case IRRemote::LEFT:
    lcd.clear();
    currentObstacle--;
    if (currentObstacle < 0)
    {
      currentObstacle = 3;
    }
    break;

  case IRRemote::RIGHT:
    lcd.clear();
    currentObstacle++;
    if (currentObstacle > 3)
    {
      currentObstacle = 0;
    }
    break;

  case IRRemote::OK:
  case IRRemote::RETURN:
    *currentScreen = 0;
    break;
  default:
    break;
  }
}