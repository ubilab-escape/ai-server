/*This file describes header of the maze class. Class Maze will represent a whole maze with all entities and positions.
 * Class consists of n by n tiles. Each tile can be router without firewall and router with firewall. 
 * Data can go through tiles without firewall and will dissapear in router with firewall
 * 
 */

#ifndef Maze_h
#define Maze_h

#define STATE_OK 0;
#define STATE_FIREWALL 1
#define STATE_TARGET 2

#define MIN_DISTANCE 4

#define MODE_CHILDISH 0
#define MODE_NORMAL_TEAMPLAY 1
#define MODE_NIGHTMARE 2

#include "Arduino.h"
#include "Tile.h"
#include "Colour.h"
#include "Settings.h"
#include "Point.h";

class Maze
{
  public:
    Tile field[MAZE_X][MAZE_Y];
    void getColorArray();
    byte colourArray[LED_COUNT][3];
    void InitMaze(byte mod, byte _lifes);
    void CreateMaze();
    Point findRandomEmptySpot();

    bool deathFlag = false;
    bool failFlag = false;
    bool completedFlag = false;
    byte lifes = 3;

    byte initialMode = MODE_NORMAL_TEAMPLAY;
    byte initialLifes = 3;
    

    Colour c_server = Colour (0,0,0);
    Colour c_firewall = Colour (255,0,0);
    Colour c_player = Colour (0,0,255);
    Colour c_target = Colour (0,255,255);

    const Colour c_red = Colour (255,0,0);
    const Colour c_green = Colour (0,255,0);
    const Colour c_blue = Colour (0,0,255);
    const Colour c_pink = Colour (255,0,255);
    const Colour c_white = Colour (255,255,255);

    Point playerPos = Point(7,7);
    Point initPlayerPos = Point(7,7);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void checkState();

    void resurect();

    byte MAP1[LED_COUNT]
{
0,0,1,1,0,1,0,1,
1,0,1,1,0,1,0,1,
1,0,0,0,0,1,0,0,
0,0,1,0,0,1,1,0,
0,0,0,1,0,1,0,0,
1,1,0,1,0,0,0,1,
1,0,0,1,1,1,0,1,
0,0,1,1,0,0,0,1,
};
    

    private:
    Colour getTileColour(Tile t);
};
#endif
