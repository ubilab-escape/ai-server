
#ifndef MQTT_h
#define MQTT_h


#include <WiFi.h>
#include <PubSubClient.h>
#include "Arduino.h"




 class MQTT
{
  public:
  
  static void Setup();
  static void Callback(char* topic, byte* message, unsigned int length);
  static void Reconnect();
  static String split (String s, char parser, int index);
  private:
  
  
};

#endif
