#include <ArduinoJson.h>

#include "Arduino.h"
#include "MQTT.h"
#include "Display.h"

StaticJsonDocument<200> doc;
const int capacity = JSON_OBJECT_SIZE(3);

WiFiClient espClient;
PubSubClient client(espClient);
 
const char*  mqtt_server =  "10.0.0.2";
//const char*  mqtt_server =  "192.168.0.199";


const char* MQTTclientName =  "8_rack";


String  MQTT::state = "inactive";
const char* MQTTtopic =  "8/rack";
const char* LightControllerTopic =  "2/ledstrip/serverroom";


void MQTT::Setup() 
{
  client.setServer(mqtt_server, 1883); // Setting server by ip address and port
  client.setCallback(Callback); // Setting callback for recieved packets
}
/*
 * This void is processing incoming messages as soon as they arrived. 
 * Dont forget to subscribe on required topics in Reconnect void.
 * 
 */
void MQTT::Callback(char* topic, byte* message, unsigned int length) 
{
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);
  Serial.print(". Message: ");
  Serial.println((char *) message);
  Serial.println();
  DeserializationError error = deserializeJson(doc, message);
  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }
    String da = doc["data"];
    String me = doc["method"];
    String st = doc["state"];
    String t = topic;
    doc.clear();
    if (t == MQTTtopic&&me== "TRIGGER" && st== "rgb") // this should be changed to required topic name
    {
     //here you can process incoming messages on specific topic     
      Display().startAnimation(RANDOM_BLINKING, split(da,',',0).toInt(), split(da,',',1).toInt(), split(da,',',2).toInt());
   
    }
    if (t == MQTTtopic&&me== "TRIGGER" && st== "rgb"&&da=="0,0,120") // this should be changed to required topic name
    {
     //here you can process incoming messages on specific topic     
      Display().startAnimation(RANDOM_BLINKING, 0,0,120);
   
    }
    if (t == MQTTtopic&&me== "TRIGGER" && st== "eye"&&da=="0,0,120") // this should be changed to required topic name
    {
     //here you can process incoming messages on specific topic     
      Display().startAnimation(EYE_D, 0,0,120);
   
    }
    if (t == MQTTtopic&&me== "TRIGGER" && st== "power") // this should be changed to required topic name
    {
     //here you can process incoming messages on specific topic     
      if (da == "on")
      {
        Display().setBriteness(LED_BRITENESS);
      }
      if (da == "off")
      {
        Display().setBriteness(0);
      }
   
    }
    if (t == MQTTtopic&&me== "TRIGGER" && st== "brightness") // this should be changed to required topic name
    {
     //here you can process incoming messages on specific topic
     Display().setBriteness(da.toInt());     
     
   
    }
      
      
    // add as much cases as you have a subscriptions
}

void MQTT::clientloop() 
{
   if (client.connected()) 
    client.loop();
}
void MQTT::Reconnect() // this void resubscribes to topics on start or in case of disconnection
{
   if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("Rack")) 
    { // change clientName to name of your device
      Serial.println("connected");
      // Subscribe to all Topicks you need here
     
      client.subscribe(MQTTtopic);
      
    } 
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      
      yield();
    }
    }
    else
    {
        
    }
}
void MQTT::MQTTPublish( String state) // this void is used to send messages in topic
{
  //doc.clear();
  Serial.print("Message sent on topic: ");
  Serial.println(MQTTtopic);
  Serial.print(". Message: ");
  doc["method"] = "STATUS";
  doc["state"] = "inactive";
  char output[128];
  serializeJson(doc, output);
  Serial.println(output);
  client.publish(MQTTtopic, output);
  //doc.clear();
}


String MQTT::split(String s, char parser, int index) {
  String rs="";
  int parserIndex = index;
  int parserCnt=0;
  int rFromIndex=0, rToIndex=-1;
  while (index >= parserCnt) {
    rFromIndex = rToIndex+1;
    rToIndex = s.indexOf(parser,rFromIndex);
    if (index == parserCnt) {
      if (rToIndex == 0 || rToIndex == -1) return "";
      return s.substring(rFromIndex,rToIndex);
    } else parserCnt++;
  }
  return s.substring(rFromIndex,s.length());;
}
