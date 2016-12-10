/**
 * see userInterface.h for complete function definitions
 *
 */
#include "userInterface.h"
#include "playerMove.h"
#include "checkWindow.h"

void printStatus(Room* room, int tallest,  int tallest_bot)
{
	move(STARTY + SPACEY + tallest_bot + tallest + BOTSPACE, 0);
	printw("Health: %d, Potions: %d, Attack: %d, Inv: %d/5\n", room[0].hero.health, room[0].hero.potion, room[0].hero.attackRate, room[0].hero.capacity);
}

void printNotification(Room* room, int y, int x, int oldy, int oldx, char z, int damage)
{
	switch(z)
	{
		case ')':
			if (!checkBag(room,y,x, ')'))
			{
				stepOn(room, y,x, oldy, oldx);
				mvprintw(0,0,"Hero stepped on common weapon, and broke it");
				move(y,x);
				checkInput(room, y, x);
				move(y,x);
				break;
			}
			else
			{
				stepOn(room, y,x, oldy, oldx);
				mvprintw(0,0,"Hero picked up common weapon item");
				move(y,x);
				checkInput(room, y, x);
				move(y,x);
				break;
			}		
		case '(':
			if (!checkBag(room, y, x, '('))
			{
				stepOn(room, y,x, oldy, oldx);
				mvprintw(0,0,"Hero stepped on rare weapon, and broke it");
				move(y,x);
				checkInput(room, y, x);
				move(y,x);
				break;
			}
			else
			{
				stepOn(room, y,x, oldy, oldx);
				mvprintw(0,0,"Hero picked up rare weapon item");
				move(y,x);
				checkInput(room, y, x);
				move(y,x);
				break;
			}
		case ']':
			if (!checkBag(room, y, x, ']'))
			{
				stepOn(room, y,x, oldy, oldx);
				mvprintw(0,0,"Hero stepped on equipment, and broke it");
				move(y,x);
				checkInput(room, y, x);
				move(y,x);
				break;
			}	
			else
			{
				stepOn(room, y,x, oldy, oldx);
				mvprintw(0,0,"Hero picked up equipment item");
				move(y,x);
				checkInput(room, y, x);
				move(y,x);
				break;
			}
		case '!':
			{
				stepOn(room, y,x, oldy, oldx);
				mvprintw(0,0, "Hero picked up a potion");
				updateStatus(room, room[0].hero.potion, 2);
				move(y,x);
				checkInput(room,y,x);
				move(y,x);
				break;
			}
		case '+':
			{
				mvprintw(0,0, "Hero opened a door");
				move(y,x);
				checkInput(room,y,x);
				move(y,x);
				break;
			}
		case 'G':
			{
				mvprintw(0,0, "Hero caused %d damage", damage);
				move(oldy,oldx);
				checkInput(room,y,x);
				move(oldy,oldx);
				break;
			}
		case 'T':
			{
				mvprintw(0,0, "Hero lost %d attack", damage);
				move(oldy,oldx);
				checkInput(room,y,x);
				move(oldy,oldx);
				break;
			}
		case 'H':
			{
				mvprintw(0,0, "Hero lost %d health", damage);
				move(oldy,oldx);
				checkInput(room,y,x);
				move(oldy,oldx);
				break;
			}
		case 'A':
			{
				mvprintw(0,0, "Hero killed aquator");
				move(y,x);
				checkInput(room,y,x);
				move(y,x);
				break;
			}
		case 'M':
			{
				mvprintw(0,0, "Hero killed troll");
				move(y,x);
				checkInput(room,y,x);
				move(y,x);
				break;
			}
		case 'Z':
			{
				mvprintw(0,0, "Hero killed zombie");
				move(y,x);
				checkInput(room,y,x);
				move(y,x);
				break;
			}
		case 'B':
			{
				mvprintw(0,0, "Hero killed bat");
				move(y,x);
				checkInput(room,y,x);
				move(y,x);
				break;
			}
		case 'S':
			{
				mvprintw(0,0, "Hero killed snake");
				move(y,x);
				checkInput(room,y,x);
				move(y,x);
				break;
			}
	}
}	

void updateStatus(Room* room, int ctr, int id)
{
	int tallest;
	int tallest_bot;
	tallest = findTallest(room);
	tallest_bot = findTallest_bot(room);
	switch(id)
	{
		case 1: //health
			move(STARTY + SPACEY + tallest_bot + tallest + BOTSPACE, 0);
			printw("Health: %d, Potions: %d, Attack: %d, Inv: %d/5\n", ctr, room[0].hero.potion, room[0].hero.attackRate, room[0].hero.capacity);
			break;
		case 2: //potion
			move(STARTY + SPACEY + tallest_bot + tallest + BOTSPACE, 0);
			printw("Health: %d, Potions: %d, Attack: %d, Inv: %d/5\n", room[0].hero.health, room[0].hero.potion, room[0].hero.attackRate, room[0].hero.capacity);
			break;
		case 3://attack
			move(STARTY + SPACEY + tallest_bot + tallest + BOTSPACE, 0);
			printw("Health: %d, Potions: %d, Attack: %d, Inv: %d/5\n", room[0].hero.health, room[0].hero.potion, ctr, room[0].hero.capacity);
			break;
		case 4: //inventory
			move(STARTY + SPACEY + tallest_bot + tallest + BOTSPACE, 0);
			printw("Health: %d, Potions: %d, Attack: %d, Inv: %d/5\n", room[0].hero.health, room[0].hero.potion, room[0].hero.attackRate, ctr+1);
			break;
	}
}

void printRoom(int y, int x, Room* room, int roomNum)
{
	/*
	 * prints room dimensions as '.'
	 * x,y correspond to arbitary starting points defined in "curses.h"
	 */
	for (int i = x ; i < (x + room[roomNum].xDim) ; i++)
    {
		for (int j = y; j < (y + room[roomNum].yDim); j++)
        {
			mvaddch(j,i,'.');
		}
	}

	//walls
	for(int i = x - 1; i <= (x + room[roomNum].xDim); i++)
    {
		mvaddch(y - 1, i, '-'); //north wall
		mvaddch((y + room[roomNum].yDim), i , '-'); //south wall
	}

	for (int i = y; i < (y+ room[roomNum].yDim); i++)
    {
		mvaddch(i, x-1, '|'); //west wall
		mvaddch(i, (x + room[roomNum].xDim) , '|'); //east wall
	}
}
void printHallway(Room* room, int roomNum, int tall, int tallest_bot, int doorPos, char location)
{
	int xMax;
        int yMax;
	getmaxyx(stdscr, yMax, xMax); 
	
	
	for(int i = STARTY-1 - STARTHALL; i < STARTY + tall + STARTHALL; i++)
	{
		mvaddch(i, STARTX + room[0].xDim + 2, HALLWAY); //hallway going down between room 0 and 1
	}

	for(int i = STARTY-1 - STARTHALL; i < STARTY + tall + STARTHALL; i++)
	{
		mvaddch(i, STARTX + room[0].xDim + room[1].xDim + SPACE + 2, HALLWAY); //hallway going down between room 1 and 2
	}

	for(int i = STARTY-1 - STARTHALL; i <= STARTY + tall + STARTHALL; i++)
	{
		mvaddch(i, STARTX + room[0].xDim + room[1].xDim + room[2].xDim + SPACE*2 +2, HALLWAY); //2 and right edge of screen
	}

	for(int i = STARTY + tall + STARTHALL; i <= STARTY + SPACEY + tallest_bot + tall ; i++)
	{
		mvaddch(i, STARTX + room[3].xDim + SPACE-3, HALLWAY);  //between room room 3 and 4
	}

	for(int i = STARTY + tall + STARTHALL; i <= STARTY + SPACEY + tall + tallest_bot; i++)
	{
		mvaddch(i, STARTX + room[3].xDim + room[4].xDim + SPACE*2 - 3, HALLWAY); //between room 4 and 5 
	}

	for(int i = STARTY + tall + STARTHALL; i <= yMax - SPACEY; i++)
	{
		mvaddch(i, STARTX + room[3].xDim + room[4].xDim + room[5].xDim + SPACE*2 + 2, HALLWAY); //between 5 and right edge of screen
	}

	for(int i = STARTX-4; i <= xMax-2; i++)//STARTX + room[0].xDim + room[1].xDim + room[2].xDim + SPACE*2 + 2; i++)
	{
		mvaddch(STARTY+tall+STARTHALL, i, HALLWAY); //middle of screen
	}
	for(int i = STARTX-4; i <= xMax-2; i++)
	{
		mvaddch(STARTY-1 - STARTHALL, i, HALLWAY); //top 
	}
	for (int i = STARTY-1 -STARTHALL; i<= STARTY-1-STARTHALL + tall + SPACEY + tallest_bot + BOTSPACE; i++)
	{
		mvaddch(i, STARTX-1-STARTHALL, HALLWAY); //left edge of screen
	}
	switch(roomNum)
	{
		case 0:
			switch(location)
			{
				case 'n':
					for(int i = STARTY-1 - STARTHALL ; i <= STARTY-1; i++)
					{
						mvaddch(i, STARTX + doorPos, HALLWAY); //hallway going left
					}
					break;
				case 's':
					for(int i = STARTY + room[0].yDim; i <= STARTY + tall + STARTHALL; i++)
					{
						mvaddch(i, STARTX + doorPos, HALLWAY);
					}
						break;
				case 'e':
					for(int i = STARTX + room[0].xDim; i <= STARTX + room[0].xDim + STARTHALL; i++) //going right
					{
						mvaddch(STARTY+ doorPos, i, HALLWAY); //going right
					}
					break;
				case 'w':
					for(int i = STARTX-1 -STARTHALL; i <= STARTX-1; i++)
					{
						mvaddch(STARTY + doorPos, i, HALLWAY);
					}
					for(int i = STARTY + doorPos; i < STARTY + tall + STARTHALL; i++)
					{
						mvaddch(i, STARTX-1-STARTHALL, HALLWAY); 
					}
					break;
			}
			break;
		case 1:
			switch(location)
			{
				case 'n':
					for(int i = STARTY-1 -STARTHALL; i <= STARTY-1; i++)
					{
						mvaddch(i, STARTX + SPACE + doorPos + room[0].xDim ,HALLWAY);
					}
					break;
				case 's':
					for(int i =  STARTY + room[1].yDim; i <= STARTY + room[1].yDim + STARTHALL; i ++)
					{
						mvaddch(i, STARTX + SPACE + doorPos + room[0].xDim, HALLWAY);
					}
					break;
				case 'e':
					for (int i = STARTX + SPACE + room[0].xDim + room[1].xDim; i <= STARTX + SPACE + room[0].xDim + room[1].xDim + STARTHALL; i++)
					{
						mvaddch(STARTY + doorPos, i, HALLWAY);
					}
					break;
				case 'w':
					for (int i = STARTX-1 + SPACE + room[0].xDim - STARTHALL; i <= STARTX-1 + SPACE + room[0].xDim ; i++)
					{
						mvaddch(STARTY + doorPos, i, HALLWAY);
					}
					break;
			}		
			break;
		case 2:
			switch(location)
			{
				case 'n':
					for(int i = STARTY-1 -STARTHALL ; i <= STARTY-1;i++)
					{
						mvaddch(i,  STARTX + (SPACE * 2) + doorPos + (room[0].xDim + room[1].xDim)  ,HALLWAY);
					}
					break;
				case 's':
					for(int i = STARTY + room[2].yDim ; i <= STARTY + room[2].yDim + STARTHALL; i++)
					{
						mvaddch(i, STARTX + (SPACE * 2) + doorPos + (room[0].xDim + room[1].xDim) , HALLWAY);
					}
					break;
				case 'e':
					for(int i = STARTX + (SPACE * 2) + (room[0].xDim + room[1].xDim + room[2].xDim); i <= STARTX + (SPACE * 2) + (room[0].xDim + room[1].xDim + room[2].xDim) + STARTHALL; i++)
					{
						mvaddch(STARTY + doorPos, i, HALLWAY);
					}
					break;
				case 'w':
					for(int i = (STARTX - 1) + (SPACE * 2) + (room[0].xDim + room[1].xDim) - STARTHALL; i <= (STARTX - 1) + (SPACE * 2) + (room[0].xDim + room[1].xDim); i++)
					{
						mvaddch(STARTY + doorPos, i , HALLWAY);
					}
					break;
			}
			break;
		case 3:
			switch(location)
			{
				case 'n':
					for(int i =(STARTY - 1) + SPACEY + tall - STARTHALL; i <= (STARTY - 1) + SPACEY + tall; i++)
					{
						mvaddch(i, STARTX + doorPos, HALLWAY);
					}
					break;
				case 's':
					for(int i = STARTY + SPACEY + tall + room[3].yDim ; i <= STARTY + SPACEY + tall + room[3].yDim  + STARTHALL; i++)
					{
						mvaddch(i  , STARTX + doorPos , HALLWAY);
					}
					for (int i = STARTX + doorPos; i <= STARTX + room[3].xDim + SPACE-3; i++)
					{
						mvaddch(STARTY+SPACEY+tall + room[3].yDim + STARTHALL, i, HALLWAY); //connecting to hallway between room 3 and 4
					}
					break;
				case 'e':
					for(int i = STARTX + room[3].xDim; i <= STARTX + room[3].xDim + STARTHALL; i++)
					{
						mvaddch(STARTY + SPACEY + doorPos + tall , i , HALLWAY);
					}
					break;
				case 'w':
					for (int i = STARTX-1 -STARTHALL; i <= STARTX -1; i++)
					{
						mvaddch(STARTY + SPACEY + doorPos + tall , i , HALLWAY);
					}
					break;
			}
			break;
		case 4:
			switch(location)
			{
				case 'n':
					for(int i = STARTY-1 -STARTHALL + SPACEY + tall; i <= STARTY-1 + SPACEY + tall; i++)
					{
						mvaddch(i , STARTX + SPACE + doorPos + room[3].xDim , HALLWAY);
					}
					break;
				case 's':
					for (int i = STARTY+SPACEY + room[4].yDim + tall; i <= STARTY + SPACEY + room[4].yDim + tall + STARTHALL-1; i++)
					{
						mvaddch(i , STARTX  + SPACE + doorPos + (room[3].xDim) , HALLWAY);
					}
					for (int i = STARTX + room[3].xDim + SPACE-3; i <= STARTX  + SPACE + doorPos + (room[3].xDim); i++)
					{
						mvaddch(STARTY + SPACEY + room[4].yDim + tall + STARTHALL-1, i, HALLWAY); //connecting to hallway between room 3 and 4
					}
					break;
				case 'e':
					for (int i = STARTX + SPACE + (room[3].xDim  + room[4].xDim); i <= STARTX + SPACE + (room[3].xDim  + room[4].xDim) + STARTHALL; i++)
					{
						mvaddch( STARTY + SPACEY + doorPos + tall , i , HALLWAY);
					}
					break;
				case 'w':
					for (int i = (STARTX - 1) + SPACE +(room[3].xDim) -STARTHALL; i <= (STARTX - 1) + SPACE +(room[3].xDim); i++)
					{
						mvaddch( STARTY + SPACEY + doorPos + tall , i , HALLWAY);
					}
					break;
			}
			break;
		case 5:
			switch(location)
			{
				case 'n':
					for (int i = (STARTY-1 -STARTHALL) + SPACEY + tall; i <= (STARTY - 1) + SPACEY + tall ; i++)
					{
						mvaddch( i , STARTX + (SPACE * 2) + doorPos + (room[4].xDim + room[3].xDim) , HALLWAY);
					}
					break;
				case 's':
					for (int i =  STARTY + SPACEY + tall + room[5].yDim ; i <STARTY + SPACEY + tall + room[5].yDim  + STARTHALL; i++)
					{
						mvaddch(i, STARTX  + (SPACE * 2) + doorPos + (room[4].xDim + room[3].xDim) , HALLWAY);
					}
					for (int i = STARTX  + SPACE + doorPos + (room[3].xDim); i <= STARTX  + (SPACE * 2) + doorPos + (room[4].xDim + room[3].xDim); i++)
					{
						mvaddch(STARTY + SPACEY + tall + room[5].yDim + 1 , i , HALLWAY);
					}
					break;
				case 'e':
					for (int i = STARTX + (SPACE * 2) + (room[3].xDim + room[4].xDim + room[5].xDim) ; i <= STARTX + (SPACE * 2) + (room[3].xDim + room[4].xDim + room[5].xDim)  + STARTHALL; ++i)
					{
						mvaddch( STARTY + SPACEY + doorPos + tall , i, HALLWAY);
					}
					break;
				case 'w':
					for (int i = (STARTX - 1) + (SPACE * 2) + (room[3].xDim + room[4].xDim) - STARTHALL; i <= (STARTX - 1) + (SPACE * 2) + (room[3].xDim + room[4].xDim); i++)
					{
						mvaddch( STARTY + SPACEY + doorPos + tall , i , HALLWAY);
					}
					break;

			}
			break;
	}

}
void placeDoors(Room* room, int tall, int tallest_bot ,char location)
{
	int pos;
	for (int i = 0; i < 6; i++)
    {
		for (int j = 0; j < 4; j++)
        {
			if(room[i].door[j].side == location) //found a door
            {
				pos = room[i].door[j].pos;

				switch(i)//room number
                {
					//putting door based on room
					// basic math knowledge.
					case 0:
					switch(location)
                    {
						case 'n':
							printHallway(room, 0,tall, tallest_bot, pos, 'n');
							mvaddch(STARTY - 1 , STARTX + pos , DOOR);
							break;
						case 's':
							printHallway(room, 0, tall,tallest_bot,pos, 's');
							mvaddch(STARTY + room[0].yDim , STARTX + pos , DOOR);
							break;
						case 'e':
							printHallway(room, 0, tall,tallest_bot,pos, 'e');
							mvaddch(STARTY + pos , STARTX + room[0].xDim , DOOR);
							break;
						case 'w':
							printHallway(room, 0, tall, tallest_bot, pos, 'w');
							mvaddch(STARTY + pos , STARTX-1 , DOOR);
							break;
					}
					break;

					case 1:
					switch(location)
                    {
						case 'n':
							printHallway(room,1,tall, tallest_bot, pos,'n');
							mvaddch(STARTY - 1 , STARTX + SPACE + pos + room[0].xDim , DOOR);
							break;
						case 's':
							printHallway(room,1,tall, tallest_bot, pos,'s');
							mvaddch(STARTY + room[1].yDim , STARTX + SPACE + pos + room[0].xDim , DOOR);
							break;
						case 'e':
							printHallway(room,1,tall, tallest_bot,  pos,'e');
							mvaddch(STARTY + pos , STARTX + SPACE + (room[0].xDim + room[1].xDim) , DOOR);
							break;
						case 'w':
							printHallway(room,1,tall,tallest_bot, pos,'w');
							mvaddch(STARTY + pos , (STARTX - 1) + SPACE + room[0].xDim , DOOR);
							break;
					}
					break;

					case 2:
					switch(location)
                    {
						case 'n':
							printHallway(room,2,tall,tallest_bot,pos,'n');
							mvaddch(STARTY - 1 , STARTX + (SPACE * 2) + pos + (room[0].xDim + room[1].xDim) , DOOR);
							break;
						case 's':
							printHallway(room,2,tall,tallest_bot,pos,'s');						
							mvaddch(STARTY + room[2].yDim , STARTX + (SPACE * 2) + pos + (room[0].xDim + room[1].xDim) , DOOR);
							break;
						case 'e':
							printHallway(room,2,tall,tallest_bot,pos,'e');
							mvaddch(STARTY + pos , STARTX + (SPACE * 2) + (room[0].xDim + room[1].xDim + room[2].xDim) , DOOR);
							break;
						case 'w':
							printHallway(room,2,tall,tallest_bot,pos,'w');
							mvaddch(STARTY + pos , (STARTX - 1) + (SPACE * 2) + (room[0].xDim + room[1].xDim) , DOOR);
							break;

					}
					break;

					case 3:
					switch(location)
                    {
						case 'n':
							printHallway(room,3,tall,tallest_bot,pos,'n');
							mvaddch( (STARTY - 1) + SPACEY + tall , STARTX + pos , DOOR);
							break;
						case 's':
							printHallway(room,3,tall,tallest_bot,pos,'s');
							mvaddch(STARTY + SPACEY + tall + room[3].yDim  , STARTX + pos , DOOR);
							break;
						case 'e':
							printHallway(room,3,tall,tallest_bot,pos,'e');
							mvaddch(STARTY + SPACEY + pos + tall , STARTX + room[3].xDim , DOOR);
							break;
						case 'w':
							printHallway(room,3,tall,tallest_bot,pos,'w');
							mvaddch(STARTY + SPACEY + pos + tall , STARTX - 1 , DOOR);
							break;
					}
					break;

					case 4:
					switch(location)
                    {
						case 'n':
							printHallway(room,4,tall,tallest_bot,pos,'n');
							mvaddch( (STARTY - 1) + SPACEY + tall , STARTX + SPACE + pos + room[3].xDim , DOOR);
							break;
						case 's':
							printHallway(room,4,tall,tallest_bot,pos,'s');
							mvaddch(STARTY + SPACEY + room[4].yDim+tall , STARTX  + SPACE + pos + (room[3].xDim) , DOOR);
							break;
						case 'e':
							printHallway(room,4,tall,tallest_bot,pos,'e');
							mvaddch( STARTY + SPACEY + pos + tall , STARTX + SPACE + (room[3].xDim  + room[4].xDim) , DOOR);
							break;
						case 'w':
							printHallway(room,4,tall,tallest_bot,pos,'w');
							mvaddch( STARTY + SPACEY + pos + tall , (STARTX - 1) + SPACE +(room[3].xDim) , DOOR);
							break;

					}
					break;

					case 5:
					switch(location)
                    {
						case 'n':
						printHallway(room,5,tall,tallest_bot,pos,'n');
						mvaddch( (STARTY - 1) + SPACEY + tall , STARTX + (SPACE * 2) + pos + (room[4].xDim + room[3].xDim) , DOOR);
						break;
						case 's':
						printHallway(room,5,tall,tallest_bot,pos,'s');
						mvaddch( STARTY + SPACEY + tall + room[5].yDim , STARTX  + (SPACE * 2) + pos + (room[4].xDim + room[3].xDim) , DOOR);
						break;
						case 'e':
						printHallway(room,5,tall,tallest_bot,pos,'e');
						mvaddch( STARTY + SPACEY + pos + tall , STARTX + (SPACE * 2) + (room[3].xDim + room[4].xDim + room[5].xDim) , DOOR);
						break;
						case 'w':
						printHallway(room,5,tall,tallest_bot,pos,'w');
						mvaddch( STARTY + SPACEY + pos + tall , (STARTX - 1) + (SPACE * 2) + (room[3].xDim + room[4].xDim) , DOOR);
						break;
					}
					break;
				}
			}
			else
			{
				//do nothing
			}
		}
	}
}

void placeItem(Room* room,int tall, char type)
{
	int itemPosX;
	int itemPosY;

	for (int i = 0; i < 6; i++)
    {
		for (int j = 0; j < 10; j++)
        {
			if(room[i].elements[j].type == type)
            {
				itemPosY = room[i].elements[j].posY;
				itemPosX = room[i].elements[j].posX;
				switch(i)
                {
					case 0:
						if(type == '@') //for hero
                        {
							mvaddch(STARTY + itemPosY , STARTX + itemPosX , HERO); //adds hero
							move(STARTY + itemPosY , STARTX + itemPosX); //cursor
							break;
						}
						//for regular item found
						mvaddch(STARTY + itemPosY , STARTX + itemPosX , type);
						break;
					case 1:
						if(type == '@')
                        {
							mvaddch(STARTY + itemPosY , STARTX + SPACE + itemPosX + (room[0].xDim) , HERO);
							move(STARTY + itemPosY , STARTX + SPACE + itemPosX + (room[0].xDim));
							break;
						}
						mvaddch(STARTY + itemPosY , STARTX + SPACE + itemPosX + (room[0].xDim) , type);
						break;
					case 2:
						if(type == '@')
                        {
							mvaddch(STARTY + itemPosY , STARTX + (SPACE * 2) + itemPosX + (room[0].xDim + room[1].xDim) , HERO);
							move(STARTY + itemPosY , STARTX + (SPACE * 2) + itemPosX + (room[0].xDim + room[1].xDim));
							break;
						}
						mvaddch(STARTY + itemPosY , STARTX + (SPACE * 2) + itemPosX + (room[0].xDim+ room[1].xDim) , type);
						break;
					case 3:
						if(type == '@')
                        {
							mvaddch(STARTY + SPACEY + tall + itemPosY , STARTX + itemPosX , HERO);
							move(STARTY + SPACEY +  tall + itemPosY , STARTX + itemPosX);
							break;
						}
						mvaddch(STARTY + SPACEY + tall + itemPosY , STARTX + itemPosX , type);
						break;
					case 4:
						if(type == '@')
                        {
							mvaddch(STARTY + SPACEY + tall + itemPosY , STARTX + SPACE + itemPosX + (room[3].xDim) , HERO);
							move(STARTY + SPACEY + tall + itemPosY , STARTX + SPACE + itemPosX + (room[3].xDim));
							break;
						}
						mvaddch(STARTY + SPACEY + tall + itemPosY , STARTX + SPACE + itemPosX + (room[3].xDim) , type);
						break;
					case 5:
						if(type == '@')
                        {
							mvaddch(STARTY + SPACEY + tall + itemPosY , STARTX + (SPACE * 2) + itemPosX + (room[3].xDim + room[4].xDim) , HERO);
							move(STARTY + SPACEY + tall + itemPosY , STARTX + (SPACE * 2) + itemPosX + (room[3].xDim + room[4].xDim));
							break;
						}
						mvaddch(STARTY + SPACEY + tall + itemPosY , STARTX + (SPACE * 2) + itemPosX + (room[3].xDim + room[4].xDim) , type);
						break;
				}
			}
			else
			{
				//do nothing
			}
		}
	}
}

