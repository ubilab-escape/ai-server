/*
 * This file describes header of the color class.
 */

#ifndef Colour_h
#define Colour_h

#include "Arduino.h"

class Colour
{
  public:
    Colour(byte _r, byte _g, byte _b);
    byte r;
    byte g;
    byte b;
    byte a;
    uint32_t getRGB();
};
#endif
