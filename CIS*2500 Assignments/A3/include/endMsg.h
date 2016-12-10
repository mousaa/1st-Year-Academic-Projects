#ifndef _MOUSAA_ENDMSG_
#define _MOUSAA_ENDMSG_

#include "curses.h"

/*
 *printGold
 *prints total gold collected by hero at end of game
 * IN: room struct
 */
void printGold(Room* room);
/*
 *printInventory
 *prints items/weaponsns collected by hero at end of game
 * IN: room struct
 */
void printInventory(Room* room);
#endif
