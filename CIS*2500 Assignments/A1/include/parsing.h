#ifndef _MOUSAA_PARSING_
#define _MOUSAA_PARSING_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * parseData
 * Accepts data file as parameter, parses it into variables and values
   by utilizing function (setValue) from storeval.c (setValue: variable to value)
 * IN: file pointer specifically the data file
 * OUT: returns integer value corresponding to the number of variables found in
        data file
 * POST: Parses the data file line by line setting variable name to value
 */
int parseData(FILE* ptr);

/**
 * parseTemplate
 * Accepts template file as first parameter, and output file as second
   Parses each line in template once done prints it to output file
 * IN: two file pointers (template and output files)
 * OUT: None (void)
 * POST: Searches template file for variables set from data file.
         Once found, Replaces variable with value and prints to new file
         (output file)
        Once done, prints to stdout the end of the program message, which
        includes number of variables found in Template file, successful and
        failed Replacements.
 */

void parseTemplate(FILE* ptr1, FILE* ptr2);

#endif
