/*
 * This class describe all stuff related to displaying information on the matrix
 */

#include "Arduino.h"
#include "Display.h"

// init LED strip and other variables 
Adafruit_NeoPixel Display::strip = Adafruit_NeoPixel(LED_COUNT , LED_PIN, LED_TYPE + LED_SPEED); 
uint32_t Display::i = 0;
uint32_t Display::j = 0;
byte Display::animationType = PULSE;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
Colour Display::animCol=Colour(0,0,120);
Maze Display::maze = Maze();

byte Display::neopix_gamma[256] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
        1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
        2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
        5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
        10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
        17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
        25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
        37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
        51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
        69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
        90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
       115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
       144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
       177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
      215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 }; // This array is used by several animations
  

Display::Display() // Init of the LED display
{
  
  strip.setBrightness(LED_BRITENESS);
  strip.begin();
}
void Display::startAnimation(byte type, byte r, byte g, byte b) // Starts timer and animation on the display
{
  hw_timer_t *timer = NULL;
  timer = timerBegin(0, 80, true);                  //timer 0, div 80
  timerAttachInterrupt(timer, &animationHandler, true);  //attach callback
  timerAlarmWrite(timer, LED_UPDATE_TIME * 1000, true); //set time in us
  timerAlarmEnable(timer); // enable timer 
  animationType = type;
  maze.InitMaze(MODE_CHILDISH);
}

void IRAM_ATTR Display::animationHandler() // Interrupt handler called by timer. Here animations are updating
{
    switch (animationType)
    {
      case GAME:
      {
        updateGameField();
      }
      break;
      case RAINBOW:
      {
        for(i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, Wheel((i+j) & 255));
        }
      }
      break;
      case RAINBOW_FLOW:
      {
        for(i=0; i< strip.numPixels(); i++) {
        strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
        }
      }
      break;
      case PULSE:
      {
        
        for(uint16_t i=0; i<strip.numPixels(); i++) {
          strip.setPixelColor(i, strip.Color(animCol.r,animCol.g,animCol.b, neopix_gamma[j] ) );
        }
      }
      break;
      case RANDOM_BLINKING:
      {
        
        for(uint16_t i=0; i<strip.numPixels(); i++) {
          int r = random(100);
          if (r>60)
          strip.setPixelColor(i, strip.Color(animCol.r,animCol.g,animCol.b, neopix_gamma[j] ) );
          else
          strip.setPixelColor(i, strip.Color(0,0,0, 0 ) );
        }
      }
      break;
    }
    
    
    j++;

  //critical part. Nobody can interrupt writing to LEDs
  portENTER_CRITICAL_ISR(&timerMux); 
   strip.show(); // It is safe to use digitalRead/Write here if you want to toggle an output here
  portEXIT_CRITICAL_ISR(&timerMux);
  //end of the critical part. Nobody can interrupt writing to LEDs
  
}

uint32_t Display::Wheel(byte WheelPos) { // Support function for the animation. Allows to create raibow easily by using HSV color table
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
void Display::updateGameField() // Function which updates gaming field and displays it
{
  maze.getColorArray();
  for (int i=0;i<LED_COUNT;i++)
  {
    strip.setPixelColor(i, strip.Color(maze.colourArray[i][1],maze.colourArray[i][0],maze.colourArray[i][2], LED_BRITENESS ) );
  }
}
