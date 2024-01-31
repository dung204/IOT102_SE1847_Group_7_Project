#include <LiquidCrystal.h>
#include "ir_remote.h"
#include "main_menu_screen.h"
#include "choose_characters_screen.h"
#include "obstacles_screen.h"
#include "about_screen.h"
#include "gameplay_screen.h"
#include "high_score_screen.h"
#include "reset_screen.h"

#pragma once

class Screens
{
public:
  static const int MAIN_MENU = 0;
  static const int GAMEPLAY = 1;
  static const int CHARACTERS = 2;
  static const int OBSTACLES = 3;
  static const int HIGH_SCORE = 4;
  static const int RESET = 5;
  static const int ABOUT = 6;
};

class ScreenHandler
{
private:
  int currentScreen;
  LiquidCrystal lcd;
  IRRemote remote;

public:
  ScreenHandler();
  ScreenHandler(LiquidCrystal lcd, IRRemote remote);
  void handle();
};

ScreenHandler::ScreenHandler()
    : lcd(A0, A1, A2, A3, A4, A5) // Initialize the "lcd" object using the default constructor
{
}

ScreenHandler::ScreenHandler(LiquidCrystal lcd, IRRemote remote)
    : lcd(lcd), remote(remote)
{
  this->currentScreen = Screens::MAIN_MENU;
}

void ScreenHandler::handle()
{
  switch (this->currentScreen)
  {
  case Screens::GAMEPLAY:
    GameplayScreen::handle(this->lcd, this->remote, &this->currentScreen);
    break;
  case Screens::MAIN_MENU:
    MainMenuScreen::handle(this->lcd, this->remote, &this->currentScreen);
    break;
  case Screens::CHARACTERS:
    ChooseCharactersScreen::handle(this->lcd, this->remote, &this->currentScreen);
    break;
  case Screens::OBSTACLES:
    ObstaclesScreen::handle(this->lcd, this->remote, &this->currentScreen);
    break;
  case Screens::HIGH_SCORE:
    HighScoreScreen::handle(this->lcd, this->remote, &this->currentScreen);
    break;
  case Screens::RESET:
    ResetScreen::handle(this->lcd, &this->currentScreen);
    break;
  case Screens::ABOUT:
    AboutScreen::handle(this->lcd, this->remote, &this->currentScreen);
    break;
  default:
    break;
  }
}