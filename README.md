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
Information here is highly volatile.

## Dynamic
We analyze the Escape Room (ER) as a sequence of stages, being in our responsability, the last one. Thus, given the following flow chart, we infere this sequence:
<p align="center">
  <img src="https://i.ibb.co/JHLJ5KH/Flow-Diagram.png" width="85%" /> 
</p>

### Stage 0
This stage is like the preamble or the conditions that are needed to start the next stage. 

* Since mission briefieng was self destroyed, players must have memorized the encrypted "IP" (Since that sequence has a sort of encryption, we have to provide it to **Team ¿?**).
* Participants satisfactorily resolve the previous stage.

### Stage 1 (Send Data)
Once players can access the prototype data, the next stage is to send that to the client. In order to do that, first they must successfully resolve two puzzles:

* Decode encrypted IP
* Solve first puzzle "Maze"

In this case, the order of solving the puzzles is not that important since at the end (both puzzles resolved) players must introduce the decrypted IP into a fake terminal, and with fake we mean a screen with a keyboard which only compare the input with a given reference.

Once the input matches the reference, a mock "Sending..." progress bar will appear, which means that the data is being sent properly until...

Stastis goes rouge.

### Stage 1.5
This is not a proper stage, but a sequence of event which we think is good for story developing.

Since STASIS detects a data/security breach, it inferes (is an artificial inteligence right..) that there are people in the server room who are performing prohibited actions, so their very existence is in danger. Thus it activates a complete lock-out expecting that a terminator arrives soon enough.  

```
Note: With enviroment team -if they agree- we can design a sort of agressive enviroment with light and sound. The idea is to increase stress level of players.     
```

### Stage 2 (Kill Stasis)
In this final stage, players must locate STASIS core and solve the puzzle in order to shut it down (eliminate). 

At the same time, we think that STASIS should not have a silent death, so it creates a lot of noise and variates the illumination (that decision is not ours) like a kid outburs.  

The final puzzle (yet to be defined) once it is solved, a LED button turns ON, and once pressed, the escape room is resolved, the doors open and the lights return to normal.

## Puzzles

The main idea behind these puzzles is composed of a set of small puzzles, which are distributed in the control panel or hidden in the server room. The small puzzles have a defined sequence, each time a mini puzzle is solved, the next one is activated. To finish the room, all puzzles must be solved.

The dynamic of the puzzles is based on a constant communication similar to a "Keep talking an nobody dies". The participants can adopt two roles:

* Operator: Is the one who physically faces the puzzle. His role is to describe the characteristics of the puzzle and according to the commands of the instructor, solve it. 
* Instructor: Can be one or more people. Given the description given by the operator, his responsibility is to interpret the information received, decrypt the solution of the puzzle and tell the operator how to solve it.

The instructions for the puzzles can be located outside the server room (photos on the wall, posters, etc.). 

Given the above, at least two people must solve the room tasks together in constant communication and also constant under pressure, which can lead to errors in their execution. 


#### 1. Maze
The control panel contains an RGB LED matrix and 4 buttons which mimics a board. The task is to move the green marker to the red position. The problem are the obstacles (walls) which give the appearance of a labyrinth. 

The difficulty is that the operator cannot see the labyrinth, only the position of the markers; so, to complete the puzzle, the operator depends completely on the instructor's indications in order to press the buttons in the correct sequence, thus leading the green marker to the red one.

<p align="center">
  <img src="https://i.ibb.co/L06nvSF/maze.png" width="400" />
 
</p>
<p align="center">
Figure: Left, what the operator faces. Right, Hint image for instructor.
</p> 
If the operator presses a button leading to a wrong sequence, the puzzle is restarted with the markers in different positions.<br/>
<br/>

#### 2. Morse
The operator is presented with a control panel containing an LED, a buzzer and several buttons of different colors. The LED and the buzzer generate a sequence that represents a word which also represents a color (or other word that corresponds to this color) in Morse code. The aim of this puzzle is that the entire team is able to identify the color given the code using the Morse dictionary. If the operator makes a mistake, the color changes.

<p align="center">
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/b/b5/International_Morse_Code.svg/800px-International_Morse_Code.svg.png" width="400">
</p> 
<p align="center">
Figure: Morse code chart.
</p> 


#### 3. Simon didn't say that
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


 