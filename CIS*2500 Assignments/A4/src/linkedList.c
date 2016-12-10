#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "linkedList.h"

Food* createRecord(char * name, char * group, int calories, char theType)
{
	if(strlen(name) >= 50)
	{
		return NULL;
	}
	else if(strlen(group)>= 50)
	{
		return NULL;
	}
	else if(calories <= 0)
	{
		return NULL;
	}
	else if(!((theType == 'j') || (theType == 'h')))
	{
		return NULL;
	}

	else
	{
		Food* new;
		new = malloc(sizeof(Food));
		if(new == NULL)
		{
		    return NULL;
 		}
		else
		{
		    new->name = malloc(strlen(name) + 1);
		    if(new->name == NULL)
		    {
				free(new);
				return NULL;
	        }
		    new->foodGroup = malloc(strlen(group) + 1);

		  	if(new->foodGroup == NULL)
		    {
				free(new->name);
				free(new);
				return NULL;
		    }
		}

            strcpy(new->name,name);
            strcpy(new->foodGroup, group);
	    	new->calories = calories;
            new->type = theType;
            new->next = NULL;
			
            return new; 
	}    	
}

char * printRecord(Food * toPrint)
{
	if(toPrint == NULL)
		return NULL;

	char* string;
	string = malloc(sizeof(Food));

	sprintf(string,"%s (%s):%d[%c]",toPrint->name, toPrint->foodGroup, toPrint->calories, toPrint->type);

 	return string;
}

Food * addToFront(Food * theList, Food * toBeAdded)
{
	if (theList == NULL)
	{
		theList = toBeAdded;
		toBeAdded->next = NULL;
		return theList;
	}
	else
	{
		toBeAdded->next = theList;
		theList = toBeAdded;
		return theList;
	}
}

Food * addToBack(Food * theList, Food * toBeAdded)
{
	if(theList != NULL)
	{
		Food * temp;
		temp = theList;
		while(temp->next!= NULL)
		{
			temp = temp->next;
		}
		temp->next = toBeAdded; 
		toBeAdded->next = NULL;
		return theList;
	}
	else
	{
		toBeAdded->next = NULL;
		theList = toBeAdded;
		return theList;
	}
}

Food * removeFromFront(Food * theList)
{
	Food * temp;
	temp = theList;
	theList = temp->next;

	return theList;
}

Food * getFirstItem(Food * theList)
{
	return theList; 
}

Food * removeFromBack(Food * theList)
{
	Food * temp;
	Food * prev;
	temp = theList; 

	while(temp->next != NULL)
	{
		prev = temp;
		temp = temp->next;
	}
	prev->next = NULL;
	return theList;
}
Food * getLastItem(Food * theList)
{
	Food * temp;
	temp = theList;

	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	return temp;
}


void destroyRecord(Food * toDie)
{
	if(toDie != NULL)
	{
		free(toDie->name);
		free(toDie->foodGroup);
	}
}

void destroyList(Food * theList)
{
	Food * temp;
	while(theList != NULL)
	{
		temp = theList;
		theList = temp->next;
		destroyRecord(temp);
		free(temp);
	}
}

int isEmpty(Food * theList)
{
	if(theList == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

void printList(Food * theList)
{
	Food * temp;
	temp = theList;
	while(temp)
	{
		printf("%s (%s):%d[%c]\n",temp->name, temp->foodGroup, temp->calories, temp->type);	
		temp = temp->next;
	}
}
