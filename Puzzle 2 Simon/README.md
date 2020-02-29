# Puzzle 2 - Simon didn't say. 

### In a nutshell

The main plan is to design a code in such a way that a sequence of five colors is shown, this showed sequence must be then modified by the group by a previously defined set of conditions (check **[Instructions_Simon](https://github.com/ubilab-escape/ai-server/blob/master/Puzzle%202%20Simon/Poster/Instructions_Simon.pdf)**) and inserted by pressing the correct buttons. The group has three chances, in case they fail -conditions applied incorrectly or wrong button pressed- the color sequence changes.  

### Hardware

The components used are listed below. These are used as they were acquired, so no modification are necessary for their implementation.

- 1x ESP32
- 5x 60mm push type buttons (color assorted)
- 1x 100mm push type button (red)
- 1x Buzzer
- 1x Generic 5V 1A power supply with micro usb cable 
- 1x Perfboard
- 30x Male headers
- 15x Female crimp pins  


#### Connection schematic

To facilitate and strengthen the connection to the ESP32, a small board was manufactured in perfboard.Also, for the input of the ESP32 (coming from the buttons), the internal pull down resistor of the ESP32 was activated on each corresponding pin.

The buttons have an internal resistance in the LED, so they are not considered in the schematic.

<p align="center">
  <img src="https://i.ibb.co/7ym6HCj/circuit.png" width="85%" /> 
</p>

### Software

The **[code](https://github.com/ubilab-escape/ai-server/blob/master/Puzzle%202%20Simon/Simon/Simon.ino)** is done in arduino format and its flow diagram is shown below.

<p align="center">
  <img src="https://i.ibb.co/vq7xXsW/Flow-d.png" width="85%" /> 
</p>

#### Color Sequences

Predetermined color sequences (randomly choosed) are shown in the table. A limited number of sequences is used (instead of a random generator) to simplify the puzzle runs.

| Nº | OUTPUT      | INPUT         |
|:----:|:---------------:|:---------------:|
| 0  | B, Y, Y, G, G | G, R, R, Y, Y |
| 1  | W, R, G, Y, W | W, R, G, Y, W |
| 2  | G, R, B, W, W | R, R, G, W, W |
| 3  | B, Y, R, G, G | G, G, R, Y, G |
| 4  | W, B, Y, Y, B | B, Y, W, B, Y |
| 5  | W, Y, B, W, G | W, Y, B, W, R |
| 6  | B, G, Y, Y, R | G, Y, R, R, Y |

_B ≡ Blue ; Y ≡ Yellow ; R ≡ Red ; G ≡ Green ; W ≡ White_

### Syntaxis to control the Simon didn't say puzzle using MQTT

Expected JSON messages on topic `8/puzzle/simon`

* Forces the puzzle state as **active** ≈ reset puzzle and start of sequence.
```json
{"method": "trigger", "state": "on", "data": "" }
```
* Forces puzzle state as **solved** ≈ skipped puzzle. 
```json
{"method": "trigger", "state": "off", "data": "skipped" }
```
* Forces puzzle state as **inactive** ≈ reset puzzle.
```json
{"method": "trigger", "state": "off", "data": "" }
```

Note: data IS case sensitive.




