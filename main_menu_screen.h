#include <Arduino.h>
#include <LiquidCrystal.h>
#include "ir_remote.h"
#include "characters.h"
#include "utils.h"

#pragma once

int selectedMenuItem = 0;

class MainMenuScreen
{
private:
  static const int MENU_ITEMS_LENGTH = 6;
  static const String MENU_ITEMS[MENU_ITEMS_LENGTH];
  static const String SCREEN_HEADER;

  static void handleShowLcd(LiquidCrystal lcd);
  static void handleRemote(LiquidCrystal lcd, IRRemote remote, int *currentScreen);

public:
  static void handle(LiquidCrystal lcd, IRRemote remote, int *currentScreen);
};

const String MainMenuScreen::MENU_ITEMS[MENU_ITEMS_LENGTH] = {"PLAY", "CHARACTERS", "OBSTACLES", "HIGH SCORE", "RESET", "ABOUT"};

const String MainMenuScreen::SCREEN_HEADER = "OBSTAJUMP GAME";

void MainMenuScreen::handle(LiquidCrystal lcd, IRRemote remote, int *currentScreen)
{
  handleShowLcd(lcd);
  handleRemote(lcd, remote, currentScreen);
}

void MainMenuScreen::handleShowLcd(LiquidCrystal lcd)
{
  lcd.setCursor(1, 0);
  lcd.print(SCREEN_HEADER);

  lcd.setCursor(0, 1);
  lcd.print("<");

  lcd.setCursor(Utils::getCenteredPosition(MENU_ITEMS[selectedMenuItem].length()), 1);
  lcd.print(MENU_ITEMS[selectedMenuItem]);

  lcd.setCursor(15, 1);
  lcd.print(">");
}

void MainMenuScreen::handleRemote(LiquidCrystal lcd, IRRemote remote, int *currentScreen)
{
  IRRemoteCommand command = remote.getCommand();

  switch (command)
  {
  case IRRemote::LEFT:
    lcd.clear();
    selectedMenuItem--;
    if (selectedMenuItem < 0)
    {
      selectedMenuItem = MENU_ITEMS_LENGTH - 1;
    }
    break;
  case IRRemote::RIGHT:
    lcd.clear();
    selectedMenuItem++;
    if (selectedMenuItem > MENU_ITEMS_LENGTH - 1)
    {
      selectedMenuItem = 0;
    }
    break;
  case IRRemote::OK:
    lcd.clear();
    *currentScreen = selectedMenuItem + 1;
    break;
  default:
    break;
  }
}