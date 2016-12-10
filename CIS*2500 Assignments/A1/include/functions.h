#ifndef _MOUSAA_FUNCTIONS_
#define _MOUSAA_FUNCTIONS_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
 * checkArgc
 * Accepts a value (argument count of program)
 *
 * IN: integer (argument count from command lines of program)
 * OUT: None (void)
 * POST: Checks if Argument count = 4.
 */
void checkArgc(int x);

/**
 * checkFile
 * Accepts a file pointers, and values ranging from 1-3.
 * Values correspond to argv[1],argv[2],argv[3] respectively
 * IN: file pointer(template file, data file or outputfile).
       integer ranging from 1-3. 1 for template, 2 for data file,
       3 for outputfile.
 * OUT: None (void)
 * POST: checks if the file specified in function call opened successfully
         prints appropriate message regarding wether the specific file
         (template, data, ouput) did not open successfully.
 * ERRORS: must enter digit from 1-3 as second parameter to know which
           file has issues
 */
void checkFile(FILE* ptr, int x);

/**
 * closeFiles
 * Accepts any 3 file pointers to close
 * IN: 3 file pointers to close. In this case:template file, data file and
       outputfiles
 * OUT: None (void)
 * POST: Closes the previously opened files
 */
void closeFiles(FILE* ptr1, FILE* ptr2, FILE* ptr3);

/**
 * endMessage
 * accepts 2 integers, total variables found in template and failed replacements
 * IN: int tempVars, int fail.
 * OUT: None (void)
 * POST: prints message including the total variables found in template file
         and failed replacements. Uses subtraction between the two, to find the
        number of successful variables.
 **/
void endMessage(int tempVars, int fail);

#endif
