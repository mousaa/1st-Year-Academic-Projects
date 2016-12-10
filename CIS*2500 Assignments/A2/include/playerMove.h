#ifndef _MOUSAA_PLAYERMOVE_
#define _MOUSAA_PLAYERMOVE_

#include "curses.h"

/**
 * moveHero
 * takes in key from user and moves the hero
 * IN: Room* struct, key(from user)
 * OUT: none
 * POST: calls function for collision detection before moving hero
 */
void moveHero(Room* room,char key);

/**
 * nextPos
 * Collision detection function, checks what the hero
 * is going to step on before moving him to the location
 * IN: current coordinates y,x
 * OUT: returns numbers ranging from 0-5, each corresponding
 *	    whatever the hero stepped on
 * POST: returns result to moveHero function to decide what to do
 */
int nextPos(int y, int x);

/**
 * currentRoom
 * Gives you what the current room the hero is in
 * based on where the cursor is
 * IN: Room* struct
 * OUT: returns numbers ranging from 0-5, each corresponding
 *	    whatever room the hero is in
 * POST: used to store gold values & for room teleportation
 */
int currentRoom(Room* room);

/**
 * gotoDoor
 * Teleports hero to the next room
 * IN: Room* struct, int nextRoom which is decided based on
 *	   return value of currentRoom
 * OUT: none
 * POST: teleports hero to the first door found in the struct
 *		 i.e first door in the level file.
 */
void gotoDoor(Room* room, int nextRoom);

/**
 * checkInput
 * checks user input after telporting
 * incase user decides to quit while hes on the door
 * IN: Room struct(for endGame(room))
 * OUT: none
 * POST: calls endGame printing the message about total gold collected.
 */
void checkInput(Room* room);

#endif
