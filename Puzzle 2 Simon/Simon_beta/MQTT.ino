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
const char* Maze = "8/puzzle/maze";
const char* Simon = "8/puzzle/simon";


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
    //Serial.println(error);
    return;
  }

  //first puzzle controller handles only method and state
  String Method = doc["method"];
  String State = doc["state"];
  String Data = doc["data"]; 
  String Topic = topic;
  
  if(Topic == Maze && Method == "STATUS" && State == "solved") // Waiting for maze to be solved to start  
  { 
    mazesolved = true;    
  }
  
    if(Topic == Simon && Method == "TRIGGER" && State == "inactive") // Operator instruction → SIMON FORCE INACTIVE
  { 
    mazesolved = false;
  }
  
    if(Topic == Simon && Method == "TRIGGER" && State == "active")  // Operator instruction → SIMON FORCE ACTIVE
  {  
    mazesolved = true;
    loop();
  }
  
    if(Topic == Simon && Method == "TRIGGER" && State == "solved")  // Operator instruction → SIMON FORCE SOLVED
  { 
    puzzle_correct();
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
  
  // Generate the minified JSON and save it in the message buffer
  //serializeJson(doc, message);

  //send the JSON message to the specified topic
  if (client.publish(Topic, message) == false) 
  {
    Serial.println("Error sending message");
  }

    if (client.publish(Topic, message) == true) 
  {
    Serial.println("Message sent");
  }
}

/*
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
}*/
