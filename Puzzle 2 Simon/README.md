# Puzzle 2 - Simon didn't say. 

#### In a nutshell

The main plan is to design a code in such a way that a sequence of five colors is shown in a random way, this sequence that given a series of conditions will have to be modified by the players, which will then have to be entered by pressing colored buttons.

The players have three chances, in case they fail -bad color modification- the color sequence changes. 

| Nº | OUTPUT      | INPUT         |
|:----:|:---------------:|:---------------:|
| 0  | B, Y, Y, G, G | G, R, R, Y, Y |
| 1  | W, R, G, Y, W | W, R, G, Y, W |
| 2  | G, R, B, W, W | R, R, G, W, W |
| 3  | B, Y, R, G, G | G, G, R, Y, G |
| 4  | W, B, Y, Y, B | B, Y, W, B, Y |
| 5  | W, Y, B, W, G | W, Y, B, W, R |
| 6  | B, G, Y, Y, R | G, Y, R, R, Y |


#### Syntaxis to control the puzzle

Expected JSON messages on topic `8/puzzle/simon`

* Force the puzzle state as active ≈ initial state, skipping the requirement of ending MAZE first. 
```json
{"method": "TRIGGER", "state": "on", "data": "start" }
```
* Force puzzle to end, skipping the big red button sequence. It is meant for ending the Escape Room quickly. 
```json
{"method": "TRIGGER", "state": "off", "data": "end" }
```
* Force final stage of the puzzle, which is to press the big red button to kill STASIS.
```json
{"method": "TRIGGER", "state": "on", "data": "brb" }
```

Note: data IS case sensitive.

### Used hardware
- 1x ESP32
- 5x 60mm push type buttons (color assorted)
- 1x 100mm push type button (red)
- Buzzer
- 5V Power supply with micro usb cable 
