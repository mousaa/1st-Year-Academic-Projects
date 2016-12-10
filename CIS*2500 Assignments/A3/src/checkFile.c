/**
 * see checkFile.h for complete function definitions
 *
 */

#include "checkFile.h"

void checkArgc(int x)
{
    if (x != 2) //argc for this project must be 2
    {
        printf("*Invalid # of arguments*\n");
        printf("Input the program name followed by level file\n");
        printf("Program will exit now.\n");
        exit(1);
    }
}

void checkFile(FILE* ptr)
{
    //make sures file opened successfully
    if (ptr == NULL)
    {
        printf("\n****ERROR****\n");
        printf("Level file provided does not exist.\n");
        printf("Program will exit now.\n\n");
        exit(1);
    }
}
