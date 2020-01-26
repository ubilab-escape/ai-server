/*
 * This class describe all stuff related to displaying information on the matrix
 */

#include "Arduino.h"
#include "Display.h"
#define CLOCK_PIN 0
// init LED strip and other variables 
//Adafruit_NeoPixel Display::strip = Adafruit_NeoPixel(LED_COUNT , LED_PIN, LED_TYPE + LED_SPEED); 
uint32_t Display::i = 0;
uint32_t Display::j = 0;
byte Display::animationType = RANDOM_BLINKING;
volatile SemaphoreHandle_t timerSemaphore = NULL;

Colour Display::animCol=Colour(0,0,120);

CRGBArray<LED_COUNT> leds;


void Display::DisplayInit() // Init of the LED display
{
  
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_COUNT);
  FastLED.setBrightness(LED_BRITENESS);
}
void Display::startAnimation(byte type, byte g, byte r, byte b) // Starts timer and animation on the display
{
  
  animationType = type;
  animCol.r = r;
  animCol.g = g;
  animCol.b = b;
 

}
void Display::setBriteness(int br)
{
  FastLED.setBrightness(br);
}
void Display::calculateAndShowAnimation()
{
  
    switch (animationType)
    {
      break;
      case RANDOM_BLINKING:
      {
        
        for(uint16_t i=0; i<LED_COUNT; i++) {
          int r = random(100);
          if (r>60)
          leds[i]=CRGB( animCol.r,animCol.g,animCol.b);
          else
          leds[i]=CRGB( 0,0,0);
        }
      }
      break;
    }
    
    
    j++;

  //critical part. Nobody can interrupt writing to LEDs

FastLED.show();
    

}
