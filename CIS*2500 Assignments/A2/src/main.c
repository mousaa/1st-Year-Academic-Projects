#include "parsing.h" //parseLevel function
#include "checkFile.h" //for checkArgc, checkFile
#include "curses.h"

/*
 *
 * main
 * function starts entire prorgam takes in command line arguments as parameters
 * Accepts 1 command line arguments: level file
 * IN: int (argument count), char* (argument vectors)
 * OUT: int (0 if everything went well, non-zero(1)  indicates error
 * POST: Parses level file and stores all information in struct
 * 		 according to the room number. terminal control is then
 *		 moved to ncurses where the game starts.
 */

int main(int argc, char* argv[])
{
	FILE* file;
	Room* room;

    checkArgc(argc);//make sures argc = 2
	file = fopen(argv[1], "r");
    checkFile(file); //check return value of file

	room = parseLevel(file);
	fclose(file);

	startGame(room); //initialize ncurses
	gameLoop(room);
	endGame(room); //deinitializes ncurses and prints gold count

	return 0;
}
