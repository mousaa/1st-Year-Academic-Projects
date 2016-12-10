#ifndef _MOUSAA_CHECKFILE_
#define _MOUSAA_CHECKFILE_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * checkArgc
 * Accepts a value (argument count of program)
 * IN: integer (argument count from command lines of program)
 * OUT: None (void)
 * POST: Checks if Argument count = 2.
 */
void checkArgc(int x);

/**
 * checkFile
 * Accepts a file pointers which corresponds to the level file
 * IN: file pointer(level file)
 * OUT: None (void)
 * POST: checks if the file specified in function call opened successfully
 prints appropriate message if it did not open successfully/ not found.
 */
void checkFile(FILE* ptr);


#endif
