#include <Arduino.h>
#include <LiquidCrystal.h>
#include "ir_remote.h"
#include "characters.h"
#include "utils.h"

#pragma once

// To store the high score:
// 1. We use EEPROM
//
// 2. A score is of type `int`, but we can't store the score directly.
//    Because EEPROM can only store a byte (0 - 255) at a time.
//
//    Instead, we convert the score to a string. Then we store each
//    character of the string at the consecutive addresses in EEPROM.
//
// 3. We also need to store the length of the string. Hence, we store the length
//    of the string at the address `2`. Then we store the characters of the
//    string at the addresses `3` to `3 + length - 1`.
// By storing like this, we can utilize the function readEEPROMString() in
// utils.h to read the string from EEPROM.

class HighScoreScreen
{
private:
  static const String SCREEN_HEADER;

  static void handleShowLcd(LiquidCrystal lcd);
  static void handleRemote(LiquidCrystal lcd, IRRemote remote, int *currentScreen);

public:
  static void handle(LiquidCrystal lcd, IRRemote remote, int *currentScreen);
};

const String HighScoreScreen::SCREEN_HEADER = "HIGHEST SCORE";

void HighScoreScreen::handle(LiquidCrystal lcd, IRRemote remote, int *currentScreen)
{
  handleShowLcd(lcd);
  handleRemote(lcd, remote, currentScreen);
}

void HighScoreScreen::handleShowLcd(LiquidCrystal lcd)
{
  // Address 2 is the length of the score as a string
  // Address 3 to 3 + length - 1 are the characters of the score as a string
  int HIGH_SCORE = Utils::readEEPROM(2) == Utils::EEPROM_NULL
                       ? 0
                       : Utils::readEEPROMString(3, Utils::readEEPROM(2)).toInt();

  lcd.setCursor(Utils::getCenteredPosition(SCREEN_HEADER.length()), 0);
  lcd.print(SCREEN_HEADER);

  lcd.setCursor(Utils::getCenteredPosition(String(HIGH_SCORE).length()), 1);
  lcd.print(HIGH_SCORE);
}

void HighScoreScreen::handleRemote(LiquidCrystal lcd, IRRemote remote, int *currentScreen)
{
  IRRemoteCommand command = remote.getCommand();

  switch (command)
  {
  case IRRemote::RETURN:
  case IRRemote::OK:
    lcd.clear();
    *currentScreen = 0;
    break;
  default:
    break;
  }
}