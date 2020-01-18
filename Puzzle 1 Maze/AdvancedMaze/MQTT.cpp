#include "Arduino.h"
#include "MQTT.h"


WiFiClient espClient;
PubSubClient client(espClient);
 
const char*  mqtt_server =  "192.168.0.199";


const char* MQTTclientName =  "Maze";


const char* previousPuzzleTopic =  "GroupN/Puzzle";
const char* previousPuzzleDoneMSG =  "Puzzle_Done";

const char* questControllerTopic =  "GroupN/GameController";
const char* questControllerGameStarted =  "GameStarted";


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
    if (topic == previousPuzzleTopic) // this should be changed to required topic name
    {
     //here you can process incoming messages on specific topic
      if ((char*)message == previousPuzzleDoneMSG) 
      {
      arrived = true;
      state = 2;
      }
     
    }
    
    if (topic == questControllerTopic) // this should be changed to required topic name
    {
     //here you can process incoming messages on specific topic
      if ((char*)message == questControllerGameStarted)
      {
      arrived = true;
      state = 1;
      }
      
    }
   
    // add as much cases as you have a subscriptions
  }

void MQTT::Reconnect() // this void resubscribes to topics on start or in case of disconnection
{
   while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("Maze")) 
    { // change clientName to name of your device
      Serial.println("connected");
      // Subscribe to all Topicks you need here
      client.subscribe(previousPuzzleTopic);
      client.subscribe(questControllerTopic);
      
    } 
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
    }
}
void MQTT::MQTTPublish( char* top,  char* val) // this void is used to send messages in topic
{
  Serial.print("Message sent on topic: ");
  Serial.println(top);
  Serial.print(". Message: ");
  Serial.println(val);
  client.publish(top, val);
}
