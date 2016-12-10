#ifndef _MOUSAA_NCURSES_
#define _MOUSAA_NCURSES_

#include <ncurses.h>
#include "parsing.h"
#define STARTY 5 //STARTING Y POSITION TO PRINT FIRST ROOM 
#define STARTX 5 //STARTING X POS
#define SPACE 6 //SPACE BETWEEN ROOMS SO WALLS DONT OVERLAP (width)
#define SPACEY 4. //space between top and bottom rooms
#define BOTSPACE 3 //RESERVED SPACE AT THE BOTTOM FOR STATUS BAR
#define DOOR '+'
#define HERO '@'
#define STARTHALL 2 
#define HALLWAY '#'


/** startGame
 * Draws level to the screen
 * IN:  Room* pointer (struct containing all information about level)
 * OUT: none
 * POST: Calls various functions to check window size, print the rooms
         and place all items in level.
 */
void startGame(Room *room);

/** gameLoop
 * Main game loop that holds all other functions neccessary for movement/teleportation
 * IN:  Room* pointer (struct containing all information about level)
 * OUT: none
 * POST: you play the game.
 */
void gameLoop(Room *room);

/** endGame
 * deinitializes ncurses when called
 * either when user hits 'q'/ steps on stairs
 * IN:  Room* pointer (struct containing all information about level)
 * OUT: none
 * POST: prints out total gold collected during the level
 */
void endGame(Room * room);

#endif