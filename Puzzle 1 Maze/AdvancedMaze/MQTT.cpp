#include <ArduinoJson.h>

#include "Arduino.h"
#include "MQTT.h"
#include "Display.h"

StaticJsonDocument<200> doc;
const int capacity = JSON_OBJECT_SIZE(3);

WiFiClient espClient;
PubSubClient client(espClient);
 
const char*  mqtt_server =  "10.0.0.2";


const char* MQTTclientName =  "8_Maze";
const char* MQTTtpoic =  "8/Maze";


const char* previousPuzzleTopic =  "GroupN/Puzzle";
const char* LightControllerTopic =  "2/ledstrip/serverroom";

bool  MQTT::arrived = false;
int  MQTT::state =0;

void MQTT::Setup() 
{
  client.setServer(mqtt_server, 1883); // Setting server by ip address and port
  client.setCallback(MQTT().Callback); // Setting callback for recieved packets
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
  //Serial.println(message);
  Serial.println();
  DeserializationError error = deserializeJson(doc, message);
  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }
    String da = doc["DATA"];
    String me = doc["METHOD"];
    String st = doc["STATE"];
    String t = topic;
    if (t == previousPuzzleTopic&&me== "STATUS" && st == "solved") // this should be changed to required topic name
    {
     //here you can process incoming messages on specific topic
      
      arrived = true;
      state = 1;
      
     
    }
    
    if (t == LightControllerTopic&&me== "TRIGGER" && st== "rgb"&&(Display().animationType!=GAME)) // this should be changed to required topic name
    {
     //here you can process incoming messages on specific topic     
      Display().startAnimation(RANDOM_BLINKING, split(da,',',0).toInt(), split(da,',',1).toInt(), split(da,',',2).toInt());
   
    }
   
    // add as much cases as you have a subscriptions
}

void MQTT::Reconnect() // this void resubscribes to topics on start or in case of disconnection
{
   if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("Maze")) 
    { // change clientName to name of your device
      Serial.println("connected");
      // Subscribe to all Topicks you need here
      client.subscribe(previousPuzzleTopic);
      client.subscribe(LightControllerTopic);
   
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
      client.loop();
    }
}
void MQTT::MQTTPublish( char* state) // this void is used to send messages in topic
{
  Serial.print("Message sent on topic: ");
  Serial.println(MQTTtpoic);
  Serial.print(". Message: ");
  doc["METHOD"] = "STATUS";
  doc["STATE"] = state;
  char output[128];
  serializeJson(doc, output);
  Serial.println(output);
  client.publish(MQTTtpoic, output);
}
void MQTT::MQTTLightControl(char* state, char* dat)
{
  Serial.print("Message sent on topic: ");
  Serial.println(LightControllerTopic);
  Serial.print(". Message: ");
  doc["METHOD"] = "TRIGGER";
  doc["STATE"] = state;
  doc["DATA"] = dat;
  char output[128];
  serializeJson(doc, output);
  Serial.println(output);
  client.publish(LightControllerTopic, output);
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
  return rs;
}
