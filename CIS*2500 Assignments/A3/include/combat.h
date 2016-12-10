#ifndef _MOUSAA_COMBAT_
#define _MOUSAA_COMBAT_


#include "curses.h"


/*
 * fight
 * combat of heros with monsters
 * IN: room struct, coordinates of hero, enemy that hero is about to encounter
 */
void fight(Room* room, int y, int x, int oldy, int oldx, char enemy);
#endif