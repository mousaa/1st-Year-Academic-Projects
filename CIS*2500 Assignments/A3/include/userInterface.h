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
 * printStatus
 * Prints status with initial stats of hero
 * IN: Room* pointer (struct containing all information about level)
 *     tallest rooms in the top and bot to know where to put the status bar
 * OUT: none
 */
void printStatus(Room* room, int tallest, int tallest_bot);


/**
 * printHallways
 * Prints hallways after doors and in middle and top,bottom of rooms and connects them to doors
 * IN: Room* pointer (struct containing all information about level)
 *     tallest rooms in the top and bot to know where to put the status bar
 * OUT: none
 * POST: hallways printed
 */
void printHallways(Room* room, int tallest, int tallest_bot);

/**
 * placeDoors
 * Puts all doors in map
 * IN: Room* pointer (struct containing all information about level),
       (int) - tallest room value, (char) - location of door(e,w,n,s)
 * OUT: none
 * POST: puts door in location called, need to call 4 times for each side.
 */
void placeDoors(Room* room, int tall, int tallest_bot, char location);

/**
 * placeItem
 * Puts all items in map from the level file
 * IN: Room* pointer (struct containing all information about level),
 *     (int) - tallest room value, (char) - symbol to print,
 * OUT: none
 * POST: need to call each item seperatly(item == symbol, i.e hero == '@')
 */
void placeItem(Room* room,int tall, char type);

/**
 * printNotification
 * Prints notification based on what the hero does
 * IN: Room* pointer (struct containing all information about level)
 *     int y,x,oldy,oldx (coordinates,old coordinates), character that represents what to print
 *		int damage incase hero looses health/attack
 * OUT: none
 */
void printNotification(Room* room,int y, int x, int oldy, int oldx, char z, int damage);

/**
 * updateStatus
 * updates hero status based on combat/item pickup potion pickup etc.
 * IN: Room* pointer (struct containing all information about level)
 *     ctr for what to increment(i.e inventory count), int id to characterize what to change 
 * i.e 1 represents updating hero attack
 * OUT: none
 */
void updateStatus(Room* room, int itemCtr, int id);

#endif
