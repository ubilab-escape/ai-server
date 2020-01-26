
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
  static void MQTTPublish(String st);
  static void MQTTLightControl(String st, String dat);
  static void MQTTLightControlRack( String dat);
  static void clientloop();
   static String state;
   static String newstate;
    static bool statechanged;
  private:
 
  
};

#endif
