# Puzzle 1 - Maze

This folder contains the source [code](https://github.com/ubilab-escape/ai-server/tree/master/Puzzle%201%20Maze/AdvancedMaze) and other files of the Maze puzzle. 

## Legend

You are private secret agent and you got very important information which you must send to your customer as soon as possible using available servers. The problem is, that most of the routers in the local network contain firewalls which blocks any data comming through. You are limited in time and attempts, but you must find a path through to the internet.

## Getting Started

Maze puzzle is a advanced version of well known puzzle with a twist: finding a correct path to the exit without seeing the obstacles. If the player reaches the firewall it initiates disconnection from this subnet and the player should start again with other subnet and other position.

To find right path, the players should find a [poster](https://github.com/ubilab-escape/ai-server/tree/master/Puzzle%201%20Maze/Poster) of the maze. Then, they shoud determine the corrent path according to the start and end point drawn on the screen.

* Example:

In the figure, on the left is what the player sees and on the right is the solution meant for the instructor. Once the player indicates the position of both points, the instructor is able to identify the solution and transmit it.

<p align="center">
  <img src="https://i.ibb.co/qjjNtwR/maze.png" width="70%" />
</p>
<p align="center">
Figure: Left, what the player faces. Right, solution map for instructor.
</p> 

**Note:** If the player presses a button leading to the firewall, the puzzle is restarted with the markers in different positions.<br/>
<br/>

The solution for the maze showed in the figure above would be:
```
↑ → ↑ ← ↑ ↑ ↑ ↑ ↑ ← ← ← ↓ ← ← ↑
```
### Required materials

* ESP 32 as a brain of the system with Wi-Fi
* Arduino board for interface with the LCD display
* RGB address strip used as display
* Numpad with 3D printed [holder](https://github.com/ubilab-escape/ai-server/blob/master/Puzzle%201%20Maze/3D%20Prints/Keypad_holder.stl)
* LCD Display with 3D printed [holder](https://github.com/ubilab-escape/ai-server/blob/master/Puzzle%201%20Maze/3D%20Prints/LCD_holder.stl)

* [Poster](https://github.com/ubilab-escape/ai-server/tree/master/Puzzle%201%20Maze/Poster) with instructions


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

3. Install library for the FastLED from here:
https://github.com/FastLED/FastLED

4. Install library for the Keypad from here:
https://www.arduinolibraries.info/libraries/keypad

5. Install library for the Arduino JSON from here:
https://github.com/bblanchon/ArduinoJson

6. Install library for the MQTT from here:
https://github.com/knolleary/pubsubclient

7. Select ESP32 Dev Module from board manager and press compile


All relevant vesrions of libraries are provided [here](https://github.com/ubilab-escape/ai-server/tree/master/Libraries)


## Plagiarism

All code is written based on original documentation such as:
1. [arduino](https://www.arduino.cc/en/main/docs)
2. [ESP32](https://docs.espressif.com/projects/esp-idf/en/latest/)
3. [freeRTOS](https://www.freertos.org/Documentation/RTOS_book.html)
 
and examples of libraries:

1. [FastLED](https://github.com/FastLED/FastLED)
2. [Keypad](https://www.arduinolibraries.info/libraries/keypad)
3. [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
4. [PubSubClient](https://github.com/knolleary/pubsubclient)

so it may contain some unreferenced parts/blocks of provided in documentations/examples code.

### Syntaxis to control the puzzle using MQTT

Expected JSON messages on topic `8/puzzle/maze`

* Forces the puzzle state as **active** ≈ reset puzzle and starts the game.
```json
{"method": "trigger", "state": "on", "data": "" }
```
* Forces puzzle state as **solved** ≈ skipped puzzle. 
```json
{"method": "trigger", "state": "off", "data": "skip" }
```
* Forces puzzle state as **inactive** ≈ reset puzzle.
```json
{"method": "trigger", "state": "off", "data": "" }
```

Note: data IS case sensitive.