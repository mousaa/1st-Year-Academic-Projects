/**
 * see curses.h for complete function definitions
 *
 */

#include "curses.h"
#include "userInterface.h"
#include "checkWindow.h"
#include "playerMove.h"

void startGame(Room *room)
{
	windowSize(room);//checks terminal size
	noecho();
	cbreak();
	int tallest;

	// DRAWING ROOMS.
	//SPACE*2 to account for space between room1&r2 + r2+r3.
	printRoom(STARTY, STARTX , room ,0);
	printRoom(STARTY, STARTX + (room[0].xDim + SPACE) , room, 1);
	printRoom(STARTY, STARTX + (room[1].xDim + room[0].xDim + SPACE*2), room, 2);

	tallest = findTallest(room);
	//bottom rooms
	printRoom(STARTY + tallest , STARTX, room, 3);
	printRoom(STARTY + tallest, STARTX + (room[3].xDim + SPACE), room, 4);
	printRoom(STARTY + tallest , STARTX + (room[3].xDim + room[4].xDim + SPACE*2), room, 5);

	//puts all items/doors in rooms
	placeDoors(room, tallest, 'n');
	placeDoors(room, tallest, 's');
	placeDoors(room, tallest, 'w');
	placeDoors(room, tallest, 'e');

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
	int bigGold;
	int smallGold;
	smallGold = room[0].smallGold + room[1].smallGold + room[2].smallGold + room[3].smallGold + room[4].smallGold + room[5].smallGold;
	bigGold = room[0].bigGold + room[1].bigGold + room[2].bigGold + room[3].bigGold + room[4].bigGold + room[5].bigGold;
	printf("\nTotal gold collected: %d\n\n", bigGold + smallGold);
	free(room);
}
