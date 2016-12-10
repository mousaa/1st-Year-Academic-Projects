#include "curses.h"
#include "userInterface.h"
#include "checkWindow.h"
#include "playerMove.h"
#include "endMsg.h"
#include "enemyMove.h"
#include "combat.h"

 
void fight(Room* room, int y, int x, int oldy, int oldx, char enemy)
{
	int num;
	num = currentRoom(room);

	switch(enemy)
	{	
		//combat algorthim based on enemy
		//CHANGE
		//really buggy becuase of monster movement 
		case 'B':
			switch(num)
			{
				case 0:
					if(rand() % 10 + 1 > 4)
					{
						room[0].bat[0].health -= room[0].hero.attackRate;
						printNotification(room,y,x,oldy,oldx, 'G', room[0].hero.attackRate);
						if(room[0].bat[0].health < 1)
						{
							room[0].bat[0].cycle = 0; //stop bat movement
							stepOn(room,y,x,oldy,oldx);
							printNotification(room ,y,x,oldy,oldx, 'B', 0);
						}

					}
					else
					{
						room[0].hero.health -= 5;
						if(room[0].hero.health < 1)
						{
							endGame(room);
							exit(1);
						}

						printNotification(room,y,x,oldy,oldx, 'H', 5); //lost damage
						updateStatus(room, room[0].hero.health, 1);
						move(oldy,oldx);
					}
					break;
				case 2:
					if(rand() % 10 + 1 > 4)
					{
						room[2].bat[1].health -= room[0].hero.attackRate;
						printNotification(room,y,x,oldy,oldx, 'G', room[0].hero.attackRate);
						if(room[2].bat[1].health < 1)
						{
							room[2].bat[1].cycle = 0;
							stepOn(room,y,x,oldy,oldx);
							printNotification(room,y,x,oldy,oldx, 'B', 0);
						}

					}
					else
					{
						if(room[0].hero.health < 1)
						{
							endGame(room);
							exit(1);
						}

						room[0].hero.health -= 5;
						printNotification(room,y,x,oldy,oldx, 'H', 5);
						updateStatus(room,room[0].hero.health,1);
						move(oldy,oldx);
					}
					break;
				case 4:
					if(y < 33)
					{
						if(rand() % 10 + 1 > 4)
						{
							room[4].bat[2].health -= room[0].hero.attackRate;
							printNotification(room,y,x,oldy,oldx, 'G', room[0].hero.attackRate);
							if(room[4].bat[2].health < 1)
							{
								room[4].bat[2].cycle = 0;
								stepOn(room,y,x,oldy,oldx);
								printNotification(room,y,x,oldy,oldx, 'B', 0);
							}

						}
						else
						{
							if(room[0].hero.health < 1)
							{
								endGame(room);
								exit(1);
							}

							room[0].hero.health -= 5;
							printNotification(room,y,x,oldy,oldx, 'H', 5);
							updateStatus(room,room[0].hero.health,1);
							move(oldy,oldx);
						}
					}
					else
					{
						if(rand() % 10 + 1 > 4)
						{
							room[4].bat[3].health -= room[0].hero.attackRate;
							printNotification(room,y,x,oldy,oldx, 'G', room[0].hero.attackRate);
							if(room[4].bat[3].health < 1)
							{
								room[4].bat[3].cycle = 0;
								stepOn(room,y,x,oldy,oldx);
								printNotification(room,y,x,oldy,oldx, 'B', 0);
							}

						}
						else
						{
							if(room[0].hero.health < 1)
							{
								endGame(room);
								exit(1);
							}

							room[0].hero.health -= 5;
							printNotification(room,y,x,oldy,oldx, 'H', 5);
							updateStatus(room,room[0].hero.health,1);
							move(oldy,oldx);
						}
					}
					break;
				case 5:
					if(y < 35)
					{
						if(rand() % 10 + 1 > 4)
						{
							//player attack
							room[5].bat[4].health -= room[0].hero.attackRate;
							printNotification(room,y,x,oldy,oldx,'G',  room[0].hero.attackRate); //give damage
							if(room[5].bat[4].health < 1)
							{
								room[5].bat[4].cycle = 0;
								stepOn(room,y,x,oldy,oldx);
								printNotification(room,y,x,oldy,oldx,'B',0); //killed bat
							}

						}
						else //enemy attack
						{
							room[0].hero.attackRate -= 5;
							if(room[0].hero.health < 1)
							{
								endGame(room);
								exit(1);
							}

							printNotification(room,y,x,oldy,oldx,'H', 1); //take damage
							updateStatus(room, room[0].hero.attackRate, 3);
							move(oldy,oldx);
						}
				break;
					}
					else
					{
						if(rand() % 10 + 1 > 4)
						{
							//player attack
							room[5].bat[5].health -= room[0].hero.attackRate;
							printNotification(room,y,x,oldy,oldx,'G',  room[0].hero.attackRate); //give damage
							if(room[5].bat[5].health < 1)
							{
								room[5].bat[5].cycle = 0;
								stepOn(room,y,x,oldy,oldx);
								printNotification(room,y,x,oldy,oldx,'B',0); //killed aquator
							}

						}
						else //enemy attack
						{
							room[0].hero.health -= 5;
							printNotification(room,y,x,oldy,oldx,'H', 5); //take damage
							updateStatus(room, room[0].hero.attackRate, 3);
							move(oldy,oldx);
						}

				break;
					}
					break;
			}
		case 'S':
			switch(num)
			{
				case 0:
					if(rand() % 10 + 1 > 4)
					{
						room[0].snake[0].health -= room[0].hero.attackRate;
						printNotification(room,y,x,oldy,oldx, 'G', room[0].hero.attackRate);
						if(room[0].snake[0].health < 1)
						{
							room[0].snake[0].cycle = 0;
							stepOn(room,y,x,oldy,oldx);
							printNotification(room ,y,x,oldy,oldx, 'S', 0);
						}
					}
					else
					{
						room[0].hero.health -= 5;
						if(room[0].hero.health < 1)
						{
							endGame(room);
							exit(1);
						}
						printNotification(room,y,x,oldy,oldx, 'H', 5);
						updateStatus(room, room[0].hero.health, 1);
						move(oldy,oldx);
					}
					break;
				case 2:
					if(rand() % 10 + 1 > 4)
					{
						room[2].snake[1].health -= room[0].hero.attackRate;
						printNotification(room,y,x,oldy,oldx, 'G', room[0].hero.attackRate);
						if(room[2].snake[1].health < 1)
						{
							room[2].snake[1].cycle = 0;
							stepOn(room,y,x,oldy,oldx);
							printNotification(room,y,x,oldy,oldx, 'S', 0);
						}
					}
					else
					{
						if(room[0].hero.health < 1)
						{
							endGame(room);
							exit(1);
						}
						room[0].hero.health -= 5;
						printNotification(room,y,x,oldy,oldx, 'H', 5);
						updateStatus(room,room[0].hero.health,1);
						move(oldy,oldx);
					}
					break;
				case 4:
					if(y < 33)
					{
						if(rand() % 10 + 1 > 4)
						{
							room[4].snake[2].health -= room[0].hero.attackRate;
							printNotification(room,y,x,oldy,oldx, 'G', room[0].hero.attackRate);
							if(room[4].snake[2].health < 1)
							{
								room[4].snake[2].cycle = 0;
								stepOn(room,y,x,oldy,oldx);
								printNotification(room,y,x,oldy,oldx, 'S', 0);
							}

						}
						else
						{
							if(room[0].hero.health < 1)
							{
								endGame(room);
								exit(1);
							}
							room[0].hero.health -= 5;
							printNotification(room,y,x,oldy,oldx, 'H', 5);
							updateStatus(room,room[0].hero.health,1);
							move(oldy,oldx);
						}
					}
					else
					{
						if(rand() % 10 + 1 > 4)
						{
							room[4].snake[3].health -= room[0].hero.attackRate;
							printNotification(room,y,x,oldy,oldx, 'G', room[0].hero.attackRate);
							if(room[4].snake[3].health < 1)
							{
								room[4].snake[3].cycle = 0;
								stepOn(room,y,x,oldy,oldx);
								printNotification(room,y,x,oldy,oldx, 'S', 0);
							}
						}
						else
						{
							if(room[0].hero.health < 1)
							{
								endGame(room);
								exit(1);
							}
							room[0].hero.health -= 5;
							printNotification(room,y,x,oldy,oldx, 'H', 5);
							updateStatus(room,room[0].hero.health,1);
							move(oldy,oldx);
						}
					}
					break;
				case 5:
					if(y < 34)
					{
						if(rand() % 10 + 1 > 4)
						{
							//player attack
							room[5].snake[4].health -= room[0].hero.attackRate;
							printNotification(room,y,x,oldy,oldx,'G',  room[0].hero.attackRate); //give damage
							if(room[5].snake[4].health < 1)
							{
								room[5].snake[4].cycle = 0;
								stepOn(room,y,x,oldy,oldx);
								printNotification(room,y,x,oldy,oldx,'S',0); //killed zombie
							}
						}
						else //enemy attack
						{
							room[0].hero.attackRate -= 5;
							if(room[0].hero.health < 1)
							{
								endGame(room);
								exit(1);
							}
							printNotification(room,y,x,oldy,oldx,'H', 1); //take damage
							updateStatus(room, room[0].hero.attackRate, 3);
							move(oldy,oldx);
						}
				break;
					}
					else
					{
						if(rand() % 10 + 1 > 2)
						{
							//player attack
							room[5].bat[5].health -= room[0].hero.attackRate;
							printNotification(room,y,x,oldy,oldx,'G',  room[0].hero.attackRate); //give damage
							if(room[5].bat[5].health < 1)
							{
								room[5].bat[5].cycle = 0;
								stepOn(room,y,x,oldy,oldx);
								printNotification(room,y,x,oldy,oldx,'S',0); //killed Snake
							}
						}
						else //enemy attack
						{
							room[0].hero.health -= 5;
							printNotification(room,y,x,oldy,oldx,'H', 5); //take damage
							updateStatus(room, room[0].hero.attackRate, 3);
							move(oldy,oldx);
						}
				break;
					}
					break;
			}
		case 'T':
			if(rand() %10 + 1 > 3)
			{
				room[1].troll.health -= room[0].hero.attackRate;
				printNotification(room,y,x,oldy,oldx,'G',  room[0].hero.attackRate);
				if(room[1].troll.health < 1)
				{
					stepOn(room,y,x,oldy,oldx);
					room[0].trollCycle =0;
					printNotification(room,y,x,oldy,oldx,'M',0); //killed troll
				}
			}
			else
			{
				room[0].hero.health -= 5;
				if(room[0].hero.health < 1)
				{
					endGame(room);
					exit(1);
				}
				printNotification(room,y,x,oldy,oldx,'H', 5); //take damage
				updateStatus(room, room[0].hero.health, 1);
				move(oldy,oldx);
			}
			break;
		case 'Z':
			switch(num)
			{
				case 0:
					if(rand() % 10 + 1 > 2)
					{
						room[0].zombie[0].health -= room[0].hero.attackRate;
						printNotification(room,y,x,oldy,oldx, 'G', room[0].hero.attackRate);
						if(room[0].zombie[0].health < 1)
						{
							room[0].zombie[0].cycle = 0;
							stepOn(room,y,x,oldy,oldx);
							printNotification(room ,y,x,oldy,oldx, 'Z', 0);
						}
					}
					else
					{
						room[0].hero.health -= 5;
						if(room[0].hero.health < 1)
						{
							endGame(room);
							exit(1);
						}
						printNotification(room,y,x,oldy,oldx, 'H', 5);
						updateStatus(room, room[0].hero.health, 1);
						move(oldy,oldx);
					}
					break;
				case 2:
					if(rand() % 10 + 1 > 2)
					{
						room[2].zombie[1].health -= room[0].hero.attackRate;
						printNotification(room,y,x,oldy,oldx, 'G', room[0].hero.attackRate);
						if(room[2].zombie[1].health < 1)
						{
							room[2].zombie[1].cycle = 0;
							stepOn(room,y,x,oldy,oldx);
							printNotification(room,y,x,oldy,oldx, 'Z', 0);
						}
					}
					else
					{
						if(room[0].hero.health < 1)
						{
							endGame(room);
							exit(1);
						}
						room[0].hero.health -= 5;
						printNotification(room,y,x,oldy,oldx, 'H', 5);
						updateStatus(room,room[0].hero.health,1);
						move(oldy,oldx);
					}
					break;
				case 4:
					if(y < 33)
					{
						if(rand() % 10 + 1 > 2)
						{
							room[4].zombie[2].health -= room[0].hero.attackRate;
							printNotification(room,y,x,oldy,oldx, 'G', room[0].hero.attackRate);
							if(room[4].zombie[2].health < 1)
							{
								room[4].zombie[2].cycle = 0;
								stepOn(room,y,x,oldy,oldx);
								printNotification(room,y,x,oldy,oldx, 'Z', 0);
							}
						}
						else
						{
							if(room[0].hero.health < 1)
							{
								endGame(room);
								exit(1);
							}
							room[0].hero.health -= 5;
							printNotification(room,y,x,oldy,oldx, 'H', 5);
							updateStatus(room,room[0].hero.health,1);
							move(oldy,oldx);
						}
					}
					else
					{
						if(rand() % 10 + 1 > 2)
						{
							room[4].zombie[3].health -= room[0].hero.attackRate;
							printNotification(room,y,x,oldy,oldx, 'G', room[0].hero.attackRate);
							if(room[4].zombie[3].health < 1)
							{
								room[4].zombie[3].cycle = 0;
								stepOn(room,y,x,oldy,oldx);
								printNotification(room,y,x,oldy,oldx, 'Z', 0);
							}
						}
						else
						{
							if(room[0].hero.health < 1)
							{
								endGame(room);
								exit(1);
							}
							room[0].hero.health -= 5;
							printNotification(room,y,x,oldy,oldx, 'H', 5);
							updateStatus(room,room[0].hero.health,1);
							move(oldy,oldx);
						}
					}
					break;
				case 5:
					if(y < 34)
					{
						if(rand() % 10 + 1 > 2)
						{
							//player attack
							room[5].zombie[4].health -= room[0].hero.attackRate;
							printNotification(room,y,x,oldy,oldx,'G',  room[0].hero.attackRate); //give damage
							if(room[5].zombie[4].health < 1)
							{
								room[5].zombie[4].cycle = 0;
								stepOn(room,y,x,oldy,oldx);
								printNotification(room,y,x,oldy,oldx,'Z',0); //killed zombie
							}
						}
						else //enemy attack
						{
							room[0].hero.attackRate -= 5;
							if(room[0].hero.health < 1)
							{
								endGame(room);
								exit(1);
							}
							printNotification(room,y,x,oldy,oldx,'H', 1); //take damage
							updateStatus(room, room[0].hero.attackRate, 3);
							move(oldy,oldx);
						}
				break;
					}
					else
					{
						if(rand() % 10 + 1 > 2)
						{
							//player attack
							room[5].zombie[5].health -= room[0].hero.attackRate;
							printNotification(room,y,x,oldy,oldx,'G',  room[0].hero.attackRate); //give damage
							if(room[5].zombie[5].health < 1)
							{
								room[5].zombie[5].cycle = 0;
								stepOn(room,y,x,oldy,oldx);
								printNotification(room,y,x,oldy,oldx,'Z',0); //killed aquator
							}
						}
						else //enemy attack
						{
							room[0].hero.health -= 5;
							printNotification(room,y,x,oldy,oldx,'H', 5); //take damage
							updateStatus(room, room[0].hero.attackRate, 3);
							move(oldy,oldx);
						}
				break;
					}
			}
			break;	
		case 'A':
			switch(num)
			{
				case 0:
					if(rand() % 10 + 1 > 2)
					{	
						//player attack
						room[0].aquator[0].health -= room[0].hero.attackRate;
						printNotification(room,y,x,oldy,oldx,'G',  room[0].hero.attackRate); //give damage
						if(room[0].aquator[0].health < 1)
						{
							stepOn(room,y,x,oldy,oldx);
							printNotification(room,y,x,oldy,oldx,'A',0); //killed aquator
						}
					}
					else //enemy attack
					{
						room[0].hero.attackRate -= 1;
						printNotification(room,y,x,oldy,oldx,'T', 1); //take damage
						updateStatus(room, room[0].hero.attackRate, 3);
						move(oldy,oldx);
					}
				break;
				case 2:
					if(rand() % 10 + 1 > 2)
					{
						//player attack
						room[2].aquator[1].health -= room[0].hero.attackRate;
						printNotification(room,y,x,oldy,oldx,'G',  room[0].hero.attackRate); //give damage
						if(room[2].aquator[1].health < 1)
						{
							stepOn(room,y,x,oldy,oldx);
							printNotification(room,y,x,oldy,oldx,'A',0); //killed aquator
						}
					}
					else //enemy attack
					{
						room[0].hero.attackRate -= 1;
						printNotification(room,y,x,oldy,oldx,'T', 1); //take damage
						updateStatus(room, room[0].hero.attackRate, 3);
						move(oldy,oldx);
					}
				break;
				case 4:
					if(y < 32)
					{
						if(rand() % 10 + 1 > 2)
						{
							//player attack
							room[4].aquator[2].health -= room[0].hero.attackRate;
							printNotification(room,y,x,oldy,oldx,'G',  room[0].hero.attackRate); //give damage
							if(room[4].aquator[2].health < 1)
							{
								stepOn(room,y,x,oldy,oldx);
								printNotification(room,y,x,oldy,oldx,'A',0); //killed aquator
							}
						}
						else //enemy attack
						{
							room[0].hero.attackRate -= 1;
							printNotification(room,y,x,oldy,oldx,'T', 1); //take damage
							updateStatus(room, room[0].hero.attackRate, 3);
							move(oldy,oldx);
						}
				break;
					}
					else
					{
						if(rand() % 10 + 1 > 2)
						{	
						//player attack
							room[4].aquator[3].health -= room[0].hero.attackRate;
							printNotification(room,y,x,oldy,oldx,'G',  room[0].hero.attackRate); //give damage
							if(room[4].aquator[3].health < 1)
							{
								stepOn(room,y,x,oldy,oldx);
								printNotification(room,y,x,oldy,oldx,'A',0); //killed aquator
							}
						}
						else //enemy attack
						{
							room[0].hero.attackRate -= 1;
							printNotification(room,y,x,oldy,oldx,'T', 1); //take damage
							updateStatus(room, room[0].hero.attackRate, 3);
							move(oldy,oldx);
						}
				break;
					}
				case 5:
					if(y < 34)
					{
						if(rand() % 10 + 1 > 2)
						{
							//player attack
							room[5].aquator[4].health -= room[0].hero.attackRate;
							printNotification(room,y,x,oldy,oldx,'G',  room[0].hero.attackRate); //give damage
							if(room[5].aquator[4].health < 1)
							{
								stepOn(room,y,x,oldy,oldx);
								printNotification(room,y,x,oldy,oldx,'A',0); //killed aquator
							}
						}
						else //enemy attack
						{
							room[0].hero.attackRate -= 1;
							printNotification(room,y,x,oldy,oldx,'T', 1); //take damage
							updateStatus(room, room[0].hero.attackRate, 3);
							move(oldy,oldx);
						}
				break;
					}

					else
					{
						if(rand() % 10 + 1 > 2)
						{
							//player attack
							room[5].aquator[5].health -= room[0].hero.attackRate;
							printNotification(room,y,x,oldy,oldx,'G',  room[0].hero.attackRate); //give damage
							if(room[5].aquator[5].health < 1)
							{
								stepOn(room,y,x,oldy,oldx);
								printNotification(room,y,x,oldy,oldx,'A',0); //killed aquator
							}
						}
						else //enemy attack
						{
							room[0].hero.attackRate -= 1;
							printNotification(room,y,x,oldy,oldx,'T', 1); //take damage
							updateStatus(room, room[0].hero.attackRate, 3);
							move(oldy,oldx);
						}
				break;
					}
			}
		break;
	}
}