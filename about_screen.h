#include <Arduino.h>
#include <LiquidCrystal.h>
#include "ir_remote.h"
#include "characters.h"

#pragma once

class AboutScreen
{
private:
  static void handleShowLcd(LiquidCrystal lcd);
  static void handleRemote(LiquidCrystal lcd, IRRemote remote, int *currentScreen);

public:
  static void handle(LiquidCrystal lcd, IRRemote remote, int *currentScreen);
};

void AboutScreen::handle(LiquidCrystal lcd, IRRemote remote, int *currentScreen)
{
  handleShowLcd(lcd);
  handleRemote(lcd, remote, currentScreen);
}

void AboutScreen::handleShowLcd(LiquidCrystal lcd)
{
  lcd.setCursor(16, 0);
  lcd.print("RUNNING GAME");
  lcd.setCursor(16, 1);
  lcd.print("BY GROUP 7 - IOT102");
  lcd.scrollDisplayLeft();
  delay(500);
}

void AboutScreen::handleRemote(LiquidCrystal lcd, IRRemote remote, int *currentScreen)
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