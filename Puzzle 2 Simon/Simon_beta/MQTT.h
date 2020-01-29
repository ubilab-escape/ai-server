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


#ifndef MQTT_h
#define MQTT_h

//variables
long mdnsUpdate = millis();


// Simon puzzle Publish-variables
String sta = "inactive";
String text = "Waiting...";
// Simon puzzle Publish-variables
String brb_sta = "inactive";
String brb_text = "";
// Light Publish-variables
String light_option = "";
bool Mazesolved = true;
bool Simonsolved = false;
bool f_sta = false;

  void wifi();
  void Setup();
  void Callback(char* topic, byte* payload, unsigned int length);
  void Reconnect();
  void Publish(char* Topic, String Method, String State, String Data);



#endif
