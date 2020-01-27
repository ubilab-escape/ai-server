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


// definir puzzle ad/hoc
bool mazesolved = false;
const char* sta = "inactive";

//bool closeDoor = false;


  void wifi();
  void Setup();
  void Callback(char* topic, byte* payload, unsigned int length);
  void Reconnect();
  void Publish(String topic_name, String Method, String State, String Data);
  //void initMDNS();

  
 // bool arrived = false;
 // int  state =0;


#endif
