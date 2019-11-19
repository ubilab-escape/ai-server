#ifndef GameController_h
#define GameController_h

// Animation types



#include "Arduino.h"
#include "Display.h"


 class GameController
{
 
  public:
  void startGame(byte mod, byte lifes);
  void step_up();
  void step_down();
  void step_left();
  void step_right();
  bool isCompleted;
  private: 
  void checkState();
  
  
  
  
};

#endif
