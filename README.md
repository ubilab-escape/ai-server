# AI-Server &amp; Puzzles

The information contained in this readme document ~~is highly classified and~~ describe the fabrication and coding for different puzzles implemented in the **UbiLab - Escape Room**.


## Motivation
**[Group 8](https://github.com/ubilab-escape/ai-server)** are the designers and builders of the server room, the temple where the brain of a high-tech artificial intelligence called **"STASIS"** is located and all the equipment necessary to keep it running.

Our responsibilities are: 

* The manufacture of the technical equipment that allows STASIS to remain in operation, through the use of state-of-the-art materials and technologies.

* The design and implementation of complex algorithms to prevent access to STASIS source code and also, the two wires that allows any stranger to shut it down directly, which leads to a safe and direct exit from the high-security complex aka: The Escape Room.

### Team Members
* Cristina Maurette
* Konstantin Kuliabin
* Claudio Ray 

### Work done
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
We visualize the Escape Room as a sequence of stages ending in the server room (our responsibility). Therefore, given the following flow chart, we infer the following sequence:

<p align="center">
  <img src="https://i.ibb.co/2KYccVk/flow.png" width="95%" /> 
</p>

#### Stage 0
This stage is like the preamble or the conditions that are needed to start the next stage. In this case would be to open the second door of the Escape Room to access the server room, finishing the puzzles of [Group 7](https://github.com/ubilab-escape/second-door).

#### Stage 1
Once players can access the server room, the next stage is to send the data to the client, by finishing the [Group 6](https://github.com/ubilab-escape/prototype) puzzle and successfully solving:

* [Maze](https://github.com/ubilab-escape/ai-server/tree/master/Puzzle%201%20Maze)
* [IP](https://github.com/ubilab-escape/ai-server/tree/master/Puzzle%203%20IP)

The puzzles must be solved regardless of the order.

Once the IP is inserted, a mock "Access Granted" messagge will appear, which means that the data hass been accessed/sent properly

<p align="center">
  <img src="https://www.avecsys.com/wp-content/uploads/2014/11/access-granted-hacked.jpg" width="35%" /> 
</p>


#### Stage 2
In this final stage, players must kill STASIS core and solve the [Simon didn't say](https://github.com/ubilab-escape/ai-server/tree/master/Puzzle%202%20Simon) puzzle in order to shut it down. 

Once the puzzle is solved a big red button turns ON. Once the participants press it, the escape room has been completely solved.


## Puzzles

The dynamic of the puzzles is based on a constant communication similar to the game "Keep talking and nobody dies", that means that the instructions for the puzzles can be located outside/inside the server room (posters, secret messages, etc.). The implemented puzzles (explained below) names are:

* Maze
* IP
* Simon didn't say

Given the above, at least two participants must try to solve the room tasks together. For ease of explanation, participants will be named in two ways:

* **Player:** Is the one who physically faces the puzzle. His role is to describe the characteristics of the puzzle and according to the commands of the instructor, solve it. 
* **Instructor:** Can be one person or more. Using the descriptions given by the player, his/her/their responsibility is to interpret the information received, decrypt the solution of the puzzle and tell the player how to solve it.
 

### Puzzle 1 - Maze
In this puzzle the player faces an interface that only displays two dots within an 8x8 matrix. The idea is that by using four buttons that indicate directions (arrows), the player can move one point to the position of the other without making mistakes. 

How do errors occur? It turns out that both points are actually inside a maze, which the player cannot see on his interface. To solve the maze, the instructor must find the solution hidden on a poster somewhere and point it out correctly.

The information related to the puzzle: its components and source code, is found in the Puzzle 1 Maze [folder](https://github.com/ubilab-escape/ai-server/tree/master/Puzzle%201%20Maze).


### Puzzle 2 - Simon *didn't* say 
A slightly more complex version of the traditional "Simon Says" game. Here, the player must repeat a given sequence of colors by pressing the corresponding buttons, only that this sequence of colors is "coded", this means that the color red does not necessarily mean repeating red, but another color. 

All the information related to the puzzle: its fabrication and source code, is found in the Puzzle 2 Simon [folder](https://github.com/ubilab-escape/ai-server/tree/master/Puzzle%202%20Simon).

### Puzzle 3 - IP 
By the activation of the puzzle, the player is asked on the LCD screen to insert the IP address using the keyboard. The IP address (unknown by the players) is written on the walls of the server room and the escape room with a UV marker; in order to find it, a UV flashlight (placed inside the server room) must be used. 

The source code and the information for the IP puzzle is found in the puzzle 3 IP [folder](https://github.com/ubilab-escape/ai-server/tree/master/Puzzle%203%20IP).


## Environment Design
First, let's start by defining how we imagine the server part and how the components of each puzzle are distributed. 

In the sketch below (kudos to Cristina), it is possible to identify the server (1), which is where the puzzles Maze and IP are developed. A little lower, it is possible to identify the table or "desk" (2) where the puzzle "Simon didn't say" is developed. Also, it may seem strange the gap that exists in one of the servers (the right one), but the purpose of that space is to give a defined volume to [Group 6](https://github.com/ubilab-escape/prototype) so they can implement their puzzle. 

<p align="center">
  <img src="https://i.ibb.co/qFjp7jR/SR-G8.png" width="85%" /> 
</p>

The main construction material is wood, due to its price and ease of work. All information about the servers and the LED-lighting is found in the Servers + LEDs code [folder](https://github.com/ubilab-escape/ai-server/tree/master/Servers%20%2B%20LEDs%20code).

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

For a detailed view of what is being ordered in the first and second items, please refer to the pdf [documents](https://github.com/ubilab-escape/ai-server/blob/master/Servers%20%2B%20LEDs%20code/OSB-Platte%20Cutlist%20(12mm).pdf) in the Servers + LEDs code [folder](https://github.com/ubilab-escape/ai-server/tree/master/Servers%20%2B%20LEDs%20code). 

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