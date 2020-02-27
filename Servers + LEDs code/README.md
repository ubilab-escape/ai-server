# Servers

Both servers and [Simon didn't say](https://github.com/ubilab-escape/ai-server/tree/master/Puzzle%202%20Simon) puzzle table were constructed using 12mm wood cut following the [sketches](https://github.com/ubilab-escape/ai-server/blob/master/Servers%20%2B%20LEDs%20code/OSB-Platte%20Cutlist%20(12mm).pdf) and using 150mm long wood pieces as frames. Finally, they were both painted in dark gray.

The second rack functions as the frame for the puzzle from [Group 6](https://github.com/ubilab-escape/prototype) and randomly displayed LEDs that are used in [Maze](https://github.com/ubilab-escape/ai-server/tree/master/Puzzle%201%20Maze) puzzle, [IP](https://github.com/ubilab-escape/ai-server/tree/master/Puzzle%203%20IP/IP) puzzle and [Simon didn't say](https://github.com/ubilab-escape/ai-server/tree/master/Puzzle%202%20Simon) puzzle to improve the environment-user experience. 

The [code](https://github.com/ubilab-escape/ai-server/tree/master/Servers%20%2B%20LEDs%20code/Sketch_4_SecondRack) for the LEDs is done in arduino format.


### Syntaxis to control the LEDs from second rack using MQTT

Expected JSON messages on topic `8/rack`

* Different color options are possible for a random LED sequence.
```json
{"method": "TRIGGER", "state": "rgb", "data": "255.0.0" }
```
_with "250.0.0" as red, but different rgb combinations are possible_

* Copy Maze puzzle LEDs reaction
```json
{"method": "TRIGGER", "state": "eye", "data": "0.0.120" }
```
* Power on/off.
```json
{"method": "TRIGGER", "state": "power", "data": "on" }
```
_data can also be "off"_

* Set brightness.
```json
{"method": "TRIGGER", "state": "brightness", "data": "50" }
```
_data can also be a number between 0-255_

### Connectivity

| ESP pin | LED matrix pin |
| ---| --- |
| GPIO 23 | IN |
| GND | GND |
| VDD | VDD |

<p align="center">
  <img src="https://i.ibb.co/0yb35h3/2.png" width="70%" />
</p>


## Compilation of the project


1. Install Arduino IDE
https://www.arduino.cc/en/Main/Software

2. Install ESP32 board in Arduino IDE using following ling for the board manager:
> https://dl.espressif.com/dl/package_esp32_index.json

3. Install library for the FastLED from here:
https://github.com/FastLED/FastLED

4. Install library for the Arduino JSON from here:
https://github.com/bblanchon/ArduinoJson

5. Install library for the MQTT from here:
https://github.com/knolleary/pubsubclient

6. Select ESP32 Dev Module from board manager and upload AdvancedMaze.ino sketch to the ESP32

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


