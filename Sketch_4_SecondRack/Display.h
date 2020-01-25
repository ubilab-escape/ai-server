

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



 class Display
{
  
  public:
  
  static void DisplayInit();
 // static Adafruit_NeoPixel strip;
  static void startAnimation(byte type, byte r, byte g, byte b);
  static void calculateAndShowAnimation();
  static byte animationType;
  private:
  static uint32_t i,j;
  
  static uint32_t colour;
  static Colour animCol;
  
  
  
  
};

#endif
