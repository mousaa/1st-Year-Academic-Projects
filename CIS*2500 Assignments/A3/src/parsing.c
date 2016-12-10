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
    //hero inventory stored in room 0
    //doesnt matter which room to store in. 
    room[0].hero.capacity = 0;
    room[0].hero.potion = 1; 
    room[0].hero.health = 50;
    room[0].hero.attackRate = 5;

    //flags for opening door
    room[0].ctrX = 0;
    room[0].ctrY = 0;
    room[0].ctrZ = 0;


    room[0].trollCycle = 1;


    //initial monster states
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            room[i].aquator[j].health = 5;
            room[i].aquator[j].attackRate = 1;

            room[i].zombie[j].health = 15;
            room[i].zombie[j].attackRate = 5;
            room[i].zombie[j].cycle = 1;

            room[i].bat[j].health = 2;
            room[i].bat[j].attackRate = 5;
            room[i].bat[j].cycle = 1;

            room[i].snake[j].health = 5;
            room[i].snake[j].attackRate = 5;
            room[i].snake[j].cycle = 1;
        }
    }


    char line[150];
    int roomNum = 0; //room number
    while (fgets(line,sizeof(line), f) != NULL)
    {
        int i = 0; //counter for items array
        int dNum = 0; // counter for door array
        char* token;
        int j = 0; //counter for monsters
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
                case 'W': //rare weapon
                {
                    room[roomNum].elements[i].type = '(';
                    sscanf(token, "W%d,%d", &room[roomNum].elements[i].posY, &room[roomNum].elements[i].posX);
                    i++;
                    break;
                }
                case 'm': //monster, randomly stored
                {
                    int temp;
                    temp = (rand() % 20);
                    switch (temp)
                    {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                        case 9:
                        room[roomNum].elements[i].type = 'A';
                        break;

                        case 13:
                        case 14:
                        case 10:
                        room[roomNum].elements[i].type = 'B';
                        room[roomNum].elements[i].cycleCtr = 0;
                        room[roomNum].elements[i].batCtr = 0;

                        break;

                        case 16:
                        case 17:
                        case 11:
                        room[roomNum].elements[i].type = 'S';
                        room[roomNum].elements[i].cycleCtr = 0;
                        break;

                        case 18:
                        case 19:
                        case 15:
                        case 12:
                        room[roomNum].elements[i].type = 'Z';
                        room[roomNum].elements[i].cycleCtr = 0;

                        break;
                    }
                    sscanf(token, "m%d,%d", &room[roomNum].elements[i].posY, &room[roomNum].elements[i].posX);
                    i++;
                    j++;
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

                    room[roomNum].troll.health = 50;
                    room[roomNum].troll.attackRate = 5;

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
