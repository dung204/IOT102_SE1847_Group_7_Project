#include <Arduino.h>
#include <LiquidCrystal.h>
#include "ir_remote.h"
#include "characters.h"
#include "utils.h"

#define CHARACTER_UP 0
#define CHARACTER_DOWN 1

#pragma once

int gameplayCharacter;
int prevScore = 0;
int score = 0;
bool isGameOver = false;

int obstacleCode = random(4, 8);
int characterPosition = CHARACTER_DOWN;
int obstaclePosition = 15;

unsigned long jumpTimer = millis();
unsigned long scoreTimer = millis();
unsigned long obstacleTimer = millis();

class GameplayScreen
{
private:
  static void handleShowLcd(LiquidCrystal lcd);
  static void handleRemote(LiquidCrystal lcd, IRRemote remote, int *currentScreen);
  static void handleShowGameOver(LiquidCrystal lcd);
  static void handleIncreaseScore();
  static void handleCharacterJump(LiquidCrystal lcd);
  static void handleObstacleMovement(LiquidCrystal lcd);
  static boolean handleObstacleCollapse(LiquidCrystal lcd);

public:
  static void handle(LiquidCrystal lcd, IRRemote remote, int *currentScreen);
};

void GameplayScreen::handle(LiquidCrystal lcd, IRRemote remote, int *currentScreen)
{
  if (isGameOver)
  {
    handleShowGameOver(lcd);
    return;
  }

  gameplayCharacter = Utils::readEEPROM(1) > 3 ? 0 : Utils::readEEPROM(1);

  // These handlers are performed concurrently
  handleIncreaseScore();
  handleCharacterJump(lcd);
  handleObstacleMovement(lcd);

  if (handleObstacleCollapse(lcd))
    return;

  handleShowLcd(lcd);
  handleRemote(lcd, remote, currentScreen);
}

void GameplayScreen::handleShowLcd(LiquidCrystal lcd)
{
  lcd.setCursor(Utils::getRightmostPosition(String(score).length()), 0);
  lcd.print(score);

  lcd.setCursor(2, characterPosition);
  Characters::renderCharacter(lcd, gameplayCharacter);

  lcd.setCursor(obstaclePosition, 1);
  Characters::renderCharacter(lcd, obstacleCode);
}

void GameplayScreen::handleRemote(LiquidCrystal lcd, IRRemote remote, int *currentScreen)
{
  if ((!isGameOver && characterPosition == CHARACTER_DOWN) || isGameOver)
  {
    IRRemoteCommand command = remote.getCommand();

    switch (command)
    {
    case IRRemote::UP:
    case IRRemote::OK:
      if (isGameOver)
      {
        lcd.clear();
        score = 0;
        obstaclePosition = 15;
        isGameOver = false;
        break;
      }

      characterPosition = CHARACTER_UP;
      jumpTimer = millis();
      lcd.clear();
      break;

    case IRRemote::RETURN:
      if (isGameOver)
      {
        lcd.clear();
        isGameOver = false;
        *currentScreen = 0;
      }
      break;
    default:
      break;
    }
  }
}

void GameplayScreen::handleShowGameOver(LiquidCrystal lcd)
{
  lcd.setCursor(Utils::getCenteredPosition(10), 0);
  lcd.print("GAME OVER");
  lcd.setCursor(Utils::getCenteredPosition(8 + String(prevScore).length()), 1);
  lcd.print("SCORE: ");
  lcd.print(prevScore);
}

void GameplayScreen::handleIncreaseScore()
{
  if ((millis() - scoreTimer) > 250)
  {
    score++;
    scoreTimer = millis();
  }
}

void GameplayScreen::handleCharacterJump(LiquidCrystal lcd)
{
  if ((millis() - jumpTimer) > 600 && characterPosition == CHARACTER_UP)
  {
    lcd.clear();
    characterPosition = CHARACTER_DOWN;
    jumpTimer = millis();
  }
}

void GameplayScreen::handleObstacleMovement(LiquidCrystal lcd)
{
  if ((millis() - obstacleTimer) > 250)
  {
    lcd.clear();
    obstaclePosition--;
    if (obstaclePosition < 0)
    {
      obstaclePosition = 15;
      obstacleCode = random(4, 8);
    }
    obstacleTimer = millis();
  }
}

boolean GameplayScreen::handleObstacleCollapse(LiquidCrystal lcd)
{
  if (obstaclePosition == 2 && characterPosition == CHARACTER_DOWN)
  {
    lcd.clear();
    isGameOver = true;
    prevScore = score;
    score = 0;
    return true;
  }
  return false;
}