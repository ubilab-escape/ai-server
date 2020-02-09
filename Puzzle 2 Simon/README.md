# Puzzle 2 - Simon didn't say. 

### In a nutshell

The main plan is to design a code in such a way that a sequence of five colors is shown, this showed sequence must be then modified by the group by defined set of conditions (check Instructions_Simon.pdf) and inserted by pressing the correct buttons. If a mistake is made (wrong button), the team has two more posibilities, otherwise, the sequence is changed. 

The group has three chances, in case they fail -conditions applied incorrectly or wrong button pressed- the color sequence changes. 

### Hardware

The components used are listed below. These are used as they were acquired, so no modification is necessary for their implementation.

#### Hardware
- 1x ESP32
- 5x 60mm push type buttons (color assorted)
- 1x 100mm push type button (red)
- 1x Buzzer
- 1x Generic 5V 1A power supply with micro usb cable 
- 1x Perfboard
- 30x Male headers
- 15x Female crimp pins  


#### Connection schematic

To facilitate and strengthen the connection of the ESP32 and the different cables, a small plate was manufactured in perfboard.

For the input from the buttons, the internal pull down resistor of the ESP32 was activated on each corresponding pin.

The buttons have an internal resistance in the LED, so they are not considered in the schematic.

<p align="center">
  <img src="https://i.ibb.co/7ym6HCj/circuit.png" width="85%" /> 
</p>

### Software



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




