/**
 * see parsing.h for complete function definitions
 *
 */
#include "parsing.h"
#include "storeval.c"//for setValue and getValue
#include "functions.h"

int parseData(FILE* ptr)
{
    // variable declarations
    char line[255];
    char* variable;
	char* value;
	char* token;
	int dataVars;
    int errorCheck;

    // variable initilizations
    dataVars = 0; //tracks variables in data file
    errorCheck = 1; //make sure functions from storeval.c did their job correctly

    while (fgets(line, sizeof(line), ptr) != NULL) //reads line by line until EOF
        {
            variable = malloc(sizeof(char));
            value = malloc(sizeof(char));
			if (strlen(line) >= 255) //error check
			{
                printf("\n\n   ***EXECUTION UNSUCCESSFUL*** \n\n");
				printf("ERROR: Line must be less than 255 characters.\n");
				printf("Program will exit now.\n");
				exit(1);
			}
			token = strtok(line, "=");
            /*
             * copies left side of '=' to variable
             * strcpy to overwrite any previous strings in variable.
             */
			strcpy(variable, token);
			if (strlen(variable) >= 25) //error check
				{
                    printf("\n\n   ***EXECUTION UNSUCCESSFUL*** \n\n");
					printf("ERROR: variable names must be less than 25 characters.\n");
					printf("Please change [%s] and try again.\n", variable);
					printf("Program will exit now.\n\n");
					exit(1);
				}
			if (token != NULL)
			{
				token = strtok(NULL, "=");
                /*
                 * copies right side of '=' to value
                 * overwrites any previous strings in value.
                 */
				strcpy(value, token);
				if (strlen(value) >= 25) //error check
				{
                    printf("\n\n   ***EXECUTION UNSUCCESSFUL*** \n\n");
					printf("ERROR: values must be less than 25 characters.\n");
					printf("Please change [%s] and try again\n", value);
					printf("Program will exit now.\n\n");
					exit(1);
				}
			}
			errorCheck = setValue(variable, value); //sets right side to left side.
            /*
             * should return 1 if successful
             */
            if (errorCheck == 0)
            {
                printf("\n\n   ***EXECUTION UNSUCCESSFUL*** \n\n");
                printf("Problem setting up setValue\n");
                printf("Program will exit now\n");
                exit(1);
            }
			dataVars++; //tracks variables in data file.
		}
    free(variable);
    free(value);

    return dataVars;
}

void parseTemplate(FILE* ptr1, FILE* ptr2)
{
    //variable declarations
    char line[256];
    char* temp;
    char* token;
    char* brace;
    int length;
    int i;
    int variables;
    int failed;
    int found;

    //variable initilizations
    variables = 0;//tracks total variables in template file
    failed = 0; //tracks failed replacements

    /** found flag used to track if the token just scanned was
     * between brackets or not
     */
    found = 0;

    while (fgets(line, sizeof(line), ptr1) != NULL) //reads line by line until nothing in file anymore
    {
        length = strlen(line);
        if(length >= 255)//error check to avoid program crashing
        {
            printf("\n\n   ***EXECUTION UNSUCCESSFUL*** \n\n");
            printf("ERROR: Line must be less than 255 characters.\n");
            printf("Program will exit now.\n");
            exit(1);
        }

        brace = strchr(line, '{');
        if (brace != NULL)   //ONLY GOES THROUGH LINE IF FOUND AN OPENING BRACES.
        {
            token  = strtok(line, "{}");
            found = 0; //resets found to 0 once loop ends incase anything went wrong in line(limitations)
            found++; //found opening braces

            /*if variable is very first word, no need to increment flag
             * to keep counter at an even number
             */
            if (brace[0] == '{')
            {
                found--;
            }

            //loops until reaches null terminator at the end of line
            while(token != NULL)
            {
                if(found % 2 == 0)
                {
                    /*found variable
                     * replacing with value
                     */
                    variables++;
                    temp = getValue(token);

                    if (temp == NULL)
                    {
                        //IF NULL THEN VARIABLE DOESNT EXIST IN DATA FILE.
                        failed++;
                        fputs("MISSING_DATA", ptr2);
                    }
                    else
                    {
                        /* null terminates value:
                         * Getvalue adds a newline
                         * at end
                         */
                        int tempLength;
                        tempLength = strlen(temp);
                        temp[tempLength - 1] = '\0';
                        fputs(temp, ptr2); //prints to outputfile value of variable found.
                    }
                }

                /*
                 * found regular string(wasnt between braces) from line
                 * prints to file as it is
                 * no changes made to it
                 */
                else if (found % 2 != 0)
                {
                    fputs(token,ptr2);
                }

                /*
                 * NULL because it picks up where it left off
                 * looks for closing brackets now
                 * since it just found the opening
                 */
                token = strtok(NULL, "{}");

                /*
                 * found end of line
                 * still need to parse token
                 * that was just found
                 */
                if(token == NULL)
                {
                    found--;
                    break;
                }
                else
                {
                    for (i = 0; i<strlen(token); i++)
                    {
                        if (token[i] == '\n')
                        {
                            //variable cant have a newline in it since its in braces
                            found--;
                            break;
                        }
                        else
                        {
                            //this indicates its a variable, increment to keep even
                            found++;
                            break;
                        }
                    }
                }
            }
        }
        else if (brace == NULL) //puts line as it is if there is no opening brace '{'
        {
            fputs(line,ptr2);
        }
    }
    /*
     * prints end message including:
     * 1. successful execution
     * 2. # of template variables, # of replaced or not
     */
    endMessage(variables,failed);
}
