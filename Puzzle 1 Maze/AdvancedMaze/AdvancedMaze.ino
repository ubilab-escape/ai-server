#include "Display.h";



void setup() {
 
Display(); // initialization of the display class
Display().startAnimation(GAME, 0, 0, 0); // Start animation with selected type
Display().maze.InitMaze(MODE_NORMAL_TEAMPLAY, 3);
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
      Display().maze.InitMaze(MODE_CHILDISH, 5);
    }
     break;
    case('t'):
    {
      Display().maze.InitMaze(MODE_NORMAL_TEAMPLAY, 3);
    }
     break;
    case('w'):
    {
      Display().maze.moveUp();
    }
    break;
    case('a'):
    {
      Display().maze.moveLeft();
    }
    break;
    case('s'):
    {
      Display().maze.moveDown();
    }
    break;
    case('d'):
    {
      Display().maze.moveRight();
    }
    break;
    
  }
  Display().maze.checkState();
  
  if (Display().maze.failFlag && !Display().maze.deathFlag)
  {
    Display().startAnimation(PULSE, 120, 120, 0);
    delay(1000);
    Display().startAnimation(GAME, 0, 0, 0);
    Display().maze.resurect();
    
  }
  if (Display().maze.deathFlag)
  {
    Display().startAnimation(RANDOM_BLINKING, 0, 120, 0);
    delay(3000);
    Display().startAnimation(GAME, 0, 0, 0);
    Display().maze.CreateMaze();
  }
  
  if (Display().maze.completedFlag)
  {
    Display().startAnimation(RANDOM_BLINKING, 120,0 , 0);
    delay(5000);
    Display().startAnimation(GAME, 0, 0, 0);
    Display().maze.CreateMaze();
  }
  
  //Display().updateGameField();
}

}
