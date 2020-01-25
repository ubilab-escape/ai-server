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
    Code based on Group 4 "Wifi_MQTT_Json_Motor.ino"  

//----------------------------------------------------------------------------------------------------------------// 
*/

#include "MQTT.h"

#define DEBUG

#define MAX_MDNS_LEN 16
#define MDNS_START_ADDRESS 0

//mdns - broadcasting name for OTA
char mdnsName[MAX_MDNS_LEN] = {'\0'};

const IPAddress mqttServerIP(10,0,0,2); //Main server Ip 

const String clientId = "Group8_puzzle_simon";
const char* Maze = "MQTT_8_puzzle_maze";


WiFiClient wifiClient;
PubSubClient client(wifiClient);

long lastMsg = 0;
char msg[50];
int value = 0;

void wifi()
{  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  mdnsUpdate = millis();
  while (WiFi.waitForConnectResult() != WL_CONNECTED) 
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
}

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
    
    IMPORTANTE: Falta agregar las condiciones propias de Simon 
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
    return;
  }

  //first puzzle controller handles only method and state
  String Method = doc["method"];
  String State = doc["state"];
  String Data = doc["data"]; //should be 0 if not data argument was received (see https://arduinojson.org/v6/doc/deserialization/ --> 3.3.3 in pdf) 

  if(Method == "trigger" && State == "solved")
  { // waiting for maze to be solved

    //set 
    mazesolved = true;

    //respond to activation message
    //{"method":"STATUS","state":"active", "data":"opening"}
    Publish("MQTT_8_puzzle_simon", "STATUS", "active", "");

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
    if (client.connect(clientId.c_str())) 
      { // change clientName to name of your device
        Serial.println("connected");
        // Subscribe to all topics you need here
        client.subscribe(Maze);
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

void Publish(String topic_name, String Method, String State, String Data) // this void is used to send messages in topic
{   
  //Example:
  //                              {"method":"STATUS",  "state":"active",  "data":"closing"}
  //   mqtt_publish("MQTT_4_door_entrance", "STATUS",          "active",         "closing");

  //Create the JSON format
  //const int capacity = JSON_ARRAY_SIZE(length_of_array) + 2*JSON_OBJECT_SIZE(3)
  //allocate a Json Document
  StaticJsonDocument<300> doc;
  doc["method"] = Method;
  doc["state"] = State;


  //in case a data (integer value) was handed as parameter
  if(Data != "")
  {
    doc["data"] = Data;
  }

  //create a buffer that holds the serialized JSON message
  int msg_length = measureJson(doc) + 1;                    //measureJson return value doesn't count the null-terminator
  char JSONmessageBuffer[msg_length];                         
  // Generate the minified JSON and send it to the Serial port.
  #ifdef DEBUG
  Serial.print("JSON message created for publishing: ");
  serializeJson(doc, Serial);
  Serial.println();
  #endif
  // Generate the minified JSON and save it in the message buffer
  serializeJson(doc, JSONmessageBuffer, sizeof(JSONmessageBuffer));

  //send the JSON message to the specified topic
  if (client.publish(topic_name.c_str(), JSONmessageBuffer) == false) 
  {
    Serial.println("Error sending message");
  }

    if (client.publish(topic_name.c_str(), JSONmessageBuffer) == true) 
  {
    Serial.println("Message sent");
  }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------

void initMDNS() {
  // Load the MDNS name from eeprom
  EEPROM.begin(2*MAX_MDNS_LEN);
  
  char * name = getMDNS();
  if (strlen(name) == 0) 
  {
    Serial.println(F("Info:Sth wrong with mdns"));
    //use clientID as default mdns name
    strcpy(name, clientId.c_str());
  }
  // Setting up MDNs with the given Name
  Serial.print(F("Info:MDNS Name: ")); Serial.println(name);
  if (!MDNS.begin(String(name).c_str())) 
  {             // Start the mDNS responder for esp8266.local
    Serial.println(F("Info:Error setting up MDNS responder!"));
  }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------

char * getMDNS() 
{
  uint16_t address = MDNS_START_ADDRESS;
  uint8_t chars = 0;
  EEPROM.get(address, chars);
  address += sizeof(chars);
  if (chars < MAX_MDNS_LEN) 
  {
    EEPROM.get(address, mdnsName);
  }
  return mdnsName;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------

void writeMDNS(const char * newName) {
  uint16_t address = MDNS_START_ADDRESS;
  uint8_t chars = strlen(newName);
  EEPROM.put(address, chars);
  address += sizeof(chars);
  for (uint8_t i = 0; i < chars; i++) EEPROM.put(address+i, newName[i]);
  EEPROM.put(address+chars, '\0');
  EEPROM.commit();
}
