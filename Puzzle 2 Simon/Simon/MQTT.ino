/*
//----------------------------------------------------------------------------------------------------------------//                            
                                        Group 8                               
                    _____ _                          _____                 
                   / ____(_)                        / ____|                
                  | (___  _ _ __ ___   ___  _ __   | (___   __ _ _   _ ___ 
                   \___ \| | '_ ` _ \ / _ \| '_ \   \___ \ / _` | | | / __|
                   ____) | | | | | | | (_) | | | |  ____) | (_| | |_| \__ \
                  |_____/|_|_| |_| |_|\___/|_| |_| |_____/ \__,_|\__, |___/
                                                                  __/ |    
                                                                 |___/     

//----------------------------------------------------------------------------------------------------------------//   
    Code based on Group 4 (Operator??) "Wifi_MQTT_Json_Motor.ino" code    

//----------------------------------------------------------------------------------------------------------------// 
*/

#include "MQTT.h"

#define DEBUG

#define MAX_MDNS_LEN 16
#define MDNS_START_ADDRESS 0

char mdnsName[MAX_MDNS_LEN] = {'\0'};

const IPAddress mqttServerIP(10,0,0,2); //Main server Ip 

const String clientId = "Group8_puzzle_simon";
const char* Maze = "8/puzzle/maze";
const char* Simon = "8/puzzle/simon";
//const String Kwargs = "{'TextType': 'ssml', VoiceId='Brian', LanguageCode='en-GB'}";

WiFiClient wifiClient;
PubSubClient client(wifiClient);


/*
--------------------------------------------------------------------------------------------------------------------------------------------------------
    Function: SETUP
     
--------------------------------------------------------------------------------------------------------------------------------------------------------
*/
void Setup() 
{
  client.setServer(mqttServerIP, 1883); // Setting server by ip address and port
  client.setCallback(Callback); // Setting callback for recieved packets
}

/*
--------------------------------------------------------------------------------------------------------------------------------------------------------
    Function: Callback
    
--------------------------------------------------------------------------------------------------------------------------------------------------------
*/
void Callback(char* topic, byte* payload, unsigned int length) 
{
  #ifdef DEBUG
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  for (int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  #endif

  //Deserialize
  StaticJsonDocument<300> doc;
  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, payload);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    //Serial.println(error);
    return;
  }

  //first puzzle controller handles only method and state
  String Method = doc["method"];
  String State = doc["state"];
  String Data = doc["data"]; 
  String Topic = topic;

  if(Topic == Simon && Method == "trigger" && State == "off")                        // Reset puzzle and puzzle state inactive
  { 
          Simon_active = false;
          Simon_solved = false;
          sta = "inactive";
          text = "waiting...";
          sta_change = true;
  }
  if(Topic == Simon && Method == "trigger" && State == "off" && Data == "skipped")   // Reset puzzle and puzzle state solved
  { 
          Simon_active = false;
          Simon_solved = true;
          sta = "solved";
          text = "skipped";
          sta_change = true;
  }
  if(Topic == Simon && Method == "trigger" && State == "on")                        // Puzzle active and starts puzzle_simon()
  { 
          Simon_active = true;
          Simon_solved = false;
          sta = "active";
          text = "";
          
  }

}

//--------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------

void Reconnect() // this void resubscribes to topics on start or in case of disconnection
{
   while (!client.connected()) 
   {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
   // if (client.connect(clientId.c_str())) 
      if (client.connect("Simon"))
      { // change clientName to name of your device
        Serial.println("connected");
        // Subscribe to all topics you need here
        client.subscribe(Maze);
        client.subscribe(Simon);
      } 
    
    else 
      {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println("try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
    client.loop();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------

void Publish(char* Topic, String Method, String State, String Data) // this void is used to send messages in topic
{   
  StaticJsonDocument<300> doc;
  Serial.print("Message to: ");
  Serial.println(Topic);
  Serial.print("Message: ");
  doc["method"] = Method;
  doc["state"] =  State;
  if(Data != "")//in case a data (integer value) was handed as parameter
  {
    doc["data"] = Data;
  }


  //create a buffer that holds the serialized JSON message
  //int msg_length = measureJson(doc) + 1;                    //measureJson return value doesn't count the null-terminator
  char message[128]; 
  serializeJson(doc, message); // Generate the minified JSON                        
  
 
  #ifdef DEBUG
  Serial.print("JSON message created for publishing: ");
  Serial.println(message);  
  #endif

  //send the JSON message to the specified topic

    if (client.publish(Topic, message) == true) 
  {
    Serial.println("Message sent");
  }
   else 
  {
    Serial.println("Error sending message");
  }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------

void Publish_t2s(char* Topic, String Method, String State, String Data) // this void is used to send messages in topic
{   
  StaticJsonDocument<1024> doc;
  Serial.print("Message to: ");
  Serial.println(Topic);
  Serial.print("Message: ");
  doc["method"] = Method;
  doc["state"] =  State;
  if(Data != "")//in case a data (integer value) was handed as parameter
  {
    doc["file_location"] = Data;
  }
  doc["play_from_file"] = true;
  
  //create a buffer that holds the serialized JSON message
  //int msg_length = measureJson(doc) + 1;                    //measureJson return value doesn't count the null-terminator
  char message[1024]; 
  serializeJson(doc, message); // Generate the minified JSON                        
  
 
  #ifdef DEBUG
  Serial.print("JSON message created for publishing: ");
  Serial.println(message);  
  #endif

  //send the JSON message to the specified topic

    if (client.publish(Topic, message) == true) 
  {
    Serial.println("Message sent");
  }
   else 
  {
    Serial.println("Error sending message");
  }
}
