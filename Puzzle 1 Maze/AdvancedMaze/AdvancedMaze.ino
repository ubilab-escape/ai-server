#include "GameController.h";

GameController maze;

void setup() {
 

Serial.begin(115200);

}

void loop() {
  
if (Serial.available()) //Checking available serial data to control maze (temporary feature)
{
  byte b;
  b = Serial.read();
  switch(b)
  {
    case('q'):
    {
      Display().startAnimation(RANDOM_BLINKING, 0, 0, 120);
    }
     break;
    case('g'):
    {
      Display().startAnimation(GAME, 0, 0, 120);
      maze.startGame(MODE_CHILDISH,5);
    }
     break;
    case('t'):
    {
       maze.startGame(MODE_NORMAL_TEAMPLAY, 3);
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
