#ifndef _MOUSAA_ENEMYMOVE_
#define _MOUSAA_ENEMYMOVE_
#include "curses.h"

/* moveEnemy
 * moves enemy in map
 * IN: room struct
 */
void moveEnemy(Room *room);

/* SNAKECYCLE, ZOMBIECYCLE, BATCYCLE, TROLLCYCLE
 * moves enemy in map based on their cycle
 * IN: room struct, int room numer(i), j for element number, and coordinates 
 * of monsters.
 */
void snakeCycle(Room* room, int i, int j , int posY, int posX);
void zombieCycle(Room* room, int i, int j, int posY, int posX);
void batCycle(Room* room, int i, int j, int posY, int posX);
void trollCycle(Room* room, int i, int j, int posY, int posX);


#endif