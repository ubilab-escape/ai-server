/*
 * Just a point
 */

#ifndef Point_h
#define Point_h

#include "Arduino.h"

class Point
{
  public:
    Point(byte _x, byte _y);
    byte x;
    byte y;
};
#endif
