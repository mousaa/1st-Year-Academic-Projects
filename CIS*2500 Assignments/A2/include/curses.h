#ifndef _MOUSAA_NCURSES_
#define _MOUSAA_NCURSES_

#include <ncurses.h>
#include "parsing.h"
#define STARTY 3 //STARTING Y POSITION TO PRINT FIRST ROOM (I.E '.') NOT WALLS.
#define STARTX 2 //STARTING X POS
#define SPACE 3 //SPACE BETWEEN ROOMS SO WALLS DONT OVERLAP (width)
#define DOOR '+'
#define HERO '@'

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
