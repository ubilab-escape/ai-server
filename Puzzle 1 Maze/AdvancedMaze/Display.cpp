/*
 * This class describe all stuff related to displaying information on the matrix
 */

#include "Arduino.h"
#include "Display.h"
#define CLOCK_PIN 0
// init LED strip and other variables 
//Adafruit_NeoPixel Display::strip = Adafruit_NeoPixel(LED_COUNT , LED_PIN, LED_TYPE + LED_SPEED); 
#define LED_RMT_TX_GPIO 23
uint32_t Display::i = 0;
uint32_t Display::j = 0;
byte Display::animationType = GAME;
volatile SemaphoreHandle_t timerSemaphore = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
Colour Display::animCol=Colour(0,0,120);
Maze Display::maze = Maze();
volatile float interrupt = false;
volatile bool Display::frame;
CRGBArray<LED_COUNT> leds;


void Display::DisplayInit() // Init of the LED display
{
  
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_COUNT);
  FastLED.setBrightness(LED_BRITENESS);
  hw_timer_t *timer = NULL;
  timer = timerBegin(1, 80, true);                  //timer 0, div 80
  timerAttachInterrupt(timer, &animationHandler, true);  //attach callback
  timerAlarmWrite(timer, LED_UPDATE_TIME * 1000, true); //set time in us
  // enable timer 
  //timerAlarmEnable(timer);
}
void Display::startAnimation(byte type, byte r, byte g, byte b) // Starts timer and animation on the display
{
  
  animationType = type;
  animCol.r = r;
  animCol.g = g;
  animCol.b = b;
 

}
void Display::calculateAndShowAnimation()
{
  
    switch (animationType)
    {
      case GAME:
      {
        updateGameField();
      }
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
void Display::SetColour(int r, int g, int b)
{
   for(uint16_t i=0; i<LED_COUNT; i++) {
          //leds[i]=CRGB( r,g,b);
        }
        //FastLED.show();
}
void IRAM_ATTR Display::animationHandler() // Interrupt handler called by timer. Here animations are updating
{
   
  portENTER_CRITICAL_ISR(&timerMux);
  interrupt = true;
  
  portEXIT_CRITICAL_ISR(&timerMux);
  // xSemaphoreGiveFromISR(timerSemaphore, NULL);
  
}

void Display::updateGameField() // Function which updates gaming field and displays it
{
  maze.getColorArray();
  for (int i=0;i<LED_COUNT;i++)
  {
    leds[i] = CRGB(maze.colourArray[i][0],maze.colourArray[i][1],maze.colourArray[i][2]);
  }
  FastLED.show();
}

void Display::processInterrupt()
{
 
 if (interrupt){
  calculateAndShowAnimation();
  
  interrupt=false;
  
  }
  
}
