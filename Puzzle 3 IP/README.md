# Puzzle 3 - IP

This folder contains information about the IP puzzle.

As explained, the player is asked on the LCD screen to insert the IP address hidden on the walls of the escape room and only visible using the UV flashlight (placed inside the server room).

The components, source code and setup are the ones explained in the [Maze](https://github.com/ubilab-escape/ai-server/tree/master/Puzzle%201%20Maze) puzzle.

The IP address is _128.0.32.16_, but it is written on the walls as:
* A128
* B0
* C32
* D16

The letter and numbers must be inserted using the keyboard, as seen on the walls regardless of the order.


### Syntaxis to control the IP puzzle using MQTT

Expected JSON messages on topic `8/puzzle/IP`

* Forces the puzzle state as **active** ≈ reset puzzle and ask for IP.
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



