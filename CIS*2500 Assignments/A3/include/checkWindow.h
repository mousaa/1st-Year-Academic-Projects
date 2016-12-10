#ifndef _MOUSAA_WINDOWSIZE_
#define _MOUSAA_WINDOWSIZE_

#include "curses.h"

/**
 * findTallest
 * Finds the tallest room from the 3 in the top
 * IN: Room* pointer (struct containing all information about level)
 * OUT: tallest room found + 2 so top and bottom walls wont overlap.
 *	(no need to account for that when its time to draw rooms, just get the return value of function without adding 2)
 */
int findTallest(Room* room);

/**
 * findTallest_bot
 * Finds the tallest room from the 3 in the bot
 * IN: Room* pointer (struct containing all information about level)
 * OUT: tallest room found in the bot
 */
int findTallest_bot(Room *room);
/**
 * windowSize
 * Checks the terminal size will fit the 6 rooms in the level file
 * Checks if either width/height cant fit.
 * IN: Room* pointer (struct containing all information about level)
 * OUT: none
 * POST: Calls errorMsg() and prints appropriate message if terminal
 *       size is too small.
 *
 * note: ncurses is initialized here. (initscr)
 */
void windowSize(Room* room);

/**
 * errorMsg
 * Asks user to resize terminal to fit the 6 rooms and exits
 * IN: Room* pointer (struct containing all information about level)
 * OUT: none
 * POST: exits the program and frees allocated memory
 */
void errorMsg(Room* room);

#endif
