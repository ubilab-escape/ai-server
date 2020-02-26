# AI-Server &amp; Puzzles

The information contained in this readme document ~~is highly classified and~~ will be modified constantly, so it is advisable to review it constantly to keep abreast of the latest decisions, puzzles and code outputs.

## Motivation
**[Group 8](https://github.com/ubilab-escape/ai-server)** are the designers and builders of the server room, the temple where the brain of a high-tech artificial intelligence called **"STASIS"** is located and all the equipment necessary to keep it running.

Our responsibilities are: 

* The manufacture of the technical equipment that allows STASIS to remain in operation, through the use of state-of-the-art materials and technologies.

* The design and implementation of complex algorithms to prevent access to STASIS source code and the two exposed wires that allow it to be shut down directly leading to a safe and direct exit from the high-security complex aka: Escape Room.

### Team
* Cristina Maurette
* Konstantin Kuliabin
* Claudio Ray 

### Work done and on-going
- [x] Every one ready on slack
- [x] Everyone should commit at least once
- [x] Design puzzles 
- [x] Design mock servers
- [x] Bill of materials
- [x] Hardware of puzzle 1
- [x] Hardware of puzzle 2
- [x] Fabrication of both mock servers 
- [x] Speak with Environment group about usar interation lighting effects and text-to-speech.
- [x] Speak with Prototype group to define shape and size of their puzzle.
- [x] Software of puzzle 1
- [x] Software of puzzle 2 






## The Server Room
We analyze the Escape Room as a sequence of stages, being our responsability, the last one. Thus, given the following flow chart, we infere this sequence:
<p align="center">
  <img src="https://i.ibb.co/Xsz3R65/Flow-Diagram.png" width="85%" /> 
</p>

### Stage 0
This stage is like the preamble or the conditions that are needed to start the next stage. 

* Since mission briefing was self destroyed, players must have memorized the encrypted "IP" (Since that sequence has a sort of encryption, we have to provide it to **Group 3**).
* Participants satisfactorily resolve the previous stage.

### Stage 1 (Send Data)
Once players can access the prototype data, the next stage is to send that to the client. To do that, they must first successfully solve two puzzles:

* Decode encrypted IP
* Solve first puzzle "Maze"

In this case, the order of resolution of the puzzles is not so important because at the end, when the players resolve the maze, they must enter the decrypted IP in a fake terminal, and by fake we mean a screen with a keyboard that only compares the input with a given reference.

Once the input matches the reference, a mock "Sending..." progress bar will appear, which means that the data is being sent properly until...

<p align="center">
  <img src="https://media1.tenor.com/images/3f8b9aec89d8fc5395f3ad3d82f0d697/tenor.gif?itemid=14560182" width="35%" /> 
</p>

Statis goes rouge.

### Stage 1.5
This is not a proper stage, but a sequence of event which we think is good for story developing.

Since STASIS detects a data/security breach, it infers (is an artificial intelligence right..) that there are people in the server room who are performing prohibited actions, so their very existence is in danger. Thus it activates a complete lock-out expecting that a terminator will arrive soon enough.  
  


### Stage 2 (Kill Stasis)
In this final stage, players must locate STASIS core and solve the puzzle in order to shut it down (eliminate). 

At the same time, we think that STASIS should not have a silent death, so it creates a lot of noise and variates the illumination (that decision is not ours) like a kid outburst.  

The final puzzle (yet to be defined) once it is solved, a LED button turns ON, and once pressed the escape room is resolved, the doors open (talk to **Group 4**) and the lights return to normal.

## Puzzles

The main idea behind these puzzles is composed of a set of small puzzles, which are distributed in the control panel or hidden in the server room. The small puzzles have a defined sequence, each time a mini puzzle is solved, the next one is activated. To finish the room, all puzzles must be solved.

The dynamic of the puzzles is based on a constant communication similar to a "Keep talking an nobody dies". The participants can adopt two roles:

* Player: Is the one who physically faces the puzzle. His role is to describe the characteristics of the puzzle and according to the commands of the instructor, solve it. 
* Instructor: Can be one or more people. Given the description given by the player, his responsibility is to interpret the information received, decrypt the solution of the puzzle and tell the player how to solve it.

The instructions for the puzzles can be located outside the server room (photos on the wall, posters, etc.). 

Given the above, at least two people must solve the room tasks together in constant communication and also under constant pressure, which can lead to errors in their execution. 


### Maze
In this puzzle the player faces an interface that only displays two dots within an 8x8 matrix. The idea is that by using four buttons that indicate directions (arrows), the player can move one point to the position of the other without making mistakes. 

How do errors occur? It turns out that both points are actually inside a maze, which the player cannot see on his interface. To solve the maze, the instructor must find the solution hidden somewhere and point out the solution correctly.

Example:

In the figure, on the left is what the player sees and on the right is the solution mean for the instructor. Once the player indicates the position of both points, the instructor will be able to identify the solution and transmit it.

<p align="center">
  <img src="https://i.ibb.co/qjjNtwR/maze.png" width="70%" />
</p>
<p align="center">
Figure: Left, what the player faces. Right, solution map for instructor.
</p> 

**Note:** If the player presses a button leading to a wrong sequence, the puzzle is restarted with the markers in different positions.<br/>
<br/>

The solution for the maze showed in the figure above would be:
```
↑ → ↑ ← ↑ ↑ ↑ ↑ ↑ ← ← ← ↓ ← ← ↑
```

### Simon *did not* say 
A slightly more complex version of the traditional "Simon Says" game. Here, the player must repeat a given sequence of colors by pressing the corresponding buttons, only that this sequence of colors is "coded", this means that the color red does not necessarily mean repeating red, but another color. 

As an example:  

The player faces the following sequence of colors: 
```
Red → White → Pink → Green    
```
And the instructor has the following relation:  
```
Red     →  Yellow 
Green   →  Pink 
Blue    →  Red 
Yellow  →  Blue 
Pink    →  White 
White   →  Green 
```
The instructor should tell the player to press the following sequence:  
```
Yellow → Green → White → Pink
```

## Environment Design
First, let's start by defining how we imagine the server part and how the components of each puzzle will be distributed. 

In the sketch below (kudos to Cristina), it is possible to identify the server (1), which is where the puzzle "MAZE" and the IP sequence will be developed. A little lower, it is possible to identify the table or "desk" (2) where the puzzle "Simon didn't say" will be developed. Also, it may seem strange the gap that exists in one of the servers (the right one), but the purpose of that space is to give a defined volume to group 6 so they can implement their puzzle. 

<p align="center">
  <img src="https://i.ibb.co/qFjp7jR/SR-G8.png" width="85%" /> 
</p>

The main construction material will be wood, due to its price and ease of work. The servers and the table will be constructed by means of an internal wooden frame, which will be covered with other wood planks and then painted. In addition, since these structures will be hollow inside, the lighting will be given by a large internal light source (led strip) and a series of holes in the external structure, thus avoiding the installation of individual LEDs. 

### Bill of Materials

#### Electronics

|  Name  | Qty. | Link | Price |
| ------------- | :---:  |------------- |:---  |
| ESP32  | 3  | https://amzn.to/33NX7Im  |€ 23,00  | 
| LCD  | 1  | https://amzn.to/354K7hw  |€ 17,00  |
| Big button*  | 1  | https://amzn.to/2QhkmGH  | € 10,00  |
| Small button  | 1  | https://amzn.to/2CH2TPV  | € 13,00  |
| Numpad  | 1  | https://amzn.to/2OpIu7N  | € 6,00  |
| Power  | 1  | https://amzn.to/355zCLg  | € 10,00  |
| Jumpers  | 1  | https://amzn.to/2CHOzXt  | € 10,00  |
| Buzzer  | 1  | https://amzn.to/2qfmEeP  | € 7,00  |
| Breadboards  | 1  | https://amzn.to/2rOlh7j  | € 5,50 |
| Prototype Boards  | 1  | https://amzn.to/2rOlh7j | € 6,00  |
| Transistors  | 10  | https://bit.ly/2OorPkZ  | € 7,50  |
| Step-Up  | 1  | https://amzn.to/352Vy9M  | € 6,00  |
| Led Strip  | 1  | https://amzn.to/2rQ7eOD | € 38.99  |
| **TOTAL**  |  |   | € 159,99  |

\* We find the purchase of this product crucial. Science has shown no one can resist pressing its shiny surface.


#### Fabrication

For a detailed view of what is being ordered in the first and second items, please refer to the pdf documents of the chipboard and Rahmenholz cutting list.The name of the documents is Cutlist_1 and Cutlist_2 respectively. 

|  Name  | Qty. | Link | Price | Comment |
| ------------- | :---:  |------------- |:---  | ------------- |
| Rahmenholz | 9 | https://bit.ly/2XnkWEl | € 19,71 | € 2,19 each 300 x 3,8 x 3,8 cm |
| Nagel | 1 | https://bit.ly/2Omgim9 | € 2,80 | Ø x L: 1.4 x 25 mm, 400 pcs |
| Nagel | 1  | https://bit.ly/33YbGcy | € 4,20 | Ø x L: 2.8 x 65 mm, 1.000 pcs |
| Stuhlwinkel | 2  | https://bit.ly/2OoOQ76 | € 0,50  | € 0,25 each |
| Montageband | 1  | https://bit.ly/2pqh1Ku | € 7,50 |  1,5 m x 19 mm; 10 kg/m |
| Hinge | 4  | https://bit.ly/2Qyiee5 | € 4,80 | € 1,20 each, 60 x 34 mm |
| Glasfolie | 1  | https://bit.ly/2Kukcs0 | € 5,45  | 200 x 45 cm, opal, self-adhesive |
| **TOTAL**  |  |   | € 44.96  |


Regarding the wood boards, it was decided to use the ones available at the faculty, and the cutlist was updated in order to build a simpler design.