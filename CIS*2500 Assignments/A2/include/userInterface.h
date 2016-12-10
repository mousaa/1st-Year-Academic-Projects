#ifndef _MOUSAA_USERINTERFACE_
#define _MOUSAA_USERINTERFACE_


#include "curses.h"

/**
 * printRoom
 * Prints rooms in the level file
 * IN: Room* pointer (struct containing all information about level)
 *     int y,x (starting coordinates y & x), and (int) - room number
 * OUT: none
 * POST: prints just the room being sent in the function not all of them
 *        need to call 6 times.
 */
void printRoom(int y, int x, Room* room, int roomNum);

/**
 * placeDoors
 * Puts all doors in map
 * IN: Room* pointer (struct containing all information about level),
       (int) - tallest room value, (char) - location of door(e,w,n,s)
 * OUT: none
 * POST: puts door in location called, need to call 4 times for each side.
 */
void placeDoors(Room* room, int tall, char location);

/**
 * placeItem
 * Puts all items in map from the level file
 * IN: Room* pointer (struct containing all information about level),
 *     (int) - tallest room value, (char) - symbol to print,
 * OUT: none
 * POST: need to call each item seperatly(item == symbol, i.e hero == '@')
 */
void placeItem(Room* room,int tall, char type);

#endif
