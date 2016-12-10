// for linked list.c 
// cant submit it though u have to delete it 
//only need main for part two.

#include "linkedList.h"
#include "foodTracker.h"
#include "checkFile.h"

int main(int argc, char* argv[])
{
	FILE* file;

    checkArgc(argc);//make sures argc = 1
	file = fopen(argv[1], "r");
    checkFile(file); //check return value of file

    foodTracker(file);
	fclose(file);

	return 0;
}
