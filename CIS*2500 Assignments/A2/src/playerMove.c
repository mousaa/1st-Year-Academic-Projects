/**
 * see playerMove.h for complete function definitions
 *
 */
#include "checkWindow.h"  //for findTallest
#include "playerMove.h" //for everything else.

void moveHero(Room* room, char key)
{
	int y;
	int x;
	int oldx;
	int oldy;
	int new;
	int bigGold;
	int smallGold;

	getyx(stdscr, y, x); //cursor location

	//holds old position in event hero cant step/move to a certain location
	oldx = x;
	oldy = y;

	//sum of all rooms' gold
	smallGold = room[0].smallGold + room[1].smallGold + room[2].smallGold + room[3].smallGold + room[4].smallGold + room[5].smallGold;
	bigGold = room[0].bigGold + room[1].bigGold + room[2].bigGold + room[3].bigGold + room[4].bigGold + room[5].bigGold;

	switch(key) //user input for movement
    {
		case 'w': //up
			y--;
			break;
		case 'a': //right
			x--;
			break;
		case 's': //down
			y++;
			break;
		case 'd'://left
			x++;
			break;
		default: //dont do anything.
			break;
	}

	new = nextPos(y,x); //position that hero's about to move to
	switch(new)
    {
		case 0://cant walk on.
			move(oldy,oldx);
			break;
		case 1://collectable || regular movement
			mvaddch(y,x,HERO); //moves hero to the location
			mvaddch(oldy,oldx, '.'); //to avoid echoing of hero
			move(y,x); //moves cursor to hero's position
			break;
		case 2: //stairs
			endGame(room); //ends game, prints gold amount,frees room
			exit(1);
			break;
		case 3: //hit a door
			move(oldy,oldx);//dont step on it

			switch(currentRoom(room))
            {
				case 0:
					mvaddch(oldy,oldx, '.'); //deletes the hero in old room before teleport
					gotoDoor(room,1); //teleport to next room
					break;
				case 1:
					mvaddch(oldy,oldx, '.');
					gotoDoor(room,2);
					break;
				case 2:
					mvaddch(oldy,oldx, '.');
					gotoDoor(room,3);
					break;
				case 3:
					mvaddch(oldy,oldx, '.');
					gotoDoor(room,4);
					break;
				case 4:
					mvaddch(oldy,oldx, '.');
					gotoDoor(room,5);
					break;
				case 5:
					mvaddch(oldy,oldx, '.');
					gotoDoor(room,0);
					break;
			}
			break;
		case 4: //small gold
			mvaddch(y,x,HERO);
			mvaddch(oldy,oldx, '.');
			move(y,x);
			smallGold = (rand() % 51); //random between 0 and 50
			room[currentRoom(room)].smallGold += smallGold;
			break;

		case 5://big gold
			mvaddch(y,x,HERO);
			mvaddch(oldy,oldx, '.');
			move(y,x);
			bigGold = (rand() % 200) + 50; //random between 50 and 250
			room[currentRoom(room)].bigGold = bigGold;
			break;
	}
}

int nextPos(int y, int x)
{
	int retVal;
	char new;
	new = (char)mvinch(y,x); //checks what char is in the next position

	switch(new)
    {
		//cant step on
		case ' ': //so hero cant walk outside room
		case '|':
		case '-':
		case 'A':
		case 'S':
		case 'Z':
		case 'B':
		case 'T':
			retVal = 0;
			break;

		//stairs
		case '>':
		case '<':
			retVal = 2;
			break;

		case DOOR:
			retVal = 3;
			break;

		case '*': //small gold
			retVal = 4;
			break;

		case '8': //big gold
			retVal = 5;
			break;

		default: //normal movement
			retVal = 1;
			break;
	}
	return retVal;
}

int currentRoom(Room* room)
{
	int num;
	int y;
	int x;
	int tall;

	tall = 0;
	getyx(stdscr, y, x);

	tall = findTallest(room);

	if(y < STARTY + tall) //top rooms
    {
		if(x < (STARTX + room[0].xDim))
        {
			num = 0;//first room
		}
		else if ((x > STARTX + room[0].xDim) && (x < STARTX + SPACE + room[1].xDim+room[0].xDim))
        {
			num = 1; //second room
		}
		else
        {
			num = 2; //third room
		}
	}
	else //bottom rooms
    {
		if((x < STARTX + room[3].xDim))
        {
			num = 3;
		}
		else if ((x > STARTX + room[3].xDim) && (x < STARTX + SPACE + room[3].xDim + room[4].xDim))//2= startx, 3 =space between rooms
        {
			num = 4;
		}
		else
        {
			num = 5;
		}
	}
	return num;
}

void gotoDoor(Room* room , int nextRoom)
{
	int pos;
	char side;
	int tall;

	tall = 0;
	tall = findTallest(room);

	for(int j = 0; j < 4; j++)
    {
    	//if its e,w,s, or n:
		if((room[nextRoom].door[j].side == 'e') || (room[nextRoom].door[j].side =='n') || (room[nextRoom].door[j].side == 'w') || (room[nextRoom].door[j].side == 's'))
        {
			pos = room[nextRoom].door[j].pos; //pos will be used to determine where to put the hero
			side = room[nextRoom].door[j].side; // ^same thing here
			break;
		}
	}

	switch(nextRoom)
    {
		case 0:
			switch(side) //it will always teleport to the first door in the file.
            {
				case 'n':
					mvaddch(STARTY - 1 , STARTX + pos , HERO); //put hero character on the door
					move(STARTY-1, STARTX + pos); //cursor with hero
					checkInput(room); //incase user wants to quit while theyre on the door
					mvaddch(STARTY - 1 , STARTX + pos , DOOR); //door character to overwrite hero
					mvaddch(STARTY , STARTX + pos , HERO);//moves hero into the room
					move(STARTY , STARTX + pos); //move down by one from door
					break;
				case 's':
					mvaddch(STARTY + room[0].yDim , STARTX + pos , HERO);
					move(STARTY + room[0].yDim , STARTX + pos);
					checkInput(room);
					mvaddch(STARTY + room[0].yDim , STARTX + pos , DOOR);
					mvaddch(STARTY-1 + room[0].yDim , STARTX + pos , HERO);
					move(STARTY-1 + room[0].yDim , STARTX + pos);//move up by one from door
					break;
				case 'e':
					mvaddch(STARTY + pos, STARTX + room[0].xDim, HERO);
					move(STARTY + pos, STARTX + room[0].xDim);
					checkInput(room);
					mvaddch(STARTY + pos, STARTX + room[0].xDim, DOOR);
					mvaddch(STARTY + pos, (STARTX - 1) + room[0].xDim, HERO);
					move(STARTY + pos, (STARTX - 1) + room[0].xDim); //go left one from door
					break;
				case 'w':
					mvaddch(STARTY + pos , STARTX-1 , HERO);
					move(STARTY + pos , STARTX-1);
					checkInput(room);
					mvaddch(STARTY + pos , STARTX-1 , DOOR);
					mvaddch(STARTY + pos , STARTX , HERO);
					move(STARTY + pos , STARTX); //go right one from door
					break;
			}
			break;

			//same logic as above apply
		case 1:
			switch(side)
            {
				case 'n':
					mvaddch(STARTY-1 , STARTX + SPACE + pos + room[0].xDim , HERO);
					move(STARTY-1 , STARTX + SPACE + pos + room[0].xDim);
					checkInput(room);
					mvaddch(STARTY-1 , STARTX + SPACE + pos + room[0].xDim , DOOR);
					mvaddch(STARTY , STARTX + SPACE + pos + room[0].xDim , HERO);
					move(STARTY , STARTX + SPACE + pos + room[0].xDim);
					break;
				case 's':
					mvaddch(STARTY + room[1].yDim , STARTX + SPACE + pos + room[0].xDim , HERO);
					move(STARTY + room[1].yDim , STARTX + SPACE + pos + room[0].xDim);
					checkInput(room);
					mvaddch(STARTY + room[1].yDim , STARTX + SPACE + pos + room[0].xDim , DOOR);
					mvaddch(STARTY-1 + room[1].yDim , STARTX + SPACE + pos + room[0].xDim , HERO);
					move(STARTY-1 + room[1].yDim , STARTX + SPACE + pos + room[0].xDim);
					break;
				case 'e':
					mvaddch(STARTY + pos , STARTX + SPACE + room[0].xDim + room[1].xDim, HERO);
					move(STARTY + pos , STARTX + SPACE + room[0].xDim + room[1].xDim);
					checkInput(room);
					mvaddch(STARTY + pos , STARTX + SPACE + room[0].xDim + room[1].xDim, DOOR);
					mvaddch(STARTY + pos , STARTX-1 + SPACE + room[0].xDim + room[1].xDim, HERO);
					move(STARTY + pos , STARTX-1 + SPACE + room[0].xDim + room[1].xDim);
					break;
				case 'w':
					mvaddch(STARTY + pos , STARTX-1 + SPACE + room[0].xDim , HERO);
					move(STARTY + pos , STARTX-1 + SPACE + room[0].xDim);
					checkInput(room);
					mvaddch(STARTY + pos , STARTX-1 + SPACE + room[0].xDim , DOOR);
					mvaddch(STARTY + pos , STARTX + SPACE + room[0].xDim , HERO);
					move(STARTY + pos , STARTX + SPACE + room[0].xDim);
					break;
			}
			break;
		case 2:
			switch(side)
            {
				case 'n':
					mvaddch(STARTY-1 , STARTX + (SPACE * 2) + pos + room[0].xDim + room[1].xDim, HERO);
					move(STARTY-1 , STARTX + (SPACE * 2) + pos + room[0].xDim + room[1].xDim);
					checkInput(room);
					mvaddch(STARTY-1 , STARTX + (SPACE * 2) + pos + room[0].xDim + room[1].xDim , DOOR);
					mvaddch(STARTY , STARTX + (SPACE * 2) + pos + room[0].xDim + room[1].xDim , HERO);
					move(STARTY , STARTX + (SPACE * 2) + pos + room[0].xDim + room[1].xDim);
					break;
				case 's':
					mvaddch(STARTY + room[2].yDim , STARTX + (SPACE * 2) + pos + room[0].xDim + room[1].xDim , HERO);
					move(STARTY + room[2].yDim , STARTX + (SPACE * 2) + pos + room[0].xDim + room[1].xDim);
					checkInput(room);
					mvaddch(STARTY + room[2].yDim , STARTX + (SPACE * 2) + pos + room[0].xDim + room[1].xDim , DOOR);
					mvaddch(STARTY-1 + room[2].yDim , STARTX + (SPACE * 2) + pos + room[0].xDim + room[1].xDim , HERO);
					move(STARTY-1 + room[2].yDim , STARTX + (SPACE * 2) + pos + room[0].xDim + room[1].xDim);
					break;
				case 'e':
					mvaddch(STARTY + pos , STARTX + (SPACE * 2) +  room[0].xDim + room[1].xDim + room[2].xDim , HERO);
					move(STARTY + pos , STARTX + (SPACE * 2) +  room[0].xDim + room[1].xDim + room[2].xDim);
					checkInput(room);
					mvaddch(STARTY + pos , STARTX + (SPACE * 2) +  room[0].xDim + room[1].xDim + room[2].xDim , DOOR);
					mvaddch(STARTY + pos , STARTX-1 + (SPACE * 2) +  room[0].xDim + room[1].xDim + room[2].xDim , HERO);
					move(STARTY + pos , STARTX-1 + (SPACE * 2) +  room[0].xDim + room[1].xDim + room[2].xDim);
					break;
				case 'w':
					mvaddch(STARTY + pos , STARTX-1 + (SPACE * 2) + room[0].xDim + room[1].xDim, HERO);
					move(STARTY + pos , STARTX-1 + (SPACE * 2) + room[0].xDim + room[1].xDim);
					checkInput(room);
					mvaddch(STARTY + pos , STARTX-1 + (SPACE * 2) + room[0].xDim + room[1].xDim, DOOR);
					mvaddch(STARTY + pos , STARTX + (SPACE * 2) + room[0].xDim + room[1].xDim, HERO);
					move(STARTY + pos , STARTX + (SPACE * 2) + room[0].xDim + room[1].xDim);
					break;
			}
			break;
		case 3:
			switch(side)
            {
				case 'n':
					mvaddch(STARTY-1 + tall, STARTX + pos , HERO);
					move(STARTY-1 + tall, STARTX + pos);
					checkInput(room);
					mvaddch(STARTY-1 + tall, STARTX + pos , DOOR);
					mvaddch(STARTY + tall, STARTX + pos , HERO);
					move(STARTY + tall, STARTX + pos);
	 	 			break;
				case 's':
					mvaddch(STARTY + tall + room[3].yDim, STARTX + pos , HERO);
					move(STARTY + tall + room[3].yDim, STARTX + pos);
					checkInput(room);
					mvaddch(STARTY + tall + room[3].yDim, STARTX + pos , DOOR);
					mvaddch(STARTY-1 + tall + room[3].yDim, STARTX + pos , HERO);
					move(STARTY-1 + tall + room[3].yDim, STARTX + pos);
					break;
				case 'e':
					mvaddch(STARTY + pos + tall , STARTX + room[3].xDim , HERO);
					move(STARTY + pos + tall , STARTX + room[3].xDim);
					checkInput(room);
					mvaddch(STARTY + pos + tall , STARTX + room[3].xDim , DOOR);
					mvaddch(STARTY + pos + tall , STARTX-1 + room[3].xDim , HERO);
					move(STARTY + pos + tall , STARTX-1 + room[3].xDim);
					break;
				case 'w':
					mvaddch(STARTY + pos + tall, STARTX-1 , HERO);
					move(STARTY + pos + tall, STARTX-1);
					checkInput(room);
					mvaddch(STARTY + pos + tall, STARTX-1 , DOOR);
					mvaddch(STARTY + pos + tall, STARTX , HERO);
					move(STARTY + pos + tall, STARTX);
					break;
			}
			break;
		case 4:
			switch(side)
            {
				case 'n':
					mvaddch(STARTY-1 + tall , STARTX + SPACE + pos + room[3].xDim , HERO);
					move(STARTY-1 + tall , STARTX + SPACE + pos + room[3].xDim);
					checkInput(room);
					mvaddch(STARTY-1 + tall , STARTX + SPACE + pos + room[3].xDim , DOOR);
					mvaddch(STARTY + tall , STARTX + SPACE + pos + room[3].xDim, HERO);
					move(STARTY + tall , STARTX + SPACE + pos + room[3].xDim);
					break;
				case 's':
					mvaddch(STARTY + tall + room[4].yDim , STARTX + SPACE +  pos + room[3].xDim , HERO);
					move(STARTY + tall + room[4].yDim , STARTX + SPACE +  pos + room[3].xDim);
					checkInput(room);
					mvaddch(STARTY + tall + room[4].yDim , STARTX + SPACE +  pos + room[3].xDim , DOOR);
					mvaddch(STARTY-1 + tall + room[4].yDim , STARTX + SPACE +  pos + room[3].xDim , HERO);
					move(STARTY-1 + tall + room[4].yDim , STARTX + SPACE +  pos + room[3].xDim);
					break;
				case 'e':
					mvaddch(STARTY + pos + tall , STARTX + SPACE + room[3].xDim + room[4].xDim , HERO);
					move(STARTY + pos + tall , STARTX + SPACE + room[3].xDim + room[4].xDim);
					checkInput(room);
					mvaddch(STARTY + pos + tall , STARTX + SPACE + room[3].xDim + room[4].xDim , DOOR);
					mvaddch(STARTY + pos + tall , STARTX-1 + SPACE + room[3].xDim + room[4].xDim , HERO);
					move(STARTY + pos + tall , STARTX-1 + SPACE + room[3].xDim + room[4].xDim);
					break;
				case 'w':
					mvaddch(STARTY + pos + tall , STARTX-1 + SPACE + room[3].xDim , HERO);
					move(STARTY + pos + tall , STARTX-1 + SPACE + room[3].xDim);
					checkInput(room);
					mvaddch(STARTY + pos + tall , STARTX-1 + SPACE + room[3].xDim, DOOR);
					mvaddch(STARTY + pos + tall , STARTX + SPACE + room[3].xDim, HERO);
					move(STARTY + pos + tall , STARTX + SPACE + room[3].xDim);
					break;
			}
			break;
		case 5:
			switch(side)
            {
				case 'n':
					mvaddch(STARTY-1 + tall , STARTX + (SPACE * 2) + pos + room[3].xDim + room[4].xDim , HERO);
					move(STARTY-1 + tall , STARTX + (SPACE * 2) + pos + room[3].xDim + room[4].xDim);
					checkInput(room);
					mvaddch(STARTY-1 + tall , STARTX + (SPACE * 2) + pos + room[3].xDim + room[4].xDim , DOOR);
					mvaddch(STARTY + tall , STARTX + (SPACE * 2) + pos + room[3].xDim + room[4].xDim , HERO);
					move(STARTY + tall , STARTX + (SPACE * 2) + pos + room[3].xDim + room[4].xDim);
					break;
				case 's':
					mvaddch(STARTY + tall + room[5].yDim , STARTX + (SPACE * 2) + pos  + room[3].xDim + room[4].xDim , HERO);
					move(STARTY + tall + room[5].yDim , STARTX + (SPACE * 2) + pos  + room[3].xDim + room[4].xDim);
					checkInput(room);
					mvaddch(STARTY + tall + room[5].yDim , STARTX + (SPACE * 2) + pos  + room[3].xDim + room[4].xDim , DOOR);
					mvaddch(STARTY-1 + tall + room[5].yDim , STARTX + (SPACE * 2) + pos + room[3].xDim + room[4].xDim , HERO);
					move(STARTY-1 + tall + room[5].yDim , STARTX + (SPACE * 2) + pos  + room[3].xDim + room[4].xDim);
					break;
				case 'e':
					mvaddch(STARTY + pos + tall , STARTX + (SPACE * 2) + room[3].xDim + room[4].xDim + room[5].xDim , HERO);
					move(STARTY + pos + tall , STARTX + (SPACE * 2) + room[3].xDim + room[4].xDim + room[5].xDim);
					checkInput(room);
					mvaddch(STARTY + pos + tall , STARTX + (SPACE * 2) + room[3].xDim + room[4].xDim + room[5].xDim , DOOR);
					mvaddch(STARTY + pos + tall , STARTX-1 + (SPACE * 2) + room[3].xDim + room[4].xDim + room[5].xDim , HERO);
					move(STARTY + pos + tall , STARTX-1 + (SPACE * 2) + room[3].xDim + room[4].xDim + room[5].xDim);
					break;
				case 'w':
					mvaddch(STARTY + pos + tall , STARTX-1 + (SPACE * 2) + room[3].xDim + room[4].xDim , HERO);
					move(STARTY + pos + tall , STARTX-1 + (SPACE * 2) + room[3].xDim + room[4].xDim);
					checkInput(room);
					mvaddch(STARTY + pos + tall , STARTX-1 + (SPACE * 2) + room[3].xDim + room[4].xDim , DOOR);
					mvaddch(STARTY + pos + tall , STARTX + (SPACE * 2) + room[3].xDim + room[4].xDim , HERO);
					move(STARTY + pos + tall , STARTX + (SPACE * 2) + room[3].xDim + room[4].xDim);
					break;
			}
			break;
	}
}

void checkInput(Room* room)
{
	if (getch() == 'q')//checks character while the hero is on the door
    {
		endGame(room);
		exit(1);
	}
}
