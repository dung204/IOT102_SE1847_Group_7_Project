#include <Arduino.h>
#include <EEPROM.h>

#pragma once

class Utils
{
public:
  static const int EEPROM_NULL = 255;

  static int getCenteredPosition(int textLength, int lcdWidth = 16);
  static int getRightmostPosition(int textLength, int lcdWidth = 16);
  static void writeEEPROM(int address, int value);
  static int readEEPROM(int address);
};

int Utils::getCenteredPosition(int textLength, int lcdWidth = 16)
{
  return (lcdWidth - textLength) / 2;
}

int Utils::getRightmostPosition(int textLength, int lcdWidth = 16)
{
  return lcdWidth - textLength;
}

int Utils::readEEPROM(int address)
{
  return EEPROM.read(address);
}

void Utils::writeEEPROM(int address, int value)
{
  EEPROM.write(address, value);
}