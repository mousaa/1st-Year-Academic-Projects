/**
 * see playerMove.h for complete function definitions
 *
 */
#include "curses.h"
#include "userInterface.h"
#include "checkWindow.h"
#include "playerMove.h"
#include "endMsg.h"
#include "enemyMove.h"
#include "combat.h"


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
	//sum of all rooms' gold/potion
	smallGold = room[0].hero.smallGold + room[1].hero.smallGold + room[2].hero.smallGold + room[3].hero.smallGold + room[4].hero.smallGold + room[5].hero.smallGold;
	bigGold = room[0].hero.bigGold + room[1].hero.bigGold + room[2].hero.bigGold + room[3].hero.bigGold + room[4].hero.bigGold + room[5].hero.bigGold;
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
		case 'p': //potion
			if(!checkBag(room, y,x, '!'))
			{
				mvprintw(0,0,"Out of potions");
				move(y,x);
				checkInput(room, y, x);
				break;
			}
			else
			{
				mvprintw(0,0,"Hero recovered full health");
				room[0].hero.health = 50;
				updateStatus(room,room[0].hero.health , 1);
				move(y,x);
				checkInput(room, y, x);
				break;
			}
			break;
		default: 
			break;
	}
	new = nextPos(y,x); //position that hero's about to move to
	switch(new)
    {
		case 0://cant walk on.
			moveEnemy(room);
			move(oldy,oldx);
			break;
		case 1://collectable || regular movement
			moveEnemy(room);
			move(y,x);

			if (room[0].ctrZ == 1)
			{
				mvaddch(y,x,HERO);
				mvaddch(oldy,oldx, DOOR);
				move(y,x);
				room[0].ctrX = 0;
				room[0].ctrZ = 0;
				room[0].ctrY = 0;
			}
			else if(room[0].ctrZ == 0)
			{
				mvaddch(y,x,HERO); //moves hero to the location
				mvaddch(oldy,oldx, '.'); //to avoid echoing of hero
				move(y,x); //moves cursor to hero's position
			}
			break;
		case 2: //stairs
			endGame(room); //ends game, prints gold amount,frees room
			exit(1);
			break;
		case 3: //hit a DOOR
			moveEnemy(room);

			if(room[0].ctrX == 0)
			{
				mvaddch(y,x,HERO);
				move(y,x);
				mvaddch(oldy,oldx, '.'); // (1) HERO ON FIRST DOOR
				printNotification(room,y,x,oldy, oldx, '+', 0);
				room[0].ctrX = 1;
			}
			else if(room[0].ctrX  == 1)
			{
				mvaddch(y,x,HERO);
				mvaddch(oldy,oldx,HALLWAY); //(3) HERO EXITING HALLWAY
				move(y,x);
				printNotification(room,y,x,oldy, oldx, '+', 0);
			    room[0].ctrZ = 1; //TO PUT DOOR BACK WHEN COLLIDE WITH '.'
			}
			break;
		case 4: //small gold
			moveEnemy(room);
			mvaddch(y,x,HERO);
			mvaddch(oldy,oldx, '.');
			move(y,x);
			smallGold = (rand() % 51); //random between 0 and 50
			room[currentRoom(room)].hero.smallGold += smallGold;
			break;

		case 5://big gold
			moveEnemy(room);
			mvaddch(y,x,HERO);
			mvaddch(oldy,oldx, '.');
			move(y,x);
			bigGold = (rand() % 200) + 50; //random between 50 and 250
			room[currentRoom(room)].hero.bigGold = bigGold;
			break;
		case 6: // common weapon
			moveEnemy(room);

			printNotification(room, y, x, oldy, oldx,  ')', 0);
			break;
		case 7: //rare 
			moveEnemy(room);

			printNotification(room, y, x, oldy, oldx,  '(', 0);
			break;
		case 8: //equip
			moveEnemy(room);

			printNotification(room, y, x, oldy, oldx,  ']', 0);
			break;
		case 9: //potion
			moveEnemy(room);

			room[0].hero.potion += 1;
			printNotification(room,y,x,oldy, oldx, '!', 0);
			move(y,x);
			break;
		case 10: //HIT HALLWAY
			moveEnemy(room);
			if(room[0].ctrY == 0)
			{
				mvaddch(y,x,HERO);
				mvaddch(oldy,oldx, DOOR); //(2) HERO STARTED WALKING IN HALLWAY, PUT BACK DOOR
				move(y,x);
				room[0].ctrY =1;
			}
			else if(room[0].ctrY == 1)
			{
				mvaddch(y,x,HERO);
				mvaddch(oldy,oldx,HALLWAY); // (4) HERO STILL WALKING IN HALLWAY
				move(y,x);
			}
			break;

		//ENEMIES
		case 11:	//aquator
			fight(room, y, x, oldy, oldx, 'A');
			break;
		case 12: //bat
			fight(room,y,x, oldy,oldx, 'B');
			break;
		case 13://snake
			fight(room,y,x, oldy,oldx, 'S');
			break;
		case 14:	//zombie
			fight(room, y, x, oldy, oldx, 'Z');	
			break;
		case 15:	//troll
			fight(room,y,x,oldy,oldx,'T');
			break;
	}
}
void stepOn(Room* room, int y, int x, int oldy, int oldx)
{
	mvaddch(y,x,HERO);
	mvaddch(oldy,oldx, '.');
	move(y,x);
}	

int checkBag(Room* room, int y, int x, char z)
{
	switch(z)
	{
		int itemCtr;
		int potionCtr;

		case ')':
		case '(':
		case ']':
			itemCtr = room[0].hero.capacity;
			if(itemCtr == 5)
			{
				return 0;// full bag
			}
			else
			{
				room[0].hero.bag[itemCtr].weapon = z;
				createStat(room, itemCtr, z);
				updateStatus(room, itemCtr , 4);
				room[0].hero.capacity++;
			}
		break;

		case '!':
			potionCtr = room[0].hero.potion;
			if (potionCtr == 0)
			{
				return 0; //empty pot
			}
			else
			{
				room[0].hero.potion--;
				updateStatus(room, potionCtr, 2);
			}
			break;
	}
	return 1; //can add to inventory
}


void createStat(Room* room, int itemCtr, char z)
{
	int randStat;
	switch(z)
	{
		case ')':
			randStat = (rand() % 9) + 1;
			room[0].hero.bag[itemCtr].weaponStat = randStat;
			break;
		case '(':
			randStat = (rand() % 6) + 10;
			room[0].hero.bag[itemCtr].weaponStat = randStat;
			break;
		case ']':
			randStat = rand() % 21;
			room[0].hero.bag[itemCtr].weaponStat = randStat;
			break;
	}
}
void checkInput(Room* room, int y, int x)
{
	if (getch() == 'q')//checks character while the hero is getting notification etc incase they want to quit
    {
		endGame(room);
		exit(1);
	}
	else
	{
		move(0,0);
		clrtoeol();
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
		case ')': //common weapon
			retVal = 6;
			break;
		case '(': //rare weapon
			retVal = 7;
			break;
		case ']': //equipment
			retVal = 8;
			break;
		case '!': //potion
			retVal = 9;
			break;	
		case HALLWAY:
			retVal = 10;
			break;
		case 'A':
			retVal = 11;
			break;
		case 'B':
			retVal = 12;
			break;
		case 'S':
			retVal = 13;
			break;
		case 'Z':
			retVal = 14;
			break;
		case 'T':
			retVal = 15;
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