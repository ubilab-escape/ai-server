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
  void initMDNS();

  
 // bool arrived = false;
 // int  state =0;


#endif
