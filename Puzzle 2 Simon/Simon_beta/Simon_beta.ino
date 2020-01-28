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
  
   This Code Does:
     - Play Simon didn't say puzzle with 5 different combinations
     - Connects to WiFI
     - Handles Over The Air code updates
     - Handles MQTT comunication            
 
   This code is not:
     - yet perfect

//-----------------------------------------------------------------------------------------------------------------//  
   
    Out_Pin    G:13 / W:12 / Y:2   / B:27  / R:26
    
    Input_Pin  G:18 / W:19 / Y:21  / B:22  / R:23

//-----------------------------------------------------------------------------------------------------------------//  
*/

#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include "MQTT.h"
#include <EEPROM.h>
#include <ESPmDNS.h>

#define DEBUG

// WiFi + OTA 
//const char* ssid = "Guaripolo 2.4GHz";
//const char* password = "Internet1";

const char* ssid = "ubilab_wifi";
const char* password = "ohg4xah3oufohreiPe7e";
 
// Buttons 

int show[]={13,12,2,27,26}; // Initial led wave to draw user attention (also used in setup() to define output pins)
int input[]={18,19,21,22,23}; // Used in setup() to define input pins

// Sequences      G:13 / W:12 / Y:2   / B:27  / R:26
int simon[7][5]={{27,2,2,13,13},    // B, Y, Y, G, G
                 {12,26,13,2,12},   // W, R, G, Y, W
                 {13,26,27,12,12},  // G, R, B, W, W
                 {27,2,26,13,13},   // B, Y, R, G, G
                 {12,27,2,2,27},    // W, B, Y, Y, B
                 {12,2,27,12,13},   // W, Y, B, W, G
                 {27,13,2,2,26}};   // B, G, Y, Y, R

// Solutions    G:18 / W:19 / Y:21  / B:22  / R:23
int sol[7][5]={{18,23,23,21,21},    // G, R, R, Y, Y 
               {19,23,18,21,19},    // W, R, G, Y, W
               {23,23,18,19,19},    // R, R, G, W, W
               {18,18,23,21,18},    // G, G, R, Y, G 
               {22,21,19,22,21},    // B, Y, W, B, Y
               {19,21,22,19,23},    // W, Y, B, W, R
               {18,21,23,23,21}};   // G, Y, R, R, Y


int input_sequence[5];
int pinCount = 5; // Should be constant since is the button counter, but maybe in tests we use less buttons.
int code;
int randnum; // Random selection of puzzle (row of matrix)
int error;
        
// Buzzer 
const int brb = 5; // BRB because it is a big red button
const int freq = 2000;
const int channel = 0;
const int resolution = 8;
int channel1 = 1;
const int buzz = 4;

unsigned long previousMillis = 0;

// Light control
String red = "255,0,0";
String dimmed = "100,0,0";
String off = "0,0,0";


// --------------------------------- SETUP ---------------------------------
void setup() 
{
  
  #ifdef DEBUG
  Serial.begin(115200);
  #endif
  //mdnsUpdate = millis();
  
  
  

  for (int i = 0; i < pinCount; i++) 
  {
    pinMode(show[i], OUTPUT);
    pinMode(input[i], INPUT_PULLUP);
  }
  pinMode(14,INPUT_PULLUP);
  ledcSetup(channel, freq, resolution);  
  ledcAttachPin(brb, channel);
  ledcAttachPin(buzz, channel1);

  xTaskCreate(
                    Wifi_Task,          /* Task function. */
                    "Wifi_Task",        /* String with name of task. */
                    10000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    3,                /* Priority of the task. */
                    NULL);            /* Task handle. */
  


  xTaskCreate(
                    OTA_Task,          /* Task function. */
                    "OTA_Task",        /* String with name of task. */
                    10000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */
  


  xTaskCreate(
                    Reconnect_Task,          /* Task function. */
                    "Reconnect_Task",        /* String with name of task. */
                    10000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */
  

  xTaskCreate(
                    Publish_Task,          /* Task function. */
                    "Publish_Task",        /* String with name of task. */
                    10000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */
  
}


// --------------------------------- Wifi Setup ---------------------------------
void Wifi_Task( void * parameter )
{
 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, password);
 while (WiFi.waitForConnectResult() != WL_CONNECTED) 
  {
    Serial.println("Connection Failed! Rebooting...");
    ESP.restart();
  }
   if(WiFi.waitForConnectResult() == WL_CONNECTED)  
   {
    Serial.println("Connected");
    Setup(); 
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


// --------------------------------- OTA Setup ---------------------------------
void OTA_Task( void * parameter )
{
  ArduinoOTA.setHostname("Simon");
  ArduinoOTA.setPassword("1");
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";
  
      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
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


// --------------------------------- Reconnect and Publish ---------------------------------
void Reconnect_Task( void * parameter )
{
  delay(5000);
  for(;;)
  {
    Reconnect(); 
    delay(300);
  }
}

void Publish_Task( void * parameter )
{
  delay(5000);
  for(;;)
  {   
    if(sta == "inactive" || sta == "solved"){
      Publish("8/puzzle/simon", "STATUS", sta, text);
      Publish("8/puzzle/kill-button", "STATUS", brb_sta, brb_text);
      delay(5000);
    }
    if(sta == "active"){
      Publish("8/puzzle/simon", "STATUS", sta, text);
      Publish("8/puzzle/kill-button", "STATUS", brb_sta, brb_text);
      delay(800);
    }
    
    delay(10000);
  }
}


// --------------------------------- LOOP ---------------------------------
void loop() 
{ 
  if (Mazesolved == true && Simonsolved == false)
  {
    Publish("8/puzzle/simon", "STATUS", sta, text);
    puzzle_simon();
  }
 /* 
  if (f_sta == true) {
    sta == "active";
    Publish("8/puzzle/simon", "STATUS", sta, text);
    puzzle_simon(); 
    f_sta = false;   
 }*/
  
} // end of loop()




// --------------------------------- SIMON ---------------------------------
void puzzle_simon() 
{ 
    //code = choosecode();
    Publish("5/safe/control", "TRIGGER", "on", "3:0"); 
    code = 0;
    Serial.print("Simon didn't say puzzle nº ");
    Serial.println(code);
    error = 0;
    preamble();  
    Publish("2/ledstrip/serverroom", "TRIGGER", "rgb", dimmed);   // dimmed the room lights
               
    while(error < 3 && Simonsolved == false)
    {
      sequence_show(error);         // Here is where simon[][] is showed to the user.
      Serial.print("User input: ");
      sequence_read();              // Here is where input_sequence[] is compared with sol[][]
      Serial.println(" ");
    }

} // end of loop()


// --------------------------------- Choose random input ---------------------------------
int choosecode()
{
    randnum = random(0,6); 
    return randnum;
} // end of choosecode()


// --------------------------------- Preamble Sequence ---------------------------------
void preamble() 
{
  Serial.println("Showing preamble");
  for (int k = 0; k < 5; k++) 
  {
    
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(27, HIGH);
      digitalWrite(26, HIGH);
      delay(400);
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(2, LOW);
      digitalWrite(27, LOW);
      digitalWrite(26, LOW);
      delay(400);      
      //tone(buzz,800,10); //Commented bcz is super annoying
  }
  delay(1500);
} // end of preamble()


// --------------------------------- Read Sequence ---------------------------------
void sequence_read()
{
  text = "Waititng input..";
  Publish("8/puzzle/simon", "STATUS", sta, text);
  int flag = 0; // This is the state toggle. Analize inputs, when detected flag == 1. 
              // The logic is while inputs are correct, while function remains. if the whole sequence is correct (correctly compared), for function ends and final sequence -puzzle_correct()- starts 

  for (int i = 0; i < pinCount; i++)
  {
    flag = 0;
    while(flag == 0)
    {
        if (digitalRead(18) == LOW) 
        {
            Serial.print("18 ");
            digitalWrite(13, HIGH); // When the button is pressed, the led turns on... because why not
            input_sequence[i] = 18;
            flag = 1; // exit while
            delay(200);
            
            if (input_sequence[i] != sol[code][i]) //input comparisson with solution
            {
              digitalWrite(13, LOW);
              w_input();
              return;
            }
            
            c_input();
            digitalWrite(13, LOW);
        }
  
        if (digitalRead(19) == LOW)
        {
            Serial.print("19 ");
            digitalWrite(12, HIGH);
            input_sequence[i] = 19;
            flag = 1;
            delay(200);
            if (input_sequence[i] != sol[code][i])
            {
              digitalWrite(12, LOW);
              w_input();
              return;
            }
            c_input();
            digitalWrite(12, LOW);
        }
  
        if (digitalRead(21) == LOW)
        {
            Serial.print("21 ");
            digitalWrite(2, HIGH);
            input_sequence[i] = 21;
            flag = 1;
            delay(200);
            if (input_sequence[i] != sol[code][i])
            {
              digitalWrite(2, LOW);
              w_input();
              return;
            }
            c_input();
            digitalWrite(2, LOW);
        }
  
        if (digitalRead(22) == LOW)
        {
            Serial.print("22 ");
            digitalWrite(27, HIGH);
            input_sequence[i] = 22;
            flag = 1;
            delay(200);
            if (input_sequence[i] != sol[code][i])
            {
            digitalWrite(27, LOW);
            w_input();
            return;
            }
            c_input();
            digitalWrite(27, LOW);
        }
  
        if (digitalRead(23) == LOW)
        {
            Serial.print("23 ");
            digitalWrite(26, HIGH);
            input_sequence[i] = 23;
            flag = 1;
            delay(200);
            if (input_sequence[i] != sol[code][i])
            {
              digitalWrite(26, LOW);
              w_input();
              return;
            }
            c_input();
            digitalWrite(26, LOW);
        }
    } 
  }

  Simonsolved = true;
  sta = "solved";
  text = "puzzle solved";
  Publish("8/puzzle/simon", "STATUS", sta, text);
  
  brb_sta = "active";
  Publish("8/puzzle/kill-button", "STATUS", brb_sta, brb_text);
  puzzle_correct();     // This is the puzzle ending sequence. 
  
} // end of sequence_read()


// --------------------------------- Show Sequence ---------------------------------
void sequence_show(int x)
{
  text = "showing pattern";
  Publish("8/puzzle/simon", "STATUS", sta, text);
  Serial.print("Sequence: ");
  for (int s = 0; s < pinCount; s++) 
    {
      Serial.print(simon[code][s]);
      Serial.print(" ");
      digitalWrite(simon[code][s], HIGH);
      ledcWriteTone(channel1, 600);
      delay(400);
      ledcWriteTone(channel1, 0);
      delay(600-x*10);
      ledcWriteTone(channel1, 0);
      digitalWrite(simon[code][s], LOW);
      delay(300);
      //tone(buzz,800,10); //Commented bcz is super annoying
    }
    Serial.println(" ");
} // end of sequence_show()


// --------------------------------- Wrong input ---------------------------------
void w_input()
{
  Serial.println(" ");
  Serial.println("Input error, puzzle incorrect");
  text = "wrong button";
  Publish("8/puzzle/simon", "STATUS", sta, text);
  
  error++;
     Publish("2/ledstrip/serverroom", "TRIGGER", "rgb", red);   // turn red the room lights
     ledcWriteTone(channel1, 200);
     delay(200);
     ledcWriteTone(channel1, 100);
     delay(500);
     ledcWriteTone(channel1, 0);
     delay(2000);
     Publish("2/ledstrip/serverroom", "TRIGGER", "rgb", dimmed);   // dimmed the room lights
}


// --------------------------------- BRB ---------------------------------
void puzzle_correct()
{

  Publish("2/ledstrip/serverroom", "TRIGGER", "rgb", off);   // turn off the room lights
  Serial.println(" ");
  Serial.println("Puzzle correctly solved");
  while(digitalRead(14) != LOW)
  {
    for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
    {     
      ledcWrite(channel, dutyCycle);
      delay(4);
      if (digitalRead(14) == LOW) 
        {
          dutyCycle = 0;
          ledcWrite(channel, dutyCycle);
          break;
        }
    }
      
    for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
    {
      // changing the LED brightness with PWM
      ledcWrite(channel, dutyCycle);   
      delay(4);
      if (digitalRead(14) == LOW) //input comparisson with solution
      {
        dutyCycle = 0;
        ledcWrite(channel, dutyCycle);
        break;
      }
    }
  }
    brb_sta = "solved";
    brb_text = "BRB pressed";
    Publish("8/puzzle/kill-button", "STATUS", brb_sta, brb_text);
    Publish("5/safe/control", "TRIGGER", "on", "0:0");   // turn on the safe lights

    delay(2000);
    
} // end of puzzle_correct()


// --------------------------------- Correct input ---------------------------------
void c_input()
{
     text = "correct button";
     Publish("8/puzzle/simon", "STATUS", sta, text);
     ledcWriteTone(channel1, 600);
     delay(200);
     ledcWriteTone(channel1, 1000);
     delay(400);
     ledcWriteTone(channel1, 0);
     delay(10);
}
