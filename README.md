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
The main idea behind these puzzle is composed of a set of small puzzles, which are distributed in the control panel or hidden in the server room. The small puzzles have a defined sequence, each time a mini puzzle is solved, the next one is activated. To finish the room, all puzzles must be solved.

The dynamics of the puzzles is based on a constant communication of the participants where two roles are identified:

* Operator: Is the one who physically faces the puzzle. His role is to describe the characteristics of the puzzle and according to the commands of the instructor, solve it. 
* Instructor: Can be one or more people. Given the description given by the operator, his responsibility is to interpret the information received, decrypt the solution to the puzzle and tell the operator how to solve the puzzle.

The instructions for the puzzles must be located outside the server room (Photos on the wall, poster, etc.). 

Given the above, at least two people must solve the room. together in constant communication. constant under pressure, which can force errors in execution. 


**1. Maze**
The control panel contains an RGB LED matrix and 4 buttons which mimics a board. The task is to move the green marker to the red position.  The problem is obstacles (walls) given the appearance of a labyrinth. 

The difficulty is that the operator cannot see the labyrinth, only the position of the markers, so to complete the puzzle, the operator depends completely on the instructions given by the instructor to press the correct buttons in the correct sequence, thus taking the green marker to red.

<p float="left">
  <img src="https://i.ibb.co/rp1gkPp/Operator-view.png" width="250" />
  <img src="https://i.ibb.co/8zSGD9x/Team-view.png" width="250" /> 
</p>


 
Figure 1.1 Operator side Figure 1.2 Hint poster

If the operator presses a button in the wrong sequence, the puzzle is restarted with the markers in different positions. 

**2. Morse**
Control panel contain LED, buzzer and several buttons of different colours. LED and buzzer transfers some sequence which represents a word (colour or other word which corresponds to this colour) in Morse codes. Goal of the operator is to determine a word and press corresponding button on the panel which corresponds to the named colour. If operator makes a mistake, than word changes.
![alt text](https://upload.wikimedia.org/wikipedia/commons/thumb/b/b5/International_Morse_Code.svg/800px-International_Morse_Code.svg.png)
Figure 2.1 Morse codes

**3. Simon didnt tell that**
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
a

### Kill STASIS

 
