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
String sta = "inactive";          // Simon status
bool sta_change = false;
String text = "waiting...";
// Light Publish-variables
String light_option = "";
bool Simon_active = false;
bool Simon_solved = false;

  void wifi();
  void Setup();
  void Callback(char* topic, byte* payload, unsigned int length);
  void Reconnect();
  void Publish(char* Topic, String Method, String State, String Data);



#endif
