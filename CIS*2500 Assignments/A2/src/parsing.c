/**
 * see parsing.h for complete function definitions
 *
 */
#include "parsing.h"

Room* parseLevel(FILE* f)
{

    Room* room;
    srand(time(NULL));
    room = malloc(sizeof(Room) * 6); //space for 6 rooms

    if (room == NULL)
    {
        printf("No more memory\n");
        printf("program will exit now\n");
        exit(1);
    }

    char line[150];
    int roomNum = 0; //room number
    while (fgets(line,sizeof(line), f) != NULL)
    {
        int i = 0; //counter for items array
        int dNum = 0; // counter for door array
        char* token;

        //first one always dimensions of room
        token = strtok(line, " ");
        sscanf(token, "%dX%d", &room[roomNum].yDim, &room[roomNum].xDim);
        while (token != NULL)
        {
            switch (token[0])
            {
                case 'd': //door
                {
                    sscanf(token, "d%c%d", &room[roomNum].door[dNum].side, &room[roomNum].door[dNum].pos);
                    dNum++;
                    break;
                }
                case 'h': //hero
                {
                    room[roomNum].elements[i].type = '@';
                    sscanf(token, "h%d,%d", &room[roomNum].elements[i].posY, &room[roomNum].elements[i].posX);
                    i++;
                    break;
                }

                //stairs
                case 'z':
                {
                    room[roomNum].elements[i].type = '<';
                    sscanf(token, "z%d,%d", &room[roomNum].elements[i].posY, &room[roomNum].elements[i].posX);
                    i++;
                    break;
                }
                case 'a':
                {
                    room[roomNum].elements[i].type = '>';
                    sscanf(token, "a%d,%d", &room[roomNum].elements[i].posY, &room[roomNum].elements[i].posX);
                    i++;
                    break;
                }
                case 'g': //small gold
                {
                    room[roomNum].elements[i].type = '*';
                    sscanf(token, "g%d,%d", &room[roomNum].elements[i].posY, &room[roomNum].elements[i].posX);
                    i++;
                    break;
                }
                case 'G': //big gold
                {
                    room[roomNum].elements[i].type = '8';
                    sscanf(token, "G%d,%d", &room[roomNum].elements[i].posY, &room[roomNum].elements[i].posX);
                    i++;
                    break;
                }
                case 'w': //weapon
                {
                    room[roomNum].elements[i].type = ')';
                    sscanf(token, "w%d,%d", &room[roomNum].elements[i].posY, &room[roomNum].elements[i].posX);
                    i++;
                    break;
                }
                case 'W': //rare weapin
                {
                    room[roomNum].elements[i].type = '(';
                    sscanf(token, "W%d,%d", &room[roomNum].elements[i].posY, &room[roomNum].elements[i].posX);
                    i++;
                    break;
                }
                case 'm': //monster, randomly stored
                {
                    int temp;
                    temp = (rand() % 4) + 1;
                    switch (temp)
                    {
                        case 1:
                        room[roomNum].elements[i].type = 'A';
                        break;
                        case 2:
                        room[roomNum].elements[i].type = 'B';
                        break;
                        case 3:
                        room[roomNum].elements[i].type = 'S';
                        break;
                        case 4:
                        room[roomNum].elements[i].type = 'Z';
                        break;
                    }
                    sscanf(token, "m%d,%d", &room[roomNum].elements[i].posY, &room[roomNum].elements[i].posX);
                    i++;
                    break;
                }
                case 'e': //equipment
                {
                    room[roomNum].elements[i].type = ']';
                    sscanf(token, "e%d,%d", &room[roomNum].elements[i].posY, &room[roomNum].elements[i].posX);
                    i++;
                    break;
                }
                case 'M': //strong monster
                {
                    room[roomNum].elements[i].type = 'T';
                    sscanf(token, "M%d,%d", &room[roomNum].elements[i].posY, &room[roomNum].elements[i].posX);
                    i++;
                    break;
                }
                case 'p': //potion
                {
                    room[roomNum].elements[i].type = '!';
                    sscanf(token, "p%d,%d", &room[roomNum].elements[i].posY, &room[roomNum].elements[i].posX);
                    i++;
                    break;
                }
                default:
                {
                    break;
                }
            }
            token = strtok(NULL, " "); //gets next string as long as its not end of line (null)
        }
        //end of current line
        roomNum++; //to count which room elements going in. room[0]++ = room[1]..
    }
    return room;
}
