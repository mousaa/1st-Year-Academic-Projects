/**
 * see endMsg.h for complete function definitions
 *
 */
#include "endMsg.h"

void printGold(Room* room)
{
	int bigGold;
	int smallGold;
	smallGold = room[0].hero.smallGold + room[1].hero.smallGold + room[2].hero.smallGold + room[3].hero.smallGold + room[4].hero.smallGold + room[5].hero.smallGold;
	bigGold = room[0].hero.bigGold + room[1].hero.bigGold + room[2].hero.bigGold + room[3].hero.bigGold + room[4].hero.bigGold + room[5].hero.bigGold;
	printf("\n\t****** GOLD ******");
	printf("\n\tTotal gold collected: %d\n\n", bigGold + smallGold);
}
void printInventory(Room* room)
{
	printf("\t****** INVENTORY ******\n");
	if(room[0].hero.capacity == 0)
	{
		printf("\tItem \t\t Stat\n");
		for(int i = 0; i < 5; i++)
		printf("\tEMPTY \t\t NA\n");
	}
	else
	{
		printf("\tItem \t\t Stat\n");
		for(int i = 0; i < 5; i++)
		{
			switch(room[0].hero.bag[i].weapon)
			{
				printf("\n");
				case ')':
					printf("\tCommon weapon \t %d\n", room[0].hero.bag[i].weaponStat);
					break;
				case '(':
					printf("\tRare weapon \t %d\n", room[0].hero.bag[i].weaponStat);
					break;
				case ']':
					printf("\tEquipment   \t %d\n", room[0].hero.bag[i].weaponStat);
					break;
				default:
					printf("\tEMPTY       \t NA\n");
					break;
			}
		}
	}
	printf("\n\n");
}