#include <IRremote.h>

#pragma once

typedef unsigned short IRRemoteCommand;

class IRRemote
{
public:
  static const IRRemoteCommand POWER = 69;
  static const IRRemoteCommand MENU = 71;
  static const IRRemoteCommand UP = 64;
  static const IRRemoteCommand DOWN = 25;
  static const IRRemoteCommand LEFT = 7;
  static const IRRemoteCommand RIGHT = 9;
  static const IRRemoteCommand OK = 21;
  static const IRRemoteCommand RETURN = 67;
  static const IRRemoteCommand ZERO = 22;
  static const IRRemoteCommand ONE = 12;
  static const IRRemoteCommand TWO = 24;
  static const IRRemoteCommand THREE = 94;
  static const IRRemoteCommand FOUR = 8;
  static const IRRemoteCommand FIVE = 28;
  static const IRRemoteCommand SIX = 90;
  static const IRRemoteCommand SEVEN = 66;
  static const IRRemoteCommand EIGHT = 82;
  static const IRRemoteCommand NINE = 74;

  IRRemote();
  IRRemote(int pin);
  IRRemoteCommand getCommand();
};

IRRemote::IRRemote()
{
}

IRRemote::IRRemote(int pin)
{
  IrReceiver.begin(pin);
}

IRRemoteCommand IRRemote::getCommand()
{
  if (IrReceiver.decode())
  {
    delay(150);
    IrReceiver.resume();
    return IrReceiver.decodedIRData.command;
  }
  return 0;
}