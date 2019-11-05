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
- [x] Everyone should commit at least once
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


#### 1. Maze
The control panel contains an RGB LED matrix and 4 buttons which mimics a board. The task is to move the green marker to the red position.  The problem is obstacles (walls) given the appearance of a labyrinth. 

The difficulty is that the operator cannot see the labyrinth, only the position of the markers, so to complete the puzzle, the operator depends completely on the instructions given by the instructor to press the correct buttons in the correct sequence, thus taking the green marker to red.

<p align="center">
  <img src="https://i.ibb.co/L06nvSF/maze.png" width="400" />
 
</p>
<p align="center">
Figure: Left, what the operator faces. Right, Hint image for instructor.
</p> 
If the operator presses a button in the wrong sequence, the puzzle is restarted with the markers in different positions.<br/>
<br/>


#### 2. Morse
The operator is presented with a control panel containing an LED, a buzzer and several buttons of different colors. The LED and the buzzer generate a sequence that represents a word that represents a color (color or other word that corresponds to this color) in Morse code. The objective of this game is that the entire team is able to identify the color given the code using the Morse dictionary. If the operator makes a mistake, the color changes.

<p align="center">
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/b/b5/International_Morse_Code.svg/800px-International_Morse_Code.svg.png" width="400">
</p> 
<p align="center">
Figure: Morse code chart.
</p> 


#### 3. Simon didn't tell that
A slightly more complex version of the traditional "Simon Says" game. Here, the operator must repeat a given sequence of colors by pressing the corresponding buttons, only that this sequence of colors is "coded", this means that the color red does not necessarily mean repeating red, but another color. 

As an example:  

The operator faces the following sequence of colors: 
```
Red → White → Pink → Green    
```
And the instructor has the following relation:  
```
Red     → Yellow 
Green   → Pink 
Blue    → Red 
Yellow  → Blue 
Pink    → White 
White   → Green 
```
The instructor should tell the operator to press the following sequence:  
```
Yellow → Green → White → Pink
```
### Send data
a

### Kill STASIS

 