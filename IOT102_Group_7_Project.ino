#include <Arduino.h>
#include <LiquidCrystal.h>
#include "characters.h"
#include "ir_remote.h"
#include "screens.h"
#include "utils.h"

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
IRRemote remote;
ScreenHandler screenHandler;

void setup()
{
  Serial.begin(115200);
  lcd.begin(16, 2);
  Characters::init(lcd);

  remote = IRRemote(8);
  screenHandler = ScreenHandler(lcd, remote);

  randomSeed(analogRead(0));
}

void loop()
{
  screenHandler.handle();
}