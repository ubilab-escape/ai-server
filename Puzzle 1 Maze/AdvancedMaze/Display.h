

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

#define RED   0xFF0000
#define GREEN 0x00FF00
#define BLUE  0x0000FF

//#define FASTLED_INTERNAL
//#define FASTLED_ALLOW_INTERRUPTS 0

#include "Arduino.h"
#include "Settings.h" 
#include "esp_system.h"
//#include <Adafruit_NeoPixel.h>
#include <FastLED.h>
#include "Colour.h"
#include "Maze.h"



 class Display
{
  
  public:
  
  static void DisplayInit();
 // static Adafruit_NeoPixel strip;
  static void startAnimation(byte type, byte r, byte g, byte b);
  static void updateGameField();
  static void calculateAndShowAnimation();
  static volatile bool frame;
  static void processInterrupt();
  static Maze maze;
  static void SetColour(int r, int g, int b);
  static byte animationType;
   static void setBriteness(int br);
  private:
  static uint32_t i,j;
  static void IRAM_ATTR animationHandler();
  //static uint32_t Wheel(byte WheelPos);
  
  static uint32_t colour;
  static Colour animCol;
  static uint32_t  gameField[LED_COUNT];
  
  
  
  
};

#endif
