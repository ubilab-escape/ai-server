
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
  static void MQTTPublish(char* top, char* val);
  static bool arrived;
  static int state;
  private:
  
  
};

#endif
