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
void moveHero(Room* room,  char key);
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
 * checkInput
 * checks user input after telporting
 * incase user decides to quit while hes on the door
 * IN: Room struct(for endGame(room)), new hero coordinates y, x
 * OUT: none
 * POST: calls endGame printing the message about total gold collected.
 */
void checkInput(Room* room, int y, int x);


/**
 * checkBag 
 * check hero's bag to make sure it can fit one item in inventory
 * IN: Room struct, coordinates of hero, char to represent either item, rare weapon etc..
 *
 */
int checkBag(Room* room, int y, int x, char z);

/**
 * createStat
 * creates stat for the weapon/equipment hero steps on
 * IN: Room struct, ctr incremented for when to print how many weapons picked up, char z representing what to create a stat for
 *
 */
void createStat(Room* room, int itemCtr, char z);

/**
 * stepOn
 * hero steps on any item/monster etc 
 *IN: room struct, coordinates(new and old)
 *
 */
void stepOn(Room* room, int y, int x, int oldy, int oldx);


#endif
