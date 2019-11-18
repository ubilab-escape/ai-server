/*
 * This class contains basic settings of the maze
 */


#ifndef Settings_h
#define Settings_h

//LED strip settings
#define LED_TYPE  NEO_RGB// pixel type flags
#define LED_SPEED  NEO_KHZ800// pixel type flags
#define LED_PIN  13 //Arduino pin number (most are valid)
#define LED_COUNT  64 //number of pixels in strip
#define LED_UPDATE_TIME  50 // Uppdate time in ms
#define LED_BRITENESS 30


//Maze and other
#define MAZE_X 8 //length of the maze
#define MAZE_Y 8 // width of the maze


#endif