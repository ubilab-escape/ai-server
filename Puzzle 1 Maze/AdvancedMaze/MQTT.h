
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
  static void MQTTPublish(char* state);
  static void MQTTLightControl(char* state, char* dat);
  static bool arrived;
  static int state;
  static String split (String s, char parser, int index);
  private:
  
  
};

#endif