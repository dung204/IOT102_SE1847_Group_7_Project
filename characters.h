#include <Arduino.h>
#include <LiquidCrystal.h>

#pragma once

class Characters
{
public:
    static const String characterNames[4];
    static const String obstacleNames[4];

    static const int ROCKET = 0;
    static const int BELL = 1;
    static const int HUMAN = 2;
    static const int SPONGE_BOB = 3;
    static const int TREE = 4;
    static const int GHOST = 5;
    static const int FIRE = 6;
    static const int SPIDER = 7;

    static void init(LiquidCrystal lcd);
    static void renderCharacter(LiquidCrystal lcd, int character);
};

const String Characters::characterNames[4] = {
    "ROCKET",
    "BELL",
    "HUMAN",
    "SPONGE BOB",
};

const String Characters::obstacleNames[4] = {
    "TREE",
    "GHOST",
    "FIRE",
    "SPIDER",
};

byte ROCKET_BYTES[] = {
    B00100,
    B01010,
    B10001,
    B10101,
    B10001,
    B11011,
    B10101,
    B10001};

byte BELL_BYTES[] = {
    B00000,
    B00100,
    B01110,
    B01110,
    B01110,
    B11111,
    B00000,
    B00100};

byte HUMAN_BYTES[] = {
    B01110,
    B01110,
    B01110,
    B00101,
    B01110,
    B10100,
    B01110,
    B10001};

byte TREE_BYTES[] = {
    B00100,
    B01010,
    B01010,
    B10001,
    B10001,
    B11111,
    B00100,
    B01110};

byte GHOST_BYTES[] = {
    B01110,
    B10101,
    B11111,
    B11011,
    B01110,
    B01110,
    B00100,
    B00000};

byte SPONGE_BOB_BYTES[] = {
    B11111,
    B10101,
    B11111,
    B11111,
    B01110,
    B01110,
    B01010,
    B11011};

byte FIRE_BYTES[] = {
    B00000,
    B00000,
    B00100,
    B10101,
    B11111,
    B11111,
    B11111,
    B01110};

byte SPIDER_BYTES[] = {
    B10001,
    B10001,
    B11111,
    B01110,
    B01110,
    B11111,
    B10001,
    B10001};

void Characters::init(LiquidCrystal lcd)
{
    lcd.createChar(0, ROCKET_BYTES);
    lcd.createChar(1, BELL_BYTES);
    lcd.createChar(2, HUMAN_BYTES);
    lcd.createChar(3, SPONGE_BOB_BYTES);
    lcd.createChar(4, TREE_BYTES);
    lcd.createChar(5, GHOST_BYTES);
    lcd.createChar(6, FIRE_BYTES);
    lcd.createChar(7, SPIDER_BYTES);
}

void Characters::renderCharacter(LiquidCrystal lcd, int character)
{
    lcd.write(byte(character));
}
