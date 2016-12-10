/**
 * see functions.h for complete function definitions
 *
 */

#include "functions.h"

void checkArgc(int x)
{
	if (x != 4) //argc for this project must be 4
	{
        printf("\n\n   ***EXECUTION UNSUCCESSFUL*** \n\n");
		printf("*Invalid # of arguments*\n");
		printf("Input the program name followed by:\n");
		printf("Template file, data file, output file\n");
		exit(1);
	}
}

void checkFile(FILE* ptr, int x)
{
    //make sures files opened successfully
    if (ptr == NULL)
        {
			switch(x)
			{
				case 1://opened for "r"
				printf("Problem accessing template file\n");
				break;

				case 2:// "r"
				printf("Problem accessing data file\n");
				break;

				case 3:// "w"
				printf("Problem accessing output file\n");
				break;
			}
            printf("\n\n   ***EXECUTION UNSUCCESSFUL*** \n\n");
			printf("Program will exit now.\n");
			exit(1);
		}
}

void closeFiles(FILE* ptr1, FILE* ptr2, FILE* ptr3)
{
	//closes files
	fclose(ptr1);
	fclose(ptr2);
	fclose(ptr3);
}

void endMessage(int tempVars, int fail)
{
    /*
     * end message with the number of variables in template
     * include successful and failed replacements
     */
    printf("\n\n   ***EXECUTION SUCCESSFUL*** \n\n");
    printf("   ***Total Variables in Template file***\n");
    printf("\tTemplate : %d\n", tempVars);
    printf("\tFailed Replacements : %d\n", fail);
    printf("\tSuccessful Replacements : %d\n\n", tempVars-fail);
}
