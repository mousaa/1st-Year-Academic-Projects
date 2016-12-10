/**
 * see stats.h for complete function definitions
 *
 */

#include <stdio.h>
#include <string.h>
#include "linkedList.h"
#include "stats.h"

#include "foodTracker.h"

void printStats(Food * head)
{
	int calories;
	int length;
	int vCtr;
	int mCtr;
	int dCtr;
	int gCtr;
	int fCtr;
	float vTot;
	float mTot;
	float dTot;
	float gTot;
	float fTot;

	calories = 0;
	length = 0;
	vCtr = 0;
	mCtr = 0;
	dCtr = 0;
	gCtr = 0;
	fCtr = 0;
	vTot = 0;
	mTot = 0;
	dTot = 0;
	gTot = 0;
	fTot = 0;

	Food * temp;
	temp = head;
	while(temp != NULL)
	{
		if(strcmp(temp->foodGroup, "vegfruit") == 0)
		{
			vTot += temp->calories;
			vCtr++;	
		}
		if(strcmp(temp->foodGroup, "meat") == 0)
		{
			mTot += temp->calories;
			mCtr++;	
		}
		if(strcmp(temp->foodGroup, "dairy") == 0)
		{
			dTot += temp->calories;
			dCtr++;	
		}
		if(strcmp(temp->foodGroup, "grains") == 0)
		{
			gTot += temp->calories;
			gCtr++;	
		}
		if(strcmp(temp->foodGroup, "fat") == 0)
		{
			fTot += temp->calories;
			fCtr++;	
		}
		calories += temp->calories;
		length++;
		temp = temp->next;
	}	

	
	printf("%d\n", calories);

	if(vCtr != 0)
	{
		printf("%.2f\n", vTot/vCtr);
	}
	else
	{
		printf("0.00\n");
	}
	
	if(mCtr != 0)
	{
		printf("%.2f\n", mTot/mCtr);
	}
	else
	{
		printf("0.00\n");
	}

	if(dCtr != 0)
	{
		printf("%.2f\n", dTot/dCtr);
	}
	else
	{
		printf("0.00\n");
	}

	if(gCtr != 0)
	{
		printf("%.2f\n", gTot/gCtr);
	}
	else
	{
		printf("0.00\n");
	}

	if(fCtr != 0)
	{
		printf("%.2f\n", fTot/fCtr);
	}
	else
	{
		printf("0.00\n");
	}
	printf("%d\n", length);
}