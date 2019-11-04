# AI-Server &amp; Puzzles

The information contained in this readme document ~~is highly classified and~~ will be modified constantly, so it is advisable to review it constantly to keep abreast of the latest decisions, puzzles and code outputs.

## Getting Started
**Group 8** are the designers and builders of the server room, the temple where the brain of a high-tech artificial intelligence called **"STASIS"** is located and all the equipment necessary to keep it running.

Our responsibilities are: 

* The manufacture of the technical equipment that allows STASIS to remain in operation, through the use of state-of-the-art materials and technologies.

* The design and implementation of complex algorithms to prevent access to STASIS source code and the two wires that allow it to be shut down directly and "casually" open all the doors leading to a safe and direct exit from the high-security complex.

### Team
* Cristina Maurette
* Konstantin Kuliabin
* Claudio Ray 

### Work done and on-going
- [x] Discuss and define server room theme
- [x] Every one ready on slack
- [ ] Puzzles! 
- [ ] Everyone should commit at least once
- [ ] Speak with @ubilab-escape/environment about lighting inside room.
- [ ] Speak with @ubilab-escape/prototype about prototype shape and puzzle integration.

# The Server Room
Highly volatile.

## Look-a-like
### Lighting
### The "Athomsphere" thing

## Puzzles
### Keep talking a-like puzzle
This puzzle contains a set of the small mini puzzles on the control panels, which are hidden in the server room. Instructions to the puzzles are located in the lab room (pictures on the wall, poster, e.t.c.). At least two people should play together. One is operator – person in front of the control panel and instruction guy, who will give hints to the operator according to the provided instructions in the lab room. Team should work together to find solutions. 

### 1. Maze
Control panel contains an RGB LED matrix and 4 buttons. Task is to move green marker to the red position. The problem is – obstacles. Operator of the control panel can’t see the maze itself, but know the position of the markers. Obstacles are drawn in other room. Team should help operator to find a right way.
![alt text](https://i.ibb.co/rp1gkPp/Operator-view.png) 
Figure 1.1 Operator side
![alt text](https://i.ibb.co/8zSGD9x/Team-view.png)
Figure 1.2 Hint poster

If operator made a mistake, puzzle will reset and positions of the markers will change.

### 2. Morse
Control panel contain LED, buzzer and several buttons of different colours. LED and buzzer transfers some sequence which represents a word (colour or other word which corresponds to this colour) in Morse codes. Goal of the operator is to determine a word and press corresponding button on the panel which corresponds to the named colour. If operator makes a mistake, than word changes.
![alt text](https://upload.wikimedia.org/wikipedia/commons/thumb/b/b5/International_Morse_Code.svg/800px-International_Morse_Code.svg.png)
Figure 2.1 Morse codes

### 3. Simon didnt tell that
A bit more complecated version of the Simon says game. The operator should repeat sequence of colours by pressing corresponding buttons. But it is a bit harder than you expect. Colours are shifted.

For example there could be following rules:

Red     -> Yellow
Green   -> Pink
Blue    -> Red
Yellow  -> Blue
Pink    -> White
White   -> Green

So is sequence is Red -> White -> Pink -> Green, operator should press Yellow -> Green -> White -> Pink buttons.

### Send data
### Kill STASIS

 
