#include "Display.h";



void setup() {
 
Display(); // initialization of the display class
Display().startAnimation(GAME, 0, 0, 120); // Start animation with selected type
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
      Display().maze.InitMaze(MODE_CHILDISH);
    }
     break;
    case('t'):
    {
      Display().maze.InitMaze(MODE_NORMAL_TEAMPLAY);
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
}
}
