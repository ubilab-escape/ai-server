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
