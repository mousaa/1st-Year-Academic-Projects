#include "curses.h"
#include "userInterface.h"
#include "checkWindow.h"
#include "playerMove.h"
#include "endMsg.h"
#include "enemyMove.h"
#include "combat.h"

void moveEnemy(Room* room)
{
	int posX;
	int posY;
	char enemy;
	for (int i = 0; i < 6; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			if((room[i].elements[j].type == 'S') || (room[i].elements[j].type == 'B') || (room[i].elements[j].type == 'Z') || (room[i].elements[j].type == 'T'))
			{
				enemy = room[i].elements[j].type;
				posY = room[i].elements[j].posY;
				posX = room[i].elements[j].posX;

				switch(i)
				{
					case 0:
						switch(enemy)
						{
							case 'S':
								if(room[0].snake[0].cycle!=0)
									snakeCycle(room, i, j, posY, posX);
								break;
							case 'B':
								if(room[0].bat[0].cycle!= 0)
									batCycle(room, i, j, posY, posX);
								break;
							case 'Z':
								if(room[0].zombie[0].cycle != 0)
									zombieCycle(room, i, j, posY, posX);
								break;
						}	
						break;
					case 1:
						switch(enemy)
						{
							case 'S':
								snakeCycle(room, i, j, posY, posX);
								break;
							case 'B':
								batCycle(room, i, j, posY, posX);
								break;
							case 'Z':
								zombieCycle(room, i, j, posY, posX);
								break;
							case 'T':
								if(room[0].trollCycle  != 0)
									trollCycle(room, i, j, posY, posX);
								break;
						}
						break;
					case 2:
						switch(enemy)
						{
							case 'S':
								if(room[2].snake[1].cycle!= 0)
								snakeCycle(room, i, j ,posY, posX);
								break;
							case 'B':
								if(room[2].bat[1].cycle!= 0)
									batCycle(room, i, j,posY, posX);
								break;
							case 'Z':
								if(room[2].zombie[1].cycle != 0)
									zombieCycle(room, i, j, posY, posX);
								break;
						}
						break;
					case 4:
						switch(enemy)
						{
							case 'S':
							if((room[4].snake[2].cycle != 0) && (room[4].snake[3].cycle != 0))
								snakeCycle(room, i, j, posY, posX);
								break;
							case 'B':
								if((room[4].bat[2].cycle!= 0) && (room[4].bat[3].cycle!=0))
									batCycle(room, i, j,  posY, posX);
								break;
							case 'Z':
								if((room[4].zombie[2].cycle != 0) && (room[4].zombie[3].cycle != 0))
									zombieCycle(room, i, j, posY, posX );
								break;
						}
						break;
					case 5:
						switch(enemy)
						{
							case 'S':
							if((room[5].snake[4].cycle != 0) && (room[5].snake[5].cycle != 0))
								snakeCycle(room, i, j, posY, posX);
								break;
							case 'B':
							if((room[5].bat[4].cycle != 0) && (room[5].bat[5].cycle != 0))
								batCycle(room, i, j, posY, posX);
								break;
							case 'Z':
								if((room[5].zombie[4].cycle != 0) && (room[5].zombie[5].cycle != 0))
									zombieCycle(room, i, j, posY, posX );
								break;
						}
						break;
				}
			}
		}	
	}
}
int collision(int y, int x)
{
	int ret;
	char next;
	next = (char)mvinch(y,x);
	switch(next)
	{
		case '@':
		case '|':
		case '+':
			ret = 1;
			break;
		default:
			ret = 0;
			break;
	}
	return ret;
}
void snakeCycle(Room* room, int i, int j, int posY, int posX)
{
	int tall;	
	tall = findTallest(room);
	int ctr;

	room[i].elements[j].cycleCtr++;
	ctr = room[i].elements[j].cycleCtr;
	switch(i)
	{
		case 0:
			switch(ctr)
			{
				case 1:
					mvaddch(STARTY + posY , STARTX + posX , '.');
					if(collision(STARTY + posY , STARTX + posX + 1))
					{
						mvaddch(STARTY + posY , STARTX + posX , 'S');
					}
					mvaddch(STARTY + posY , STARTX + posX + 1, 'S');
					break;
				case 2:
					mvaddch(STARTY + posY , STARTX + posX + 1, '.');
					if(collision(STARTY + posY , STARTX + posX + 2))
					{
						mvaddch(STARTY + posY , STARTX + posX + 1, 'S');	
					}
					mvaddch(STARTY + posY , STARTX + posX + 2, 'S');
					break;
				case 3:
					mvaddch(STARTY + posY , STARTX + posX + 2, '.');
					if(collision(STARTY + posY , STARTX + posX + 1))
					{
						mvaddch(STARTY + posY , STARTX + posX + 2, 'S');
					}
					mvaddch(STARTY + posY , STARTX + posX + 1, 'S');
					break;
				case 4:
					mvaddch(STARTY + posY , STARTX + posX + 1, '.');
					if(collision(STARTY + posY , STARTX + posX))
					{
						mvaddch(STARTY + posY , STARTX + posX + 1, 'S');
					}
					else
					{
						mvaddch(STARTY + posY , STARTX + posX , 'S');
						room[i].elements[j].cycleCtr = 0;
					}
					break;
			}
			break;
		case 1:
			switch(ctr)
			{
				case 1:
					mvaddch(STARTY + posY , STARTX + SPACE + posX + (room[0].xDim), '.');
					mvaddch(STARTY + posY , STARTX + SPACE + posX + (room[0].xDim)+ 1, 'S');
					break;
				case 2:
					mvaddch(STARTY + posY , STARTX + SPACE + posX + (room[0].xDim) + 1, '.');
					mvaddch(STARTY + posY , STARTX + SPACE + posX + (room[0].xDim) + 2, 'S');
					break;
				case 3:
					mvaddch(STARTY + posY , STARTX + SPACE + posX + (room[0].xDim) + 2, '.');
					mvaddch(STARTY + posY , STARTX + SPACE + posX + (room[0].xDim) + 1, 'S');
					break;
				case 4:
					mvaddch(STARTY + posY , STARTX + SPACE + posX + (room[0].xDim) + 1, '.');
					mvaddch(STARTY + posY , STARTX + SPACE + posX + (room[0].xDim), 'S');
					room[i].elements[j].cycleCtr = 0;
					break;
			}
			break;
		case 2:
			switch(ctr)
			{
				case 1:
					mvaddch(STARTY + posY , STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) , '.');
					mvaddch(STARTY + posY , STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) + 1 , 'S');
					break;
				case 2:
					mvaddch(STARTY + posY , STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) + 1 , '.');
					mvaddch(STARTY + posY , STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) + 2 , 'S');
					break;
				case 3:
					mvaddch(STARTY + posY , STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) + 2, '.');
					mvaddch(STARTY + posY , STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) + 1, 'S');
					break;
				case 4:
					mvaddch(STARTY + posY , STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) + 1, '.');
					mvaddch(STARTY + posY , STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) , 'S');
					room[i].elements[j].cycleCtr = 0;
					break;
			}
			break;
		case 3:
			switch(ctr)
			{
				case 1:
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + posX , '.');
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + posX + 1, 'S');
					break;
				case 2:
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + posX + 1 , '.');
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + posX + 2, 'S');
					break;
				case 3:
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + posX + 2, '.');
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + posX + 1, 'S');
					break;
				case 4:
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + posX + 1, '.');
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + posX , 'S');
					room[i].elements[j].cycleCtr = 0;
					break;
			}
			break;
		case 4:
			switch(ctr)
			{
				case 1:
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + SPACE + posX + (room[3].xDim) , '.');
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + SPACE + posX + (room[3].xDim) + 1 , 'S');
					break;
				case 2:
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + SPACE + posX + (room[3].xDim)+ 1, '.');
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + SPACE + posX + (room[3].xDim) + 2, 'S');
					break;
				case 3:
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + SPACE + posX + (room[3].xDim) +2 , '.');
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + SPACE + posX + (room[3].xDim) + 1, 'S');
					break;
				case 4:
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + SPACE + posX + (room[3].xDim) + 1, '.');
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + SPACE + posX + (room[3].xDim) , 'S');
					room[i].elements[j].cycleCtr = 0;
					break;
			}
			break;
		case 5:
			switch(ctr)
			{
				case 1:
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) , '.');
					if(collision(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + 1))
					{
						mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) , 'S');
					}
					else
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + 1 , 'S');
					break;
				case 2:
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + 1, '.');
					if(collision(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + 2))
					{
						mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + 1, 'S');
					}
					else
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + 2, 'S');
					break;
				case 3:
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + 2, '.');
					if(collision(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + 1))
					{
						mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + 2, 'S');	
					}
					else
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + 1, 'S');
					break;
				case 4:
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + 1, '.');
					if(collision(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim)))
					{
						mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + 1, '.');
					}
					else
					{
						mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) , 'S');
						room[i].elements[j].cycleCtr = 0;
					}
					break;
			}
			break;
	}
}
void batCycle(Room* room,int  i, int j, int posY, int posX)
{
	int tall;

	tall = findTallest(room);
	int direction;

	room[i].elements[j].cycleCtr++;

	direction = rand() % 21;
	switch(i)
	{
		case 0:
			if(direction >= 10)
			{
					mvaddch(STARTY + posY , STARTX + posX + room[i].elements[j].batCtr , '.');
					room[i].elements[j].batCtr++;
					if(collision(STARTY + posY , STARTX + posX + room[i].elements[j].batCtr))
					{
						room[i].elements[j].batCtr--;
						mvaddch(STARTY + posY , STARTX + posX + room[i].elements[j].batCtr , 'B');
						room[i].elements[j].cycleCtr = 0;
					}
					else
					{
						mvaddch(STARTY + posY , STARTX + posX + room[i].elements[j].batCtr , 'B');
						room[i].elements[j].cycleCtr = 0;
					}
			}
			else
			{	
				mvaddch(STARTY + posY , STARTX + posX + room[i].elements[j].batCtr , '.');
				room[i].elements[j].batCtr--;
				if(collision(STARTY + posY , STARTX + posX + room[i].elements[j].batCtr))
				{
					room[i].elements[j].batCtr++;
					mvaddch(STARTY + posY , STARTX + posX + room[i].elements[j].batCtr, 'B');
					room[i].elements[j].cycleCtr = 0;
				}
				else
				{
					mvaddch(STARTY + posY , STARTX + posX + room[i].elements[j].batCtr, 'B');
					room[i].elements[j].cycleCtr = 0;	
				}
			}
			break;
		case 1:
			if(direction >= 10)
			{
				mvaddch(STARTY + posY , STARTX + SPACE + posX + (room[0].xDim) + room[i].elements[j].batCtr  , '.');
				room[i].elements[j].batCtr++;
				if(collision(STARTY + posY , STARTX + posX + (room[0].xDim) + room[i].elements[j].batCtr))
				{
					room[i].elements[j].batCtr--;
					mvaddch(STARTY + posY , STARTX + posX + (room[0].xDim) + room[i].elements[j].batCtr , 'B');
					room[i].elements[j].cycleCtr = 0;
				}
				else
				{
					mvaddch(STARTY + posY , STARTX + SPACE + posX + (room[0].xDim) + room[i].elements[j].batCtr  , 'B');
					room[i].elements[j].cycleCtr = 0;
				}	
			}
			else
			{	
				mvaddch(STARTY + posY , STARTX + SPACE + posX + (room[0].xDim) + room[i].elements[j].batCtr  , '.');
				room[i].elements[j].batCtr--;
				if(collision(STARTY + posY , STARTX + SPACE + posX + (room[0].xDim) + room[i].elements[j].batCtr))
				{
					room[i].elements[j].batCtr++;
					mvaddch(STARTY + posY , STARTX + SPACE + posX + (room[0].xDim) + room[i].elements[j].batCtr, 'B');
				}
				else
				{
					mvaddch(STARTY + posY , STARTX + SPACE + posX + (room[0].xDim) + room[i].elements[j].batCtr  , 'B');
					room[i].elements[j].cycleCtr = 0;
				}	
			}
			break;
		case 2:
			if(direction >= 10)
			{
				mvaddch(STARTY + posY , STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) + room[i].elements[j].batCtr, '.');
				room[i].elements[j].batCtr++;
				if(collision(STARTY + posY , STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) + room[i].elements[j].batCtr))
				{
					room[i].elements[j].batCtr--;
					mvaddch(STARTY + posY , STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) + room[i].elements[j].batCtr, 'B');
					room[i].elements[j].cycleCtr = 0;
				}
				else
				{
					mvaddch(STARTY + posY , STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) + room[i].elements[j].batCtr, 'B');	
					room[i].elements[j].cycleCtr = 0;
				}
			}
			else
			{
				mvaddch(STARTY + posY , STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) + room[i].elements[j].batCtr, '.');
				room[i].elements[j].batCtr--;
				if(collision(STARTY + posY , STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) + room[i].elements[j].batCtr))
				{
					room[i].elements[j].batCtr++;
					mvaddch(STARTY + posY , STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) + room[i].elements[j].batCtr, 'B');
					room[i].elements[j].cycleCtr = 0;
				}
				else
				{
					mvaddch(STARTY + posY , STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) + room[i].elements[j].batCtr, 'B');
					room[i].elements[j].cycleCtr = 0;
				}
			}
			break;
		case 3:
			if(direction >= 10)
			{
				mvaddch(STARTY + SPACEY + tall + posY , STARTX + posX + room[i].elements[j].batCtr, '.');
				room[i].elements[j].batCtr++;
				if(collision(STARTY + SPACEY + tall + posY , STARTX + posX + room[i].elements[j].batCtr))
				{
					room[i].elements[j].batCtr--;
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + posX + room[i].elements[j].batCtr, 'B');
					room[i].elements[j].cycleCtr = 0;
				}
				else
				{
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + posX + room[i].elements[j].batCtr, 'B');
					room[i].elements[j].cycleCtr = 0;
				}
			}
			else
			{
				mvaddch(STARTY + SPACEY + tall + posY , STARTX + posX+ room[i].elements[j].batCtr , '.');
				room[i].elements[j].batCtr--;
				if(collision(STARTY + SPACEY + tall + posY , STARTX + posX+ room[i].elements[j].batCtr))
				{
					room[i].elements[j].batCtr++;
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + posX+ room[i].elements[j].batCtr , 'B');
					room[i].elements[j].cycleCtr = 0;
				}
				else
				{
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + posX+ room[i].elements[j].batCtr , 'B');
					room[i].elements[j].cycleCtr = 0;
				}
			}
			break;
		case 4:
			if(direction >= 10)
			{
				mvaddch(STARTY + SPACEY + tall + posY , STARTX + SPACE + posX + (room[3].xDim) + room[i].elements[j].batCtr , '.');
				room[i].elements[j].batCtr++;
				if(collision(STARTY + SPACEY + tall + posY , STARTX + SPACE + posX + (room[3].xDim) + room[i].elements[j].batCtr))
				{
					room[i].elements[j].batCtr--;
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + SPACE + posX + (room[3].xDim) + room[i].elements[j].batCtr , 'B');
					room[i].elements[j].cycleCtr = 0;
				}
				else
				{
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + SPACE + posX + (room[3].xDim) + room[i].elements[j].batCtr , 'B');
					room[i].elements[j].cycleCtr = 0;
				}

			}
			else
			{
				mvaddch(STARTY + SPACEY + tall + posY , STARTX + SPACE + posX + (room[3].xDim) + room[i].elements[j].batCtr, '.');
				room[i].elements[j].batCtr--;
				if(collision(STARTY + SPACEY + tall + posY , STARTX + SPACE + posX + (room[3].xDim) + room[i].elements[j].batCtr))
				{
					room[i].elements[j].batCtr++;
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + SPACE + posX + (room[3].xDim) + room[i].elements[j].batCtr, 'B');
					room[i].elements[j].cycleCtr = 0;
				}
				else
				{
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + SPACE + posX + (room[3].xDim) + room[i].elements[j].batCtr, 'B');
					room[i].elements[j].cycleCtr = 0;
				}
			}
			break;
		case 5:
			if(direction >= 10)
			{
				mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + room[i].elements[j].batCtr , '.');
				room[i].elements[j].batCtr++;
				if(collision(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + room[i].elements[j].batCtr))
				{
					room[i].elements[j].batCtr--;
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + room[i].elements[j].batCtr, 'B');
					room[i].elements[j].cycleCtr = 0;
				}
				else
				{
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + room[i].elements[j].batCtr, 'B');
					room[i].elements[j].cycleCtr = 0;
				}
			}
			else
			{
				mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + room[i].elements[j].batCtr  , '.');
				room[i].elements[j].batCtr--;
				if(collision(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + room[i].elements[j].batCtr))
				{
					room[i].elements[j].batCtr++;
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + room[i].elements[j].batCtr , 'B');
					room[i].elements[j].cycleCtr = 0;
				}
				else
				{
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) + room[i].elements[j].batCtr , 'B');
					room[i].elements[j].cycleCtr = 0;
				}
			}
			break;
	}
}

void zombieCycle(Room* room, int i, int j, int posY, int posX)
{
	int tall;

	tall = findTallest(room);
	int ctr;

	room[i].elements[j].cycleCtr++;
	ctr = room[i].elements[j].cycleCtr;
	switch(i)
	{
		case 0:
			switch(ctr)
			{
				case 1:
					mvaddch(STARTY + posY , STARTX + posX , '.');
					mvaddch(STARTY + posY + 1, STARTX + posX , 'Z');
					break;
				case 2:
					mvaddch(STARTY + posY + 1, STARTX + posX , '.');
					mvaddch(STARTY + posY , STARTX + posX , 'Z');
					room[i].elements[j].cycleCtr = 0;
					break;
			}
			break;
		case 1:
			switch(ctr)
			{
				case 1:
					mvaddch(STARTY + posY , STARTX + SPACE + posX + (room[0].xDim) , '.');
					mvaddch(STARTY + posY + 1 , STARTX + SPACE + posX + (room[0].xDim) , 'Z');
					break;
				case 2:
					mvaddch(STARTY + posY + 1, STARTX + SPACE + posX + (room[0].xDim) , '.');
					mvaddch(STARTY + posY , STARTX + SPACE + posX + (room[0].xDim) , 'Z');
					room[i].elements[j].cycleCtr = 0;
					break;
			}
			break;
		case 2:
			switch(ctr)
			{
				case 1:
					mvaddch(STARTY + posY , STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) , '.');
					mvaddch(STARTY + posY + 1, STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) , 'Z');
					break;
				case 2:
					mvaddch(STARTY + posY + 1, STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) , '.');
					mvaddch(STARTY + posY , STARTX + (SPACE * 2) + posX + (room[0].xDim+ room[1].xDim) , 'Z');
					room[i].elements[j].cycleCtr = 0;
					break;
			}
			break;
		case 3:
			switch(ctr)
			{
				case 1:
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + posX , '.');
					mvaddch(STARTY + SPACEY + tall + posY + 1 , STARTX + posX , 'Z');
					break;
				case 2:
					mvaddch(STARTY + SPACEY + tall + posY + 1, STARTX + posX , '.');
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + posX , 'Z');
					room[i].elements[j].cycleCtr = 0;
					break;
			}
			break;
		case 4:
			switch(ctr)
			{
				case 1:
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + SPACE + posX + (room[3].xDim) , '.');
					mvaddch(STARTY + SPACEY + tall + posY + 1 , STARTX + SPACE + posX + (room[3].xDim) , 'Z');
					break;
				case 2:
					mvaddch(STARTY + SPACEY + tall + posY + 1 , STARTX + SPACE + posX + (room[3].xDim) , '.');
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + SPACE + posX + (room[3].xDim) , 'Z');
					room[i].elements[j].cycleCtr = 0;
					break;
			}
			break;
		case 5:
			switch(ctr)
			{
				case 1:
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) , '.');
					mvaddch(STARTY + SPACEY + tall + posY + 1, STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) , 'Z');
					break;
				case 2:
					mvaddch(STARTY + SPACEY + tall + posY + 1, STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) , '.');
					mvaddch(STARTY + SPACEY + tall + posY , STARTX + (SPACE * 2) + posX + (room[3].xDim + room[4].xDim) , 'Z');
					room[i].elements[j].cycleCtr = 0;
					break;
			}
			break;
	}
}

void trollCycle(Room* room, int i, int j, int posY, int posX)
{
	int ctr;

	room[i].elements[j].cycleCtr++;
	ctr = room[i].elements[j].cycleCtr;
	switch(i)
	{
		case 1:
			switch(ctr)
			{
				case 1:
					mvaddch(STARTY + posY , STARTX + SPACE + posX + (room[0].xDim) , '.');
					mvaddch(STARTY + posY -1  , STARTX + SPACE + posX + (room[0].xDim) , 'T');
					break;
				case 2:
					mvaddch(STARTY + posY -1  , STARTX + SPACE + posX + (room[0].xDim) , '.');
					mvaddch(STARTY + posY -1  , STARTX + SPACE + posX + (room[0].xDim) + 1, 'T');
					break;
				case 3:
					mvaddch(STARTY + posY -1  , STARTX + SPACE + posX + (room[0].xDim) + 1, '.');
					mvaddch(STARTY + posY   , STARTX + SPACE + posX + (room[0].xDim) + 1, 'T');
					break;
				case 4:
					mvaddch(STARTY + posY   , STARTX + SPACE + posX + (room[0].xDim) + 1, '.');
					mvaddch(STARTY + posY   , STARTX + SPACE + posX + (room[0].xDim) , 'T');
					room[i].elements[j].cycleCtr = 0;
					break;
			}
			break;
	}
}
