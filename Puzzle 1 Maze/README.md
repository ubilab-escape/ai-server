# Maze puzzle
This folder will contain source code and other files of the Maze puzzle. 

##Legend
You are private secret agent and you got wery important information which you must send to your customer as soon as possible using available servers. The problem is, that most of the routers in the local network contain firewalls which blocks any data comming through. You are limited in time and attempts, but you must find a path through to the internet.

## Getting Started
Maze puzzle is a advanced version of well known puzzle, when you should find a correct path to the exit, but you dont see the obstacles. When you reach firewall it initiate disconnection from this subnet and you should start again with other subnet, other map and other position.
To find right path, players should find a drawing of the maze. Then they shoud determine the right maze and corrent path according to the start and end point drawn on the screen.

### Required materials
* STM 32 as a brain of the system with Wi-Fi
* RGB address strip used as display
* Buttons for movement

* Poster with instructions


### Work done and on-going
- [x] Create plan of implementation
- [x] Create maps
- [x] Implement maze game class
- [x] Implement MQTT connecction and control
- [x] Implement button control
- [x] Make the poster with map and instructions


## Compilation of the project

1. Install Arduino IDE
https://www.arduino.cc/en/Main/Software
2. Install ESP32 board in Arduino IDE using following ling for the board manager:
> https://dl.espressif.com/dl/package_esp32_index.json
Select ESP32 Dev module.

3. Install library for the FastLED from here:
https://github.com/FastLED/FastLED
4. Install library for the Keypad from here:
https://www.arduinolibraries.info/libraries/keypad
