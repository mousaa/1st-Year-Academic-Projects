/**
 * see userInterface.h for complete function definitions
 *
 */
#include "userInterface.h"

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

void placeDoors(Room* room, int tall, char location)
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
							mvaddch(STARTY - 1 , STARTX + pos , DOOR);
							break;
						case 's':
							mvaddch(STARTY + room[0].yDim , STARTX + pos , DOOR);
							break;
						case 'e':
							mvaddch(STARTY + pos , STARTX + room[0].xDim , DOOR);
							break;
						case 'w':
							mvaddch(STARTY + pos , STARTX-1 , DOOR);
							break;
					}
					break;

					case 1:
					switch(location)
                    {
						case 'n':
							mvaddch(STARTY - 1 , STARTX + SPACE + pos + room[0].xDim , DOOR);
							break;
						case 's':
							mvaddch(STARTY + room[1].yDim , STARTX + SPACE + pos + room[0].xDim , DOOR);
							break;
						case 'e':
							mvaddch(STARTY + pos , STARTX + SPACE + (room[0].xDim + room[1].xDim) , DOOR);
							break;
						case 'w':
							mvaddch(STARTY + pos , (STARTX - 1) + SPACE + room[0].xDim , DOOR);
							break;
					}
					break;

					case 2:
					switch(location)
                    {
						case 'n':
							mvaddch(STARTY - 1 , STARTX + (SPACE * 2) + pos + (room[0].xDim + room[1].xDim) , DOOR);
							break;
						case 's':
							mvaddch(STARTY + room[2].yDim , STARTX + (SPACE * 2) + pos + (room[0].xDim + room[1].xDim) , DOOR);
							break;
						case 'e':
							mvaddch(STARTY + pos , STARTX + (SPACE * 2) + (room[0].xDim + room[1].xDim + room[2].xDim) , DOOR);
							break;
						case 'w':
							mvaddch(STARTY + pos , (STARTX - 1) + (SPACE * 2) + (room[0].xDim + room[1].xDim) , DOOR);
							break;

					}
					break;

					case 3:
					switch(location)
                    {
						case 'n':
							mvaddch( (STARTY - 1) + tall , STARTX + pos , DOOR);
							break;
						case 's':
							mvaddch(STARTY + tall + room[3].yDim , STARTX + pos , DOOR);
							break;
						case 'e':
							mvaddch(STARTY + pos + tall , STARTX + room[3].xDim , DOOR);
							break;
						case 'w':
							mvaddch(STARTY + pos + tall , STARTX - 1 , DOOR);
							break;
					}
					break;

					case 4:
					switch(location)
                    {
						case 'n':
							mvaddch( (STARTY - 1) + tall , STARTX + SPACE + pos + room[3].xDim , DOOR);
							break;
						case 's':
							mvaddch( STARTY + room[4].yDim+tall , STARTX  + SPACE + pos + (room[3].xDim) , DOOR);
							break;
						case 'e':
							mvaddch( STARTY + pos + tall , STARTX + SPACE + (room[3].xDim  + room[4].xDim) , DOOR);
							break;
						case 'w':
							mvaddch( STARTY + pos + tall , (STARTX - 1) + SPACE +(room[3].xDim) , DOOR);
							break;
					}
					break;

					case 5:
					switch(location)
                    {
						case 'n':
						mvaddch( (STARTY - 1) + tall , STARTX + (SPACE * 2) + pos + (room[4].xDim + room[3].xDim) , DOOR);
						break;
						case 's':
						mvaddch( STARTY + tall + room[5].yDim , STARTX  + (SPACE * 2) + pos + (room[4].xDim + room[3].xDim) , DOOR);
						break;
						case 'e':
						mvaddch( STARTY + pos + tall , STARTX + (SPACE * 2) + (room[3].xDim + room[4].xDim + room[5].xDim) , DOOR);
						break;
						case 'w':
						mvaddch( STARTY + pos + tall , (STARTX - 1) + (SPACE * 2) + (room[3].xDim + room[4].xDim) , DOOR);
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
							mvaddch(STARTY + tall + itemPosY , STARTX + itemPosX , HERO);
							move(STARTY +  tall + itemPosY , STARTX + itemPosX);
							break;
						}
						mvaddch(STARTY + tall + itemPosY , STARTX + itemPosX , type);
						break;
					case 4:
						if(type == '@')
                        {
							mvaddch(STARTY + tall + itemPosY , STARTX + SPACE + itemPosX + (room[3].xDim) , HERO);
							move(STARTY + tall + itemPosY , STARTX + SPACE + itemPosX + (room[3].xDim));
							break;
						}
						mvaddch(STARTY + tall + itemPosY , STARTX + SPACE + itemPosX + (room[3].xDim) , type);
						break;
					case 5:
						if(type == '@')
                        {
							mvaddch(STARTY + tall + itemPosY , STARTX + (SPACE * 2) + itemPosX + (room[3].xDim + room[4].xDim) , HERO);
							move(STARTY + tall + itemPosY , STARTX + (SPACE * 2) + itemPosX + (room[3].xDim + room[4].xDim));
							break;
						}
						mvaddch(STARTY + tall + itemPosY , STARTX + (SPACE * 2) + itemPosX + (room[3].xDim + room[4].xDim) , type);
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
