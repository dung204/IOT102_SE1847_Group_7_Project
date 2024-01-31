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
  static void writeEEPROMString(int addressStart, String value);
  static int readEEPROM(int address);
  static String readEEPROMString(int addressStart, int length);
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

String Utils::readEEPROMString(int addressStart, int length)
{
  String result = "";

  for (int i = addressStart; i < addressStart + length; i++)
  {
    int value = readEEPROM(i);
    if (value == EEPROM_NULL)
    {
      break;
    }
    result += (char)value;
  }

  return result;
}

void Utils::writeEEPROMString(int addressStart, String value)
{
  for (int i = 0; i < value.length(); i++)
  {
    writeEEPROM(addressStart + i, value[i]);
  }
  writeEEPROM(addressStart + value.length(), EEPROM_NULL);
}