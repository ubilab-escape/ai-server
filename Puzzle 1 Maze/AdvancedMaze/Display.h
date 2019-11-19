/*
 * This class describe all stuff related to displaying information on the matrix
 */


#ifndef Display_h
#define Display_h

// Animation types
#define GAME 0
#define RAINBOW 1
#define RAINBOW_FLOW 2
#define PULSE 3
#define RANDOM_BLINKING 4




#include "Arduino.h"
#include "Settings.h" 
#include "esp_system.h"
#include <Adafruit_NeoPixel.h>
#include "Colour.h"
#include "Maze.h"


 class Display
{
  
  public:
  Display();
  static Adafruit_NeoPixel strip;
  static void startAnimation(byte type, byte r, byte g, byte b);
  static void updateGameField();
  static void calculateAndShowAnimation();
  static volatile bool frame;
  
  static Maze maze;
  private:
  static uint32_t i,j;
  static void IRAM_ATTR animationHandler();
  static uint32_t Wheel(byte WheelPos);
  static byte animationType;
  static uint32_t colour;
  static Colour animCol;
  static byte neopix_gamma[256];
  static uint32_t  gameField[LED_COUNT];
  
  
  
  
};

#endif
