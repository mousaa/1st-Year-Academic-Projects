/**
 * see checkWindow.h for complete function definitions
 *
 */
#include "checkWindow.h"

int findTallest(Room* room)
{
	int tallest;


	// basic math to find out tallest room
	if((room[0].yDim >= room[1].yDim) && (room[0].yDim >= room[2].yDim))
    {
		tallest = room[0].yDim;
	}
	else if ((room[1].yDim >= room[0].yDim) && (room[1].yDim >= room[2].yDim))
    {
		tallest = room[1].yDim;
	}
	else
    {
		tallest = room[2].yDim;
	}
	return tallest; //tallest room.
}
int findTallest_bot(Room *room)
{
	int tallest; 

	if((room[3].yDim >= room[4].yDim) && (room[3].yDim >= room[5].yDim))
    {
		tallest = room[3].yDim;
	}
	else if ((room[4].yDim >= room[3].yDim) && (room[4].yDim >= room[5].yDim))
    {
		tallest = room[4].yDim;
	}
	else
    {
		tallest = room[5].yDim;
	}
	return tallest; //tallest room.
}

void windowSize(Room* room)
{
	initscr(); //INITIALIZES NCURSES

	int tallest;
	int yMax;
	int xMax;
	int sumX1;
	int sumX2;

	tallest = findTallest(room); //tallest room in the top

	/* total width the top rooms, bottom rooms occupy
	 * takes into account the space between the rooms
	 * and starting x coordinate of first rooms
	 */
	sumX1 = STARTX + (SPACE*2) + room[0].xDim + room[1].xDim + room[2].xDim +3 ;//2 for hallways
	sumX2 = STARTX + (SPACE*2) + room[3].xDim + room[4].xDim + room[5].xDim +3; //2 for hallways

	getmaxyx(stdscr, yMax, xMax);//screen size

	for (int i = 3; i < 6; i++)
    {
		/* checking if tallest room in top + any rooms in bottom
		 * will be greater than the yMax (screen -y- size).
		 * takes into account starting y coordinate of rooms.
		 */
		if((STARTY + SPACEY + tallest + room[i].yDim + BOTSPACE) >= yMax)
        {
			errorMsg(room);
		}
	}
	//screen -x- size
	if((sumX1 >= xMax) || (sumX2 >= xMax))
    {
		errorMsg(room);
	}
}

void errorMsg(Room* room)
{
	endwin(); //deinitializes ncurses
	printf("\n****** ERROR ******\n");
	printf("Rooms will not fit in current terminal screen\n");
	printf("Resize terminal  and try again\n\n");
	free(room);
	exit(1);
}
