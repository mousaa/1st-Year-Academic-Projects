#ifndef _MOUSAA_PARSING_
#define _MOUSAA_PARSING_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //FOR SRAND

/**
 * struct item
 * used to store the max of 10 items in a room
 * type corresponds to the symbol of the item
 * posY/X = location in the room
 * will be statically allocated (item[10]) in struct room
 */
typedef struct item
{
    char type; //symbol for item
    int posY;
    int posX;
} Item;

/**
 * struct door
 * used to store the max of 4 doors in a room
 * side corresponds to n,w,e,s
 * pos = location in each wall
 * will be statically allocated ([4]) in struct room
 */
typedef struct door
{
    int pos;
    char side;
}Door;

/**
 * struct room
 * used to store all information about room
 * including elements, doors and room dimensions
 * also holds the sum of biggold and smallgold values
 * of each room as the hero steps on them.
 * will be dynamically allocated (*6) in program
 */
typedef struct room
{
    //room dimensions
    int yDim;
    int xDim;

    //holds sum of all gold collected throughout all the rooms
    int bigGold;
    int smallGold;

    Door door[4]; //max of 4 doors per room
    Item elements[10]; //10 items per room
}Room;

/**
 * parseLevel
 * parses through the level file delimited by space and stores in struct room
 * IN: file to parse
 * OUT:  Room* pointer (struct containing all information about level)
 * POST: stores all information regarding each room in struct room
 * NOTE: will malloc for 6 of Room in this function.
 *       will free either in endGame or errorMsg function depending
 *       on if the program excuted successfully or not.
 */
Room* parseLevel(FILE* f);

#endif
