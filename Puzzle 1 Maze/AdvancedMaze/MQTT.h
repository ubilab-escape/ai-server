
#ifndef MQTT_h
#define MQTT_h


#include <WiFi.h>
#include <PubSubClient.h>
#include "Arduino.h"
#include "CaseComparator.h"




 class MQTT
{
  public:
  
  static void Setup();
  static void Callback(char* topic, byte* message, unsigned int length);
  static void Reconnect();
  static String split (String s, char parser, int index);
  static void MQTTPublishMAZE(String st);
  static void MQTTPublishIP(String st);
  static void MQTTLightControl(String st, String dat);
  static void MQTTLightEverywhere(String st, String dat);
  static void MQTTLightControlRack( String dat);
  static void MQTTLightControlRackEye( String dat);
  static void clientloop();
   static String IPstate;
   static String IPnewstate;
   static String MAZEstate;
   static String MAZEnewstate;
    static bool MAZEstatechanged;
    static bool IPstatechanged;
    static String msg;
  private:
 
  
};

#endif
