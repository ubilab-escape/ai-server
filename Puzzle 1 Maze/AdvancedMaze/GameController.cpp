#include "GameController.h"
#include "MQTT.h"


void GameController::startGame(byte mod, byte lifes)
{
  MQTT().MQTTPublish("Group8/Maze/Compleated", "Game Started");
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
    Display().SetColour(120,120,0);
    MQTT().MQTTPublish("Group8/Maze/Fail", "Failed");
    delay(1000);
    MQTT().MQTTPublish("Group8/Maze/Fail", "Ok");
    Display().startAnimation(GAME, 0, 0, 0);
    Display().maze.resurect();
    
  }
  if (Display().maze.deathFlag)
  {
   Display().SetColour(0,120,0);
   MQTT().MQTTPublish("Group8/Maze/Death", "Dead");
    delay(3000);
   MQTT().MQTTPublish("Group8/Maze/Death", "Reborned");
    Display().startAnimation(GAME, 0, 0, 0);
    Display().maze.CreateMaze();
  }
  
  if (Display().maze.completedFlag)
  {
    MQTT().MQTTPublish("Group8/Maze/Compleated", "Compleated");
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
