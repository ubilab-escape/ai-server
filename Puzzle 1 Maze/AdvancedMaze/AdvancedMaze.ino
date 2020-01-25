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

HardwareSerial MySerial(1);

TaskHandle_t WiFi_Task_handle;
TaskHandle_t MQTT_Task_handle;

GameController maze;



//const char* ssid = "ubilab_wifi";
//const char* password = "ohg4xah3oufohreiPe7e";
const char* ssid = "WirelessMan";
const char* password = "Rahatlukum75";


const byte rows = 4; //four rows
const byte cols = 4; //three columns
char keys[rows][cols] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'#','0','*', 'D'}
};
byte rowPins[rows] = {21, 19, 18, 5}; //connect to the row pinouts of the keypad
byte colPins[cols] = {12, 22, 4, 0}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

IP ip = IP();




int workmode  = 0;


void setup() {
MySerial.begin(115200, SERIAL_8N1, 16, 17);
Serial.begin(115200);
MySerial.println("S1");

xTaskCreate(
                    WiFi_Task,          /* Task function. */
                    "WiFi_Task",        /* String with name of task. */
                    10000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    3,                /* Priority of the task. */
                    &WiFi_Task_handle);            /* Task handle. */
xTaskCreate(
                    MQTT_Task,          /* Task function. */
                    "MQTT_Task",        /* String with name of task. */
                    20000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    &MQTT_Task_handle);            /* Task handle. */
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
vTaskSuspend(MQTT_Task_handle);









//maze.startGame(MODE_NORMAL_TEAMPLAY,1);
}

void loop() {
//MQTT().Reconnect();
//Display().processInterrupt();


char key = keypad.getKey();
 if (key != NO_KEY){
    //Serial.println(key);
 switch (workmode)
 { 
  case 2:
{
  if (maze.isCompleted)
  {
     MySerial.println("S3");
     workmode=0;
  }
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
  break;
  case 1:
  {
    MySerial.println("S1");
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
      //Serial.println(ip.getIP());
      MySerial.println("I"+ip.getIP()+"E");
      if (ip.check()) 
      {
      MySerial.println("S4");
      workmode =2;
      ip.clearIP();
      Display().startAnimation(RANDOM_BLINKING, 0, 120, 0);
      MQTT().MQTTPublish("active");
      delay(10000);
      MQTT().MQTTPublish("active");
      
      maze.startGame(MODE_NORMAL_TEAMPLAY,1);
  }
    }
    
  }
  
  }
  }
  
 }

if (Serial.available()) //Checking available serial data to control maze (temporary feature)
{
  byte b;
  b = Serial.read();
  switch(b)
  {
    case('q'):
    {
      Display().startAnimation(RANDOM_BLINKING, 0, 0, 120);
      workmode = 0;
    }
     break;
     case('m'):
    {
      Display().startAnimation(RANDOM_BLINKING, 0, 0, 120);
      workmode = 1;
      MySerial.println("S1");
    }
     break;
    case('g'):
    {
      Display().startAnimation(GAME, 0, 0, 120);
      maze.startGame(MODE_CHILDISH,5);
      workmode = 2;
    }
     break;
    case('t'):
    {
       maze.startGame(MODE_NORMAL_TEAMPLAY, 3);
       workmode = 2;
    }
     break;
    case('w'):
    {
      maze.step_up();
    }
    break;
    case('a'):
    {
      maze.step_left();
    }
    break;
    case('s'):
    {
      maze.step_down();
    }
    break;
    case('d'):
    {
      maze.step_right();
    }
    break;
    
  }
 
}

}

void WiFi_Task( void * parameter )
{
 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, password);
 while (WiFi.waitForConnectResult() != WL_CONNECTED) 
  {
    Serial.println("Connection Failed! Rebooting...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
  }
   if(WiFi.waitForConnectResult() == WL_CONNECTED)  
   {
    Serial.println("Connected!!!");
    vTaskResume(MQTT_Task_handle);
  }
 for(;;)
  {
  if (WiFi.waitForConnectResult() != WL_CONNECTED) 
  {
    Serial.println("Connection Failed! Rebooting...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
  }
  delay(5000);
  }
}
void MQTT_Task( void * parameter )
{
delay(2000);
MQTT().Setup() ;
MQTT().Reconnect();
MQTT().MQTTPublish("inactive");
 for(;;)
  {
    
    MQTT().Reconnect();
    delay(200);

    if (MQTT().arrived)
    {
      MQTT().arrived = false;
      workmode = MQTT().state;
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
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
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
