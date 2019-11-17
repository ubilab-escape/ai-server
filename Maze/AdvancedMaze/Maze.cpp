/*This file describes class maze. Class Maze will represent a whole maze with all entities and positions.
 * Class consists of n by n tiles. Each tile can be router without firewall and router with firewall. 
 * Data can go through tiles without firewall and will dissapear in router with firewall
 * 
 */

#include "Arduino.h"
#include "Maze.h"




void Maze::getColorArray() // Generates table of data for the LED stripe from tile matrix
{
  bool dir = true;
  for (int y = 0; y <MAZE_Y;y++)
  {
    if (dir)
    {
      for (int x = 0; x <MAZE_X;x++)
      {
        colourArray[x+y*MAZE_Y][0] = getTileColour(field[x][y]).r;
        colourArray[x+y*MAZE_Y][1] = getTileColour(field[x][y]).g;
        colourArray[x+y*MAZE_Y][2] = getTileColour(field[x][y]).b;
        }
    }
    else
    {
      for (int x = MAZE_X-1; x >-1;x--)
      {
        colourArray[x+y*MAZE_Y][0] = getTileColour(field[x][y]).r;
        colourArray[x+y*MAZE_Y][1] = getTileColour(field[x][y]).g;
        colourArray[x+y*MAZE_Y][2] = getTileColour(field[x][y]).b;
      }
    }
    dir = !dir;
  }
}
Colour Maze::getTileColour(Tile t) // Checks the type of the tile and returnes its colour. Colour can be specified in the header
{
  Colour res = Colour(0,0,0);
  switch (t.type)
  {
    case (SERVER):
    {
      res = c_server;
    }
    break;
    case (FIREWALL):
    {
      res = c_firewall;
    }
    break;
  }
  if (t.target == TARGET_YES) res = c_target;
  if (t.player == PLAYER_YES) res = c_player;
   
  return res;
}
void Maze::InitMaze(byte mod) // Loads map and put player and target on it randomly
{
  for (int y = 0;y<MAZE_Y;y++)
  {
      for (int x = 0;x<MAZE_X;x++)
    {
      field[x][y] = Tile();
      field[x][y].type = MAP1[y*MAZE_Y+x];
      field[x][y].target = TARGET_NOT;
      field[x][y].player = PLAYER_NOT;
    }
  }
  Point p = findRandomEmptySpot();
  field[p.x][p.y].player = PLAYER_YES;
  field[p.x][p.y].initPlayer = INITIAL_POS;
  initPlayerPos.x = p.x; initPlayerPos.y = p.y;
  playerPos.x = p.x; playerPos.y = p.y;
  p = findRandomEmptySpot();
  field[p.x][p.y].target= TARGET_YES;

  switch (mod)
  {
    case (MODE_CHILDISH):
    {
      c_server = Colour (0,0,0);
      c_firewall = Colour (255,0,0);
      c_player = Colour (0,0,255);
      c_target = Colour (0,255,0);
    }
    break;
    case (MODE_NORMAL_TEAMPLAY):
    {
      c_server = Colour (0,0,0);
      c_firewall = Colour (0,0,0);
      c_player = Colour (0,0,255);
      c_target = Colour (0,255,0);
    }
    break;
  }
  
}
Point Maze::findRandomEmptySpot() // Randomizes position of entity. Returnes x and y pos of the empty tile
{
  while (42)
  {
    byte x = random(MAZE_X);
    byte y = random(MAZE_Y);
    if (field[x][y].type == SERVER)
    {
      if(field[x][y].player == PLAYER_NOT && field[x][y].target == TARGET_NOT)
      {
        return Point(x,y);
      }
      
    }
  }
}
void Maze::moveDown() //Moves player down
{
  if (playerPos.y+1<MAZE_Y)
  {
   field[playerPos.x][playerPos.y].player = PLAYER_NOT;
   field[playerPos.x][playerPos.y+1].player = PLAYER_YES;
   playerPos.y++;
  }
  
}
void Maze::moveUp()//Moves player up
{
  if (playerPos.y>0)
  {
   field[playerPos.x][playerPos.y].player = PLAYER_NOT;
   field[playerPos.x][playerPos.y-1].player = PLAYER_YES;
   playerPos.y--;
  }
  
}
void Maze::moveRight()//Moves player right
{
  if (playerPos.x+1<MAZE_X)
  {
   field[playerPos.x][playerPos.y].player = PLAYER_NOT;
   field[playerPos.x+1][playerPos.y].player = PLAYER_YES;
   playerPos.x++;
  }
  
}
void Maze::moveLeft()//Moves player left
{
  if (playerPos.x >0)
  {
   field[playerPos.x][playerPos.y].player = PLAYER_NOT;
   field[playerPos.x-1][playerPos.y].player = PLAYER_YES;
   playerPos.x--;
  }
  
}
void Maze::checkState() // Checks if player located on valid tile, or on the target, or on the firewall tile
{
  if (field[playerPos.x][playerPos.y].type == FIREWALL) 
    {
      field[playerPos.x][playerPos.y].player = PLAYER_NOT;
      field[initPlayerPos.x][initPlayerPos.y].player = PLAYER_YES;
      playerPos.x = initPlayerPos.x;
      playerPos.y = initPlayerPos.y;
    }
    if (field[playerPos.x][playerPos.y].target == TARGET_YES)
    {
      InitMaze(MODE_NORMAL_TEAMPLAY);
    }
}
