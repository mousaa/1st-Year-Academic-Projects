#include "functions.h" //for checkArgc,checkFile,closeFile,
#include "parsing.h"   //for parseData,parseTemplate

/**
 * main
 * function starts entire prorgam takes in command line arguments as parameters
 * Accepts 3 command line arguments: Template, data and output file respectively
 * IN: int (argument count), char* (argument vecotrs)
 * OUT: int (0 if everything went well, non-zero(1)  indicates error
 * POST: Reads vaiable names and values from data file, then moves on to read
 *       template file which contains variables which will be replaced with their 
 *       values to a third output file
 */

int main(int argc, char* argv[])
{
    // variable declarations
	FILE* fp1;
	FILE* fp2;
	FILE* fp3;
	int dataVars;

    //variable initilization
	dataVars = 0;


	checkArgc(argc); //make sures argc = 4. Exits if not.

    /*
     Opens template and data file for  reading.
     Output file for writing
     checkFile make sures they opened successfully
     Program exits if not.
    */
    fp1 = fopen(argv[1], "r");
    checkFile(fp1, 1);
	fp2 = fopen(argv[2], "r");
    checkFile(fp2 , 2);
    fp3 = fopen(argv[3], "w");
    checkFile(fp3, 3);

    /*
     Begins by parsing data file
     Setting variable to value
     returns # of variables found.
     Parses template file next
     and outputting replaced words
     to output file.
    */
    dataVars = parseData(fp2);
	parseTemplate(fp1, fp3);

    printf("   ***Total Variables in Data file***\n");
	printf("\tData File : %d\n\n", dataVars);

	closeFiles(fp1,fp2,fp3); //closes all files.

    return 0;
}
