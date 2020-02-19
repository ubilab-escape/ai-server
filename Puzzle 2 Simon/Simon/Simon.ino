/*
//----------------------------------------------------------------------------------------------------------------//                            
                                        Group 8                              
                  _____                            _____                 
                 / ____|                          / ____|                
                | (___  _ _ __ ___   ___  _ __   | (___   __ _ _   _ ___ 
                 \___ \| | '_ ` _ \ / _ \| '_ \   \___ \ / _` | | | / __|
                 ____) | | | | | | | (_) | | | |  ____) | (_| | |_| \__ \
                |_____/|_|_| |_| |_|\___/|_| |_| |_____/ \__,_|\__, |___/
                                                                __/ |    
                                                               |___/     

//----------------------------------------------------------------------------------------------------------------//   
  
   This Code Does:
     - Handles Simon didn't say puzzle with 5 different combinations
     - Connects to WiFI
     - Handles Over The Air code updates
     - Handles MQTT comunication
     - Correctly reacts to MQTT triggers.            
 
   This code is not:
     - yet perfect

   Last correct implementation: 07/02/2020
   Last untested modification:  19/02/2020  

   Further improvements:
     - Visual reaction to correct input (Green lights)
     - Clear some memory 
     - Check how ESP handle interrupts and implement accordingly to inputs
     - ESP ping delay avg 150ms (Home test)
     - Optimize stack size of tasks
      
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

#define DEBUG // Release serial.print memory usage. 

const char* ssid = "ubilab_wifi";
const char* password = "ohg4xah3oufohreiPe7e";
 
// Buttons 

int show[]={13,12,2,27,26};   // Initial led wave to draw user attention (also used in setup() to define output pins)
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
int pinCount = 5; // Should be constant since is the button counter. (Duriing tests we use less buttons)
int code;
int randnum; // Variable to randomly select the sequence (row of matrix)
int error;   // Error counter
        
// Buzzer and Big red button PWM settings
const int brb = 5; // BRB pin
const int buzz = 4; // Buzzer pin
const int freq = 2000;
const int channel = 0;
const int resolution = 8;
int channel1 = 1;


unsigned long previousMillis = 0;

// Light controls
String red = "255,0,0";
String dimmed = "100,100,100";
String off = "0,0,0";
String blue = "0,0,120";
String green = "0,255,0";



// --------------------------------- SETUP ---------------------------------
void setup() 
{
  
  #ifdef DEBUG
  Serial.begin(115200);
  #endif
 

  for (int i = 0; i < pinCount; i++) //Output (leds) and input (buttons) pin mode setup
  {
    pinMode(show[i], OUTPUT);
    pinMode(input[i], INPUT_PULLUP);
  }
  pinMode(14,INPUT_PULLUP); // BRB inut
  ledcSetup(channel, freq, resolution);  
  ledcAttachPin(brb, channel);
  ledcAttachPin(buzz, channel1);


  // Tasks are explained below the definition. 
  // For more setup parameters info, please refrain to https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/freertos-smp.html
  
  xTaskCreate(
                    Wifi_Task,        /* Task function. */
                    "Wifi_Task",      /* String with name of task. */
                    30000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    3,                /* Priority of the task. */
                    NULL);            /* Task handle. */
  


  xTaskCreate(
                    OTA_Task,         /* Task function. */
                    "OTA_Task",       /* String with name of task. */
                    30000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */
  


  xTaskCreate(
                    Reconnect_Task,   /* Task function. */
                    "Reconnect_Task", /* String with name of task. */
                    30000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */
  

  xTaskCreate(
                    Publish_Task,     /* Task function. */
                    "Publish_Task",   /* String with name of task. */
                    30000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */
  
}


// --------------------------------- Wifi Setup ---------------------------------
void Wifi_Task( void * parameter ) 
{
 WiFi.mode(WIFI_STA); //ESP defined as Station mode. 
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
 for(;;) //Every 5 seconds check connection status
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
  while(WiFi.waitForConnectResult() != WL_CONNECTED) //First check wifi status
  {
    delay(1000);
   }
  ArduinoOTA.setHostname("Simon"); 
  ArduinoOTA.setPassword("1"); //Simon password, because security matters.
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";
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

   for(;;) //Every 200ms check if an OTA request is received.
   {
    ArduinoOTA.handle();
    delay(200);
   }
}


// --------------------------------- Reconnect and Publish ---------------------------------
void Reconnect_Task( void * parameter )
{
  delay(5000); //Every 5 seconds check MQTT conection to the server. 
  for(;;)
  {
    Reconnect(); 
    delay(300);
  }
}

void Publish_Task( void * parameter )
{
  delay(5000); //Every 5+3 seconds publish last defined state to mantain server conection. 
  for(;;)
  {   
    Publish("8/puzzle/simon", "status", sta, text);    
    delay(3000);
  }
}


// --------------------------------- LOOP ---------------------------------
void loop() 
{ 
  if (Simon_active == true && Simon_solved == false)  // Active game
  {
    Publish("8/puzzle/simon", "status", sta, text);  
      
    puzzle_simon(); //Function which starts Simon puzzle sequence
       
    Publish("8/rack", "TRIGGER", "rgb", green);  
    Publish("8/puzzle/maze", "trigger", "rgb", green);    
    Simon_active = false;
  }
  
  if (sta_change == true) // Publish state when game is set off or skipped
  {
    Publish("8/puzzle/simon", "status", sta, text);
    sta_change = false;
    Publish("8/rack", "TRIGGER", "rgb", blue); 
  }
  
} // end of loop()


// --------------------------------- SIMON ---------------------------------
void puzzle_simon() 
{ 
    while(Simon_solved == false && sta == "active"){ //Checks if Operator sent an active trigger and that Simon has not been previously solved.
      code = choosecode(); //For "random" sequence selection
      
      Serial.print("Simon didn't say puzzle nº ");
      Serial.println(code);
      
      error = 0; 
      preamble();  
                       
      while(error < 3 && Simon_solved == false && sta == "active") //While error is < 3 the same sequence remains, when bigger, sequence changes
      {
        sequence_show(error);         // Here is where simon[][] is showed to the user.
        Serial.print("User input: ");
        sequence_read();              // Here is where input_sequence[] is compared with sol[][]
        Serial.println(" ");
        Serial.println(Simon_solved);
    }
    }

} // end of puzzle_simon() 


// --------------------------------- Choose random input ---------------------------------
int choosecode()
{
    randnum = random(0,6); //Number defined sequences. 
    return randnum;
} // end of choosecode()


// --------------------------------- Preamble Sequence ---------------------------------
void preamble() 
{
  Serial.println("Showing preamble"); //Just to draw players attention and give some time to realize what is happening/comming. 
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
  }
  delay(1500);
} // end of preamble()


// --------------------------------- Read Sequence ---------------------------------
void sequence_read()
{
  
  text = "waititng input..";
  Publish("8/puzzle/simon", "status", sta, text);
  
  int flag = 0; // This is the state toggle. Analize inputs, when detected flag == 1. 
                // The logic is while inputs are correct the -while- function remains. If the whole sequence is correct (correctly compared), the -for- function ends and the final sequence -puzzle_correct()- starts 

  for (int i = 0; i < pinCount; i++)
  {
    flag = 0;
    while(flag == 0 && sta == "active") //The 5 buttons are constantly checked. Incorrect input triggers w_input();, correct input triggers c_input();
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

  if (sta == "active"){ //When all inputs are correctly compared, Puzzle status changed and ending sequence called.
    text = "puzzle decoded";
    Publish("8/puzzle/simon", "status", sta, text);
    Simon_solved = true;
    
    puzzle_correct();     // This is the puzzle ending sequence. 
  }
} // end of sequence_read()


// --------------------------------- Show Sequence ---------------------------------
void sequence_show(int x) 
{
  if(sta == "active"){
      text = "showing pattern";
      Publish("8/puzzle/simon", "status", sta, text);
      
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
        }
        Serial.println(" ");
  }
} // end of sequence_show()


// --------------------------------- Wrong input ---------------------------------
void w_input() //When players press the wrong button
{
  Serial.println(" ");
  Serial.println("Input error, puzzle incorrect");
  
  text = "wrong button";
  Publish("8/puzzle/simon", "status", sta, text); //Server data update.
  
  error++; //Remember the counter, if larger than 3, Sequence will change

  //This is the auditive reaction to the user input, only three different text-2-speech options.
  if(error == 1) Publish("2/textToSpeech", "message", "", "come on, it is not that difficult");
  if(error == 2) Publish("2/textToSpeech", "message", "", "no no no, that one is not");
  if(error == 3) Publish("2/textToSpeech", "message", "", "Let me change the sequence, maybe it is too easy");

   //This is the visual reaction to the user, lights turn red. 
   Publish("2/ledstrip/serverroom", "trigger", "rgb", red);   // turn red the room lights
   Publish("8/puzzle/maze", "trigger", "rgb", red);   // turn red the server lights
   Publish("8/rack", "TRIGGER", "rgb", red);   
   
   ledcWriteTone(channel1, 200);
   delay(200);
   ledcWriteTone(channel1, 100);
   delay(500);
   ledcWriteTone(channel1, 0);
   
   delay(2500);
  
   //Serverroom lights back to previous state
   Publish("2/ledstrip/serverroom", "trigger", "rgb", dimmed);   // dimmed the room lights
   Publish("8/puzzle/maze", "trigger", "rgb", green);   // turn off the server lights
   Publish("8/rack", "TRIGGER", "rgb", green);   
}


// --------------------------------- BRB ---------------------------------
void puzzle_correct()
{
  
  Serial.println(" ");
  Serial.println("Puzzle correctly solved");
  Publish("8/puzzle/maze", "trigger", "rgb", red);   // turn red the server lights
  Publish("8/rack", "TRIGGER", "rgb", red);  
  
  
  Publish_t2s("2/textToSpeech", "message", "", "simon_says.mp3"); //Enviroment team plays auditive reaction to induce player to press the big red button
  while(digitalRead(14) != LOW && sta == "active") //Big red button glows
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

  Publish("8/puzzle/maze", "trigger", "rgb", green);   // turn green the server lights
  Publish("8/rack", "TRIGGER", "rgb", green);  
  text = "big-red-button pressed";
  sta = "solved";
  Publish("8/puzzle/simon", "status", sta, text); //Server update, Puzzle state solved
      
} // end of puzzle_correct()


// --------------------------------- Correct input ---------------------------------
void c_input() //Just an auditive reaction to a correct input.
{
     text = "correct button";
     Publish("8/puzzle/simon", "status", sta, text);
     
     ledcWriteTone(channel1, 600);
     delay(200);
     ledcWriteTone(channel1, 1000);
     delay(400);
     ledcWriteTone(channel1, 0);
     delay(10);
}
