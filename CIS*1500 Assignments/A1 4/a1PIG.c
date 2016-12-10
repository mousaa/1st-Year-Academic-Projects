/**********************
CIS 1500 Assignment 1
Ahmed Mousa
Oct 10/15
THE GAME OF PIG 
Game between 2 playes involving a dice
where players decisions are between 
rolling to gain a higher score or holding to 
protect their score.
***********************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    // function declarations
    srand(time(NULL)); //used to seed the random number generator
    void showDice(int num);

    // variable declarations
    int p1Turn;
    int diceRoll;
    int p1Score;
    int p2Score;
    int p1TurnTotal;
    int p2TurnTotal;
    int p1Temp;
    int p2Temp;
    int gameTotal;
    char plyrDecision;

    // variable initialization
    diceRoll = (rand() % 6) + 1;
    p1Turn = 1;
    p1Score = 0;
    p2Score = 0;
    p1TurnTotal = 0;
    p2TurnTotal = 0;
    p1Temp = 0;
    p2Temp = 0;
    gameTotal = 0;
    plyrDecision = '-';

    // GAME INTRO
    printf("WELCOME TO THE GAME OF PIG\n");
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ \n\n");
    printf("Enter the game total you would like to play to (Enter a positive integer)\n");
    scanf("%d", &gameTotal);
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ \n\n");
    printf("Player 1 score is (%d)\n", p1Score);
    printf("Player 2 score is (%d)\n", p2Score);
    printf("First player to reach %d wins!\n", gameTotal);
    printf("Good luck, you may begin!\n");
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ \n\n");
    printf("Starting with player 1:\n");

    // ALGORITHIM IMPLEMENTATION
    while (p1Turn == 1)
    {
        /* Loop for starting with player 1s turn that ends
        when p1turn is false (0)*/
        printf("(r)oll or (h)old?\n>");
        scanf(" %c", &plyrDecision); /*http://stackoverflow.com/questions/17917638/it-prints-the-printf-statement-twice*/

        if ((plyrDecision == 'r') || (plyrDecision == 'R'))
        {
            // Dice is rolled and user can see it
            // random number from 1-6 generated
            diceRoll = (rand() % 6) + 1;
            showDice(diceRoll);
            printf("\n");
            p1Temp += diceRoll; // temp score incremented as dice rolls
            if(diceRoll != 1)
            {
                p1TurnTotal += diceRoll;
                printf("Turn total : %d\n\n", p1TurnTotal);
                /* Temporary score goes back to 0 at every turn - have to add to current score*/
                if (p1Temp + p1Score >= gameTotal)
                {
                    printf("Player 1 wins with a score of %d!\n\n\n", p1Score + p1Temp);
                    printf("     ----GAME OVER----\n\n");
                    return 0;  // GAME ENDS
                }
            }
                else  // Dice rolls a 1
                {
                    p1TurnTotal = 0; // turn total goes back to 0 for next turn
                    p1Temp = 0; //Temporary score goes to 0 so nothing adds to actual score
                    printf("You rolled a pig! lose a turn\n");
                    printf("Player 1 score = %d\n", p1Score);
                    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ \n\n\n");
                    printf("Player 2's turn!(score = %d)\n", p2Score);
                    p1Turn = 0; // PLAYER 2'S TURN
                }
        }
        else  if ((plyrDecision == 'h') || (plyrDecision == 'H')) // User holds
        {
            p1Score += p1Temp; // temp score stored to the actual score
            p1Temp = 0;
            printf("(HOLD)PLAYER 1 Score at %d\n", p1Score);
            printf("_ _ _ _ _ _ _ _ _ _ _ _ _ \n\n\n");
            printf("Player 2's turn!(score = %d)\n", p2Score);
            p1TurnTotal = 0;
            p1Turn = 0;
        }

        while (p1Turn == 0)
        {
            /* Loop starts for player 2 once it recieves that p1Turn is false.
            variables/conditions in this loop do the same thing as player 1
            only difference is the name.*/
            printf("(r)oll or (h)old?\n>");
            scanf(" %c", &plyrDecision);
            if ((plyrDecision == 'r') || (plyrDecision == 'R'))
            {
                diceRoll = (rand() % 6) + 1;
                showDice(diceRoll);
                printf("\n");
                p2Temp += diceRoll;
                if (diceRoll != 1)
                {
                    p2TurnTotal += diceRoll;
                    printf("Turn total : %d\n\n", p2TurnTotal);
                    if ( p2Temp + p2Score >= gameTotal)
                    {
                        printf("Player 2 wins with a score of %d!\n\n\n", p2Score + p2Temp);
                        printf("    ----GAME OVER----\n\n");
                        return 0;
                    }
                }
                else if (diceRoll == 1)
                {
                    p2TurnTotal = 0;
                    p2Temp = 0;
                    printf("You rolled a pig! lose a Turn\n");
                    printf("Player 2 score = %d\n", p2Score);
                    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ \n\n\n");
                    printf("Player 1's turn! (score = %d)\n", p1Score);
                    p1Turn = 1;
                }
            }
            else if ((plyrDecision == 'h') || (plyrDecision == 'H'))
            {
                p2Score += p2Temp;
                p2Temp = 0;
                printf("(HOLD)PLAYER 2 score at %d\n", p2Score);
                printf("_ _ _ _ _ _ _ _ _ _ _ _ _ \n\n\n");
                printf("Player 1's turn! (score = %d)\n", p1Score);
                p2TurnTotal = 0;
                p1Turn = 1;
            }
        }
    }

    return 0;
}

/*****
showDice : Showes the dice based on num rolled
In : Numbers from 1-6 (int num)
Out : None
Post : "Dice rolls a" and a display of the dice based on num rolled prints
*****/
void showDice(int num)
{
    printf("Dice rolls a \n");
    switch (num)
    {
        case 1:
            printf("+-------+\n");
            printf("|       |\n");
            printf("|   o   |\n");
            printf("|       |\n");
            printf("+-------+\n");
            break;

        case 2:
            printf("+-------+\n");
            printf("| o     |\n");
            printf("|       |\n");
            printf("|     o |\n");
            printf("+-------+\n");
            break;

        case 3:
            printf("+-------+\n");
            printf("| o     |\n");
            printf("|   o   |\n");
            printf("|     o |\n");
            printf("+-------+\n");
            break;

        case 4:

            printf("+-------+\n");
            printf("| o   o |\n");
            printf("|       |\n");
            printf("| o   o |\n");
            printf("+-------+\n");
            break;

        case 5:
             printf("+-------+\n");
             printf("| o   o |\n");
             printf("|   o   |\n");
             printf("| o   o |\n");
             printf("+-------+\n");
             break;

        case 6:
            printf("+-------+\n");
            printf("| o   o |\n");
            printf("| o   o |\n");
            printf("| o   o |\n");
            printf("+-------+\n");
            break;
    }
}

