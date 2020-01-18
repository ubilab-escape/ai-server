/*
 * This class describes IP insert mode. Address is entered via keyboard
 */

#ifndef IP_h
#define IP_h

#define IP_GROUP_A 128
#define IP_GROUP_B 0
#define IP_GROUP_C 32
#define IP_GROUP_D 16

#include "Arduino.h"

class IP
{
  public:
  String IPadress;
  byte groups[4];
  void clearIP();
  void addDigit(char ch);
  String getIP();
  byte currentGroup;
  bool check();
};

#endif
