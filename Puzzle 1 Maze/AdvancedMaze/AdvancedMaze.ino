#include <Keypad.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "HardwareSerial.h"
#include "GameController.h";
#include "IP.h";
#include "MQTT.h";


const char* ssid = "ubilab_wifi";
const char* password = "ohg4xah3oufohreiPe7e";
//const char* ssid = "WirelessMan";
//const char* password = "Rahatlukum75";

HardwareSerial MySerial(1);

TaskHandle_t WiFi_Task_handle;
TaskHandle_t MQTT_Task_handle;
TaskHandle_t MQTTcon_Task_handle;

GameController maze;

const byte rows = 4; //four rows
const byte cols = 4; //three columns
 char keys[rows][cols] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'#','0','*', 'D'}
};
 byte colPins[cols] = {12, 14, 27, 26}; //connect to the row pinouts of the keypad
 byte rowPins[rows] = {0, 33, 32, 13}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

IP ip = IP();


int workmode  = 0;


void setup() {
MySerial.begin(9600, SERIAL_8N1, 17, 16);
Serial.begin(9600);
delay(1000);
Serial.println("S4");


xTaskCreate(
                    WiFi_Task,          /* Task function. */
                    "WiFi_Task",        /* String with name of task. */
                    10000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    3,                /* Priority of the task. */
                    &WiFi_Task_handle);            /* Task handle. */
xTaskCreate(
                    MQTTcon_Task,          /* Task function. */
                    "MQTTcon_Task",        /* String with name of task. */
                    40000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    &MQTTcon_Task_handle);            /* Task handle. */
xTaskCreate(
                    LED_Task,          /* Task function. */
                    "LED_Task",        /* String with name of task. */
                    10000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    2,                /* Priority of the task. */
                    NULL);            /* Task handle. */      
xTaskCreate(
                    OTA_Task,          /* Task function. */
                    "OTA_Task",        /* String with name of task. */
                    10000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */  
xTaskCreate(
                    MQTT_Task,          /* Task function. */
                    "MQTT_Task",        /* String with name of task. */
                    30000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    &MQTT_Task_handle);            /* Task handle. */  
xTaskCreate(
                    Keyboard_Task,          /* Task function. */
                    "Keyboard_Task",        /* String with name of task. */
                    30000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */                                                      
vTaskSuspend(MQTTcon_Task_handle);
vTaskSuspend(MQTT_Task_handle);
Display().startAnimation(RANDOM_BLINKING, 0, 0, 120);
}

void loop() {
delay(500);
if (workmode == 1)
{
  if (ip.check()) 
      {
      Serial.println("S3");
      workmode =0;
      ip.clearIP();
      MQTT().msg ="IP solved";
      Display().startAnimation(RANDOM_BLINKING, 0, 120, 0);
      MQTT().MQTTLightControlRack("0,120,0");
      delay(5000);
      MQTT().MQTTPublishIP("solved");
      }
}
if (workmode == 2)
{
  if (maze.isCompleted)
  {
     workmode = 0;
     MQTT().MQTTPublishMAZE("solved");
     Display().startAnimation(RANDOM_BLINKING, 0, 120, 0);
     MQTT().MQTTLightControlRack("0,120,0");
    // MQTT().MQTTLightControl("rgb","30,30,30");
  }
}


}

void WiFi_Task( void * parameter )
{
 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, password);
 while (WiFi.waitForConnectResult() != WL_CONNECTED) 
  {
    //Serial.println("Connection Failed! Rebooting...");
    ESP.restart();
  }
   if(WiFi.waitForConnectResult() == WL_CONNECTED)  
   {
    //Serial.println("Connected!!!");
    vTaskResume(MQTTcon_Task_handle);
  }
 for(;;)
  {
  if (WiFi.waitForConnectResult() != WL_CONNECTED) 
  {
    //Serial.println("Connection Failed! Rebooting...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
  }
  delay(5000);
  }
}
void MQTTcon_Task( void * parameter )
{
delay(5000);
MQTT().Setup() ;
MQTT().Reconnect();
vTaskResume(MQTT_Task_handle);
MQTT().MQTTLightControlRack("0,0,120");
MQTT().MQTTPublishMAZE("inactive");
MQTT().MQTTPublishIP("inactive");
 for(;;)
  {
    delay(10000);
    MQTT().Reconnect();
    MQTT().MQTTPublishMAZE(MQTT().MAZEstate);
    MQTT().MQTTPublishIP(MQTT().IPstate);
    if (MQTT().MAZEstate == "inactive")
      {
        
      }
      
  }
}
void MQTT_Task( void * parameter )
{
delay(10000);
 for(;;)
  {
    delay(500);
    MQTT().clientloop();
    if (MQTT().MAZEstatechanged)
    {
      if (MQTT().MAZEnewstate == "active")
      {
        MQTT().msg ="Forced activation";
        maze.startGame(MODE_NORMAL_TEAMPLAY, 1);
        MQTT().MQTTLightControlRack("0,0,120");
        workmode = 2;
      }
      if (MQTT().MAZEnewstate == "inactive")
      {
        MQTT().msg ="Waiting...";
        Display().startAnimation(RANDOM_BLINKING, 0, 0, 120);
        MQTT().MQTTLightControlRack("0,0,120");
        workmode = 0;
      }
      if (MQTT().MAZEnewstate == "solved")
      {
        MQTT().msg ="Forced solution";
        Display().startAnimation(RANDOM_BLINKING, 0, 120, 0);
        MQTT().MQTTLightControlRack("0,120,0");
        workmode = 0;
        MQTT().MQTTPublishMAZE("solved");
      }
      MQTT().MQTTPublishMAZE(MQTT().MAZEnewstate);
      //MQTT().state ==  MQTT().newstate;
      MQTT().MAZEstatechanged = false;
    }
    if (MQTT().IPstatechanged)
    {
      if (MQTT().IPnewstate == "active")
      {
        MQTT().MQTTSpeech(IPPhrase);
        MQTT().msg ="Forced activation";
        Serial.println("S1");
        workmode = 1;
        Display().startAnimation(EYE_D, 0, 0, 120);
        MQTT().MQTTLightControlRackEye("0,0,120");
        
      }
      if (MQTT().IPnewstate == "inactive")
      {
        Serial.println("S4");
        MQTT().msg ="Waiting...";
        Display().startAnimation(RANDOM_BLINKING, 0, 0, 120);
        MQTT().MQTTLightControlRack("0,0,120");
        workmode = 0;
      }
      if (MQTT().IPnewstate == "solved")
      {
        Serial.println("S3");
        MQTT().msg ="Forced solution";
        Display().startAnimation(RANDOM_BLINKING, 0, 120, 0);
        MQTT().MQTTLightControlRack("0,120,0");
        workmode = 0;
        MQTT().MQTTPublishIP("solved");
      }
      MQTT().MQTTPublishIP(MQTT().IPnewstate);
      //MQTT().state ==  MQTT().newstate;
      MQTT().IPstatechanged = false;
     
    }
  }
}
void OTA_Task( void * parameter )
{
 ArduinoOTA.setHostname("Maze");
 ArduinoOTA.onStart([]() 
    {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      
    })
    .onEnd([]() 
    {
      
    })
    .onProgress([](unsigned int progress, unsigned int total) {
     
    })
    .onError([](ota_error_t error) 
    {
      /*Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");*/
    });

 ArduinoOTA.begin();
 for(;;)
 {
  ArduinoOTA.handle();
  delay(200);
 }
}
void LED_Task( void * parameter )
{
  Display::DisplayInit();
  Display().startAnimation(RANDOM_BLINKING, 0, 0, 120);
  for(;;)
  {
  Display().calculateAndShowAnimation();
  delay(LED_UPDATE_TIME);
  }
 }
 void Keyboard_Task( void * parameter )
{
  keypad.setDebounceTime(50);
  for(;;)
  {
  delay(100);
  char key = keypad.getKey();
  if (key != NO_KEY){
    if (workmode == 2)
    {
    switch(key)
    {
   
      case('2'):
      {
        maze.step_up();
      }
      break;
      case('4'):
      {
        maze.step_left();
      }
      break;
      case('8'):
      {
        maze.step_down();
      }
      break;
      case('6'):
      {
        maze.step_right();
      }
      break;
   }
  }
  if (workmode == 1)
  {
  
   switch(key)
   {
      case('A'):
      {
        ip.currentGroup = 0;
      }
      break;
      case('B'):
      {
        ip.currentGroup = 1;
      }
      break;
      case('C'):
      {
        ip.currentGroup = 2;
      }
      break;
      case('D'):
      {
        ip.currentGroup = 3;
      }
      break;
      default:
      {
        ip.addDigit(key);
        Serial.println("I"+ip.getIP()+"E");
      }
  }
  }
  }
 }
}
