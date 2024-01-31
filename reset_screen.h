#include <Arduino.h>
#include <LiquidCrystal.h>
#include "ir_remote.h"
#include "characters.h"
#include "utils.h"

#pragma once

class ResetScreen
{
private:
  static const String SCREEN_HEADER;

  static void handleShowLcd(LiquidCrystal lcd);
  static void handleReset(LiquidCrystal lcd, int *currentScreen);

public:
  static void handle(LiquidCrystal lcd, int *currentScreen);
};

const String ResetScreen::SCREEN_HEADER = "RESETTING...";

void ResetScreen::handle(LiquidCrystal lcd, int *currentScreen)
{
  handleShowLcd(lcd);
  handleReset(lcd, currentScreen);
}

void ResetScreen::handleShowLcd(LiquidCrystal lcd)
{
  lcd.setCursor(Utils::getCenteredPosition(SCREEN_HEADER.length()), 0);
  lcd.print(SCREEN_HEADER);
}

void ResetScreen::handleReset(LiquidCrystal lcd, int *currentScreen)
{
  for (int i = 0; i < 1024; i++)
  {
    Utils::writeEEPROM(i, Utils::EEPROM_NULL);
  }
  lcd.clear();
  *currentScreen = 0;
}