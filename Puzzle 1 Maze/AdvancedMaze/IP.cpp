#include "Arduino.h"
#include "IP.h"


void IP::clearIP()
{
  IPadress = "";
  for (byte i = 1;i<5;i++)
  groups[i] = 0;
}

void IP::addDigit( char ch)
{
  int tmp =groups[currentGroup]*10+ch-'0';
  if (tmp>255) groups[currentGroup] = 0; 
  groups[currentGroup] = groups[currentGroup]*10;
  groups[currentGroup] = groups[currentGroup]+ch-'0';
}

String IP::getIP()
{
  IPadress = String(groups[0],DEC)+"."+String(groups[1],DEC)+"."+String(groups[2],DEC)+"."+String(groups[3],DEC);
  return IPadress;
}

bool IP::check()
{
  return (groups[0] == IP_GROUP_A) &&(groups[1] == IP_GROUP_B) &&(groups[2] == IP_GROUP_C) &&(groups[3] == IP_GROUP_D);
}
