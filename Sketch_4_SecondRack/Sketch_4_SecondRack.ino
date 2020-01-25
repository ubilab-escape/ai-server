
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "MQTT.h";
#include "Display.h"

HardwareSerial MySerial(1);

TaskHandle_t WiFi_Task_handle;
TaskHandle_t MQTT_Task_handle;


//const char* ssid = "ubilab_wifi";
//const char* password = "ohg4xah3oufohreiPe7e";
const char* ssid = "WirelessMan";
const char* password = "Rahatlukum75";




void setup() {

Serial.begin(115200);


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

 delay(1000);

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
 for(;;)
  {
    delay(2000);
    MQTT().Reconnect();
    
    
  }
}
void OTA_Task( void * parameter )
{
 ArduinoOTA.setHostname("Rack");
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
