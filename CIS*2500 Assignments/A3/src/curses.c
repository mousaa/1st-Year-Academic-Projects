/**
 * see curses.h for complete function definitions
 *
 */

#include "curses.h"
#include "userInterface.h"
#include "checkWindow.h"
#include "playerMove.h"
#include "endMsg.h"
#include "enemyMove.h"
#include "combat.h"
 

void startGame(Room *room)
{
	windowSize(room);//checks terminal size
	noecho();
	cbreak();
	int tallest;
	int tallest_bot;

	tallest_bot = findTallest_bot(room);
	tallest = findTallest(room);

	printStatus(room, tallest, tallest_bot);



	
	// DRAWING ROOMS.
	//SPACE*2 to account for space between room1&r2 + r2+r3.
	printRoom(STARTY, STARTX , room ,0);
	printRoom(STARTY, STARTX + (room[0].xDim + SPACE) , room, 1);
	printRoom(STARTY, STARTX + (room[1].xDim + room[0].xDim + SPACE*2), room, 2);

	//bottom rooms
	printRoom(STARTY + SPACEY + tallest , STARTX, room, 3);
	printRoom(STARTY + SPACEY + tallest, STARTX + (room[3].xDim + SPACE), room, 4);
	printRoom(STARTY + SPACEY + tallest , STARTX + (room[3].xDim + room[4].xDim + SPACE*2), room, 5);

	placeDoors(room, tallest, tallest_bot, 'n');
	placeDoors(room, tallest, tallest_bot, 's');
	placeDoors(room, tallest, tallest_bot,  'w');
	placeDoors(room, tallest, tallest_bot, 'e');


	printStatus(room, tallest, tallest_bot);
	/* calls each item seperately.
	 * nothing happens if item is not in struct
	 * i.e was not in the level file.
	 */
	placeItem(room, tallest, '<');
	placeItem(room, tallest, '>');
	placeItem(room, tallest, '*');
	placeItem(room, tallest, '8');
	placeItem(room, tallest, ')');
	placeItem(room, tallest, '(');
	placeItem(room, tallest, ']');
	placeItem(room, tallest, 'A');
	placeItem(room, tallest, 'B');
	placeItem(room, tallest, 'S');
	placeItem(room, tallest, 'Z');
	placeItem(room, tallest, 'T');
	placeItem(room, tallest, '!');
	placeItem(room, tallest, '@');
}

void gameLoop(Room* room)
{
	char key;//user key (a,w,s,d)
	do
    {
		key = getch();
		moveHero(room, key); //moving hero + anything related to hero movement(collision, teleport)
		refresh();
	} while (key!= 'q'); //quit
}
void endGame(Room* room)
{
	endwin();
	printGold(room);
	printInventory(room);
	free(room);
}
