/* This is Tile class. Tile class is a lowest level class of the maze. It contain parameters of the tiles.
 *  
 */
#ifndef Tile_h
#define Tile_h

#include "Arduino.h"
 //definition of tile device
#define SERVER 0
#define FIREWALL 1

 //definition of tile player entity
#define PLAYER_NOT false
#define PLAYER_YES true

 //definition of tile target entity
#define TARGET_NOT false
#define TARGET_YES true

 //definition of initial player position
#define INITIAL_POS_NOT false
#define INITIAL_POS true

//definition of initial player position
#define PATH_NOT false
#define PATH_YES true
 
 class Tile
{
  public:
    Tile(); // Init of the tile
    byte type; // Type of the tile (free or not)
    bool player; // Is player there?
    bool target; // Is target there?
    bool initPlayer; // Is this init position?
    bool path; // Is it important path tile?
};

#endif
