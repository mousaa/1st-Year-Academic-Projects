****************************************************
Ahmed Mousa		0927129
CIS 2500		Assignment 2
February 17/2016
****************************************************


************
Compilation
************
To compile this program execute the following command while in A2 directory:
gcc -lncurses src/main.c src/checkFile.c src/parsing.c src/curses.c src/checkWindow.c src/userInterface.c src/playerMove.c -Iinclude -Wall -std=c99 -o rogue


***********************
Running the program(s)/Usage
***********************
To run the program type the following command from the root directory of the assignment:
./rogue assets/level.txt

Program will scan level file for room dimensions and position of elements then move to ncurses to print all the rooms and initialize the game. 

***********************
Testing
***********************
The following files have been tested in order to minimize and identify errors in the program:
1. assets/Testing/1.txt:
   Used to check that the hero can start in any room other than the first and that the order doesnt matter(doors dont have to be first)

2. assets/Testing/2.txt:
   Used to make sure program can handle an empty file with just room dimensions.

3. assets/Testing/3.txt:
   Used to make sure program can handle more than one item of same type in 1 room and hold 10 items.
   

*****************
Known Limitations
*****************
This program has quite a few limitations even though it has error checking. Some of the limitations are:
- Hero can’t step on doors located on corners
- If user doesn’t press the correct input to move(w,a,s,d) the hero just disappears, cursor is still on the same place.
- Program simply exits if the rooms in level file wont fit on the terminal screen. 
- If level file has more than 10 items(excluding door and room dimensions) program behaves strangely, and could possibly cause a segfault.
- Program assumes that level file will follow specification. (i.e 1 big gold to track, file line is not greater than 150)
- can still handle room dimensions greater than the maximum described in specification
- if level file just contains room dimensions, rooms will print and cursor will be next to last room printed.
- if 2 items are in the same spot in the room, the item that is read last in the level file will overwrite the other one
- hero teleports to the first door found in the level file for the destination room.
- Program only keeps track of gold. 
     
****************
References
****************

No references other than professor Justin’s lectures were used for this assignment.
- NOTE: Reused functions from A1 CIS*2500 W16, modified slightly to meet criteria of this project. (checkFile, checkArgc).
