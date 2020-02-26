/*
 * This is a colour class. This class helps to operate with colours using only one object
 */

#include "Colour.h";

Colour::Colour(byte _r = 0, byte _g = 0, byte _b = 0)
{
  r = _r;
  g = _g;
  b = _b;
}

uint32_t Colour::getRGB()
{
  uint32_t res = 0;
  res & r << 8;
  res & g << 8;
  res & b;
}
