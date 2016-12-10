/**
 * see foodTracker.h for complete function definitions
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"
#include "foodTracker.h"
#include "stats.h"
void foodTracker(FILE* f)
{
	char line[255];
	Food* head;
	head = NULL;
	while(fgets(line,255, f) != NULL)
	{
		Food* node;
		char* token;
		char* name;
		char* foodGroup;
		int calories;
		char type;
		token = strtok(line, ",");
		name = malloc(strlen(token) + 1);
		strcpy(name, token);


		token = strtok(NULL, ",");
		foodGroup = malloc(strlen(token) + 1);
		strcpy(foodGroup, token);


		token = strtok(NULL,",");
		calories = atoi(token);

		token = strtok(NULL,",");
		type = token[0];


		node = createRecord(name,foodGroup,calories,type);
		free(name);
		free(foodGroup);

		if(node != NULL)	
		{

			if(node->type == 'j')
			{
				head = addToBack(head,node);
			}
			else if(node->type == 'h')
			{
				head = addToFront(head,node);
			}
		}
		else
		{
			
		}
	}
		printStats(head);
		printList(head);
	    destroyList(head);
} 
