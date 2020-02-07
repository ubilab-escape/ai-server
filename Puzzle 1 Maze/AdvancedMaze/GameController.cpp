#include "GameController.h"
#include "MQTT.h"


void GameController::startGame(byte mod, byte lifes)
{
  MQTT().MQTTPublishMAZE("active");
  //Display(); // initialization of the display class
  Display().startAnimation(GAME, 0, 0, 0); // Start animation with selected type
  Display().maze.InitMaze(mod, lifes);
  isCompleted = false;
}
void GameController::checkState()
{
  Display().maze.checkState();
  
  if (Display().maze.failFlag && !Display().maze.deathFlag)
  {
    MQTT().MQTTSpeech(FailPhrase[random(10)]);
    MQTT().MQTTSpeech(RestartPhrase);
    Display().startAnimation(RANDOM_BLINKING, 120, 120, 0); 
    MQTT().msg ="Fail: "+String(Display().maze.lifes)+" left";
    MQTT().MQTTPublishMAZE("failed");
    //MQTT().MQTTLightControl("power","on");
    //MQTT().MQTTLightControl("rgb", "255,250,0");
    MQTT().MQTTLightControlRack("120,120,0");
    
    delay(3000);
    MQTT().MQTTSpeech(RestartedPhrase);
    MQTT().msg ="Maze: "+ String(Display().maze.lifes)+" left";
    MQTT().MQTTPublishMAZE("active");
    //MQTT().MQTTLightControl("power", "on");
    //MQTT().MQTTLightControl("rgb", "0,0,0");
    MQTT().MQTTLightControlRack("0,0,120");
    Display().startAnimation(GAME, 0, 0, 0);
    Display().maze.resurect();
    
  }
  if (Display().maze.deathFlag)
  {
    MQTT().MQTTSpeech(FailPhrase[random(10)]);
    MQTT().MQTTSpeech(RestartPhrase);
   Display().startAnimation(RANDOM_BLINKING, 120, 0, 0);
   MQTT().msg ="Death: restarting";
   MQTT().MQTTPublishMAZE("failed");
   //MQTT().MQTTLightControl("power","on");
   //MQTT().MQTTLightControl("rgb", "255,0,0");
   MQTT().MQTTLightControlRack("255,0,0");
    delay(5000);
    MQTT().MQTTSpeech(RestartedPhrase);
   MQTT().msg ="Maze: "+ String(Display().maze.lifes)+" left";
   MQTT().MQTTPublishMAZE("active");
   
    //MQTT().MQTTLightControl("rgb","0,0,0");
    MQTT().MQTTLightControlRack("0,0,120");
    Display().startAnimation(GAME, 0, 0, 0);
    Display().maze.CreateMaze();
  }
  
  if (Display().maze.completedFlag)
  {
    MQTT().msg ="Maze solved";
    MQTT().MQTTPublishMAZE("active");
    // MQTT().MQTTLightControl("rgb", "255,0,0");
     MQTT().MQTTLightControlRack("255,0,0");
    Display().startAnimation(RANDOM_BLINKING, 120,0 , 0);
    isCompleted = true;
  }
}
void GameController::step_up()
{
  Display().maze.moveUp();
  checkState();
}
void GameController::step_down()
{
  Display().maze.moveDown();
  checkState();
}
void GameController::step_left()
{
  Display().maze.moveLeft();
  checkState();
}
void GameController::step_right()
{
  Display().maze.moveRight();
  checkState();
}
