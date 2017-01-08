****************************************************
Ahmed Mousa		0927129
CIS 2500		Assignment 1
January 24/2016
****************************************************


************
Compilation
************
To compile this program execute the following command while in A1 directory:
gcc src/main.c src/functions.c src/parsing.c -Iinclude -Wall -std=c99 -o program


***********************
Running the program(s)/Usage
***********************
To run the program type the following command from the root directory of the assignment:
./program assets/temp.txt assets/data.txt assets/output.txt

Program will scan data file for variables and values, move to template file to replace variables between {} with corresponding values. Prints replaced variables to an output file.


***********************
Testing
***********************
The following files have been tested in order to minimize and identify errors in the program:
Syntax:(template file, data file, output file) respectively 
1. assets/temp.txt assets/data.txt assets/output.txt:
   obtained from A1 example to check basic criteria has been met

2. assets/Testing/test1.txt assets/Testing/test2.txt assets/Testing/output.txt
   Used to make sure MISSING_DATA is inputted correctly.

3. assets/Testing/test3.txt assets/Testing/test4.txt assets/Testing/output.txt
   Used to illustrate known limitations that syntax like: {variable1}{variable2} 
   causes program to output missing data even though it is in data file.

4. assets/Testing/test3.txt assets/Testing/test5.txt assets/Testing/output.txt 
   Used to illustrate segmentation fault as a result of an extra newline in data file

5. assets/Testing/test6.txt assets/Testing/test7.txt assets/Testing/output.txt 
   To make sure program can handle multiple variables in 1 line.

6. assets/Testing/test6.txt assets/Testing/test8.txt assets/Testing/output.txt
   To make sure program exits if variable is greater than 25 characters.

7. assets/Testing/test6.txt assets/Testing/test9.txt assets/Testing/output.txt
   To make sure program exits if value is greater than 25 characters.

8. assets/Testing/test10.txt assets/Testing/test7.txt assets/Testing/output.txt
   To make sure program exits if Line in template file is greater than 255 characters.


	
*****************
Known Limitations
*****************
This program has quite a few limitations even though it has error checking. Some of the limitations are:
- IMPORTANT: there must be a space or any character between two variables or line will output different than expected. {variable1}{variable2} causes program to behave 
  different than expected.
   
- If the user enters a variable name/value greater than or equal to 25 characters the program simply exits after displaying an appropriate error message.
 
- The same goes for when if the template file contains a line greater than 255 characters. 

- If a variable in the template file is not included in the data file, the program just puts “MISSING_DATA” as a replacement instead of asking the user what they want as a replacement.

- The program can only set variables correctly if they are just 1 per line, and separated by the equal sign without space (variableName=variable value<newline>).  Also, there must be a newline at the end of the data file or the last variable will be missing its last letter once its being replaced in the template file.

- If an extra newline is left in the data file segmentation fault will occur. 
  Only one newline should be at the end of the data file as specified. 

****************
References
****************

Information about the function strtok() was obtained from the following websites on January 23, 2016:
1. https://www.youtube.com/watch?v=o_RKfLrmCEs
2. http://www.cplusplus.com/reference/cstring/strtok/ 

Information about the function fputs() was obtained from the following site on January 23, 2016:
1. http://www.tutorialspoint.com/c_standard_library/c_function_fputs.htm 
