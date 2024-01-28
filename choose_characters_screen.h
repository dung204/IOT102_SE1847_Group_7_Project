#include <Arduino.h>
#include <LiquidCrystal.h>
#include "ir_remote.h"
#include "characters.h"
#include "utils.h"

#pragma once

int currentCharacter = Utils::readEEPROM(1) > 3 ? 0 : Utils::readEEPROM(1);

class ChooseCharactersScreen
{
private:
  static void handleShowLcd(LiquidCrystal lcd);
  static void handleRemote(LiquidCrystal lcd, IRRemote remote, int *currentScreen);

public:
  static void handle(LiquidCrystal lcd, IRRemote remote, int *currentScreen);
};

void ChooseCharactersScreen::handle(LiquidCrystal lcd, IRRemote remote, int *currentScreen)
{
  handleShowLcd(lcd);
  handleRemote(lcd, remote, currentScreen);
}

void ChooseCharactersScreen::handleShowLcd(LiquidCrystal lcd)
{
  // ________________
  // | RUNNING GAME |
  // | <   Play   > |
  // ----------------
  lcd.setCursor(Utils::getCenteredPosition(Characters::characterNames[currentCharacter].length()), 0);
  lcd.print(Characters::characterNames[currentCharacter]);

  lcd.setCursor(0, 1);
  lcd.print("<");

  lcd.setCursor(7, 1);
  Characters::renderCharacter(lcd, currentCharacter);

  lcd.setCursor(15, 1);
  lcd.print(">");
}

void ChooseCharactersScreen::handleRemote(LiquidCrystal lcd, IRRemote remote, int *currentScreen)
{
  IRRemoteCommand command = remote.getCommand();

  switch (command)
  {
  case IRRemote::LEFT:
    lcd.clear();
    currentCharacter--;
    if (currentCharacter < 0)
    {
      currentCharacter = 3;
    }
    break;

  case IRRemote::RIGHT:
    lcd.clear();
    currentCharacter++;
    if (currentCharacter > 3)
    {
      currentCharacter = 0;
    }
    break;

  case IRRemote::OK:
    Utils::writeEEPROM(1, currentCharacter);
    *currentScreen = 0;
    break;

  case IRRemote::RETURN:
    *currentScreen = 0;
    break;
  default:
    break;
  }
}