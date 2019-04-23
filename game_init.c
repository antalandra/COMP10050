#include "game_init.h"
#include "game_logic.h"
#include <stdio.h>
/*
 * This function creates the board for the first time
 *
 * Input: board - a 6x9 array of squares
 *
 */
void initialize_board(Square board[NUM_ROWS][NUM_COLUMNS]){

    for (int i =0; i< NUM_ROWS; i++){
        for(int j =0; j < NUM_COLUMNS; j++){
            //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
            if((i == 0 && j==3) || (i == 1 && j == 6) || (i ==2 && j ==4)
                    || (i == 3 && j ==5) || (i==4 && j==2) || (i==5 && j==7)){
                board[i][j].type = OBSTACLE;
            } else{
                //creates a normal square otherwise
                board[i][j].type = NORMAL;
            }
            board[i][j].top_stack = NULL;
        }
    }
}

 /*
 * This function creates players for the first time
 *
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 */
int initialize_players(Player players[])
{

    int numPlayer = 0; //initializing number of players to zero at beginning of the game

    //asking how many players will play and storing value in variable numPlayer
    printf("\nPlease enter the number of players (between 2 and 6): ");
    scanf("%d", &numPlayer);

    //checking if the number of players is valid
    if (numPlayer < 2 || numPlayer > 6)
    {
        //error message when player number is too small or too high
        printf("\nSorry, the game can accommodate only between 2 and 6 players.\n"
               "Please start again.\n");
        return 0;
    }

    else
    {
        //declaring variable that will hold integer value for color choice
        int color_choice;
        //going through the number of players to fill in their names and color choices
        for (int pl = 0; pl < numPlayer; ++pl)
        {
            printf("\nPlease enter name of player %d: ", pl+1);

            char new_line;  //creating a variable to store the new line in the buffer
            scanf("%c", &new_line); //storing the new line stored in the buffer

            gets(players[pl].player_name); //scanning name of player

            //asking user to pick color they wish to use
            printf("\nPlease pick the color you wish to play with:\n"
                   "Input 1 for Red.\n"
                   "Input 2 for Blue.\n"
                   "Input 3 for Green\n"
                   "Input 4 for Yellow.\n"
                   "Input 5 for Pink.\n"
                   "Input 6 for Orange.\n");

            //scanning choice into a variable
           scanf("%d", &color_choice);
           color_choice--;  //decrementing choice as ENUMS are ordered from zero
           players[pl].col = color_choice;    //placing color choice in corresponding member of structure of that player

        }

        //checking if the color has been chosen already by another user
        while (checkIfChosen(players, numPlayer) == 1)
        {
            //asking users to input their colors again when the return value of function that checks color validity is 1
            printf("Each player must have a different color!\n");
            for(int pl = 0; pl < numPlayer; ++pl)
            {
                printf("\nPlayer %s, please enter a color.\n"
                       "Input 1 for Red.\n"
                       "Input 2 for Blue.\n"
                       "Input 3 for Green\n"
                       "Input 4 for Yellow.\n"
                       "Input 5 for Pink.\n"
                       "Input 6 for Orange.\n", players[pl].player_name);

                scanf("%d", &color_choice); //scanning color choice again
                color_choice--;  //decrementing as ENUM colors start from zero
                players[pl].col = color_choice; //setting the color choice in the corresponding member of structure of that player
            }
        }
    }

        return numPlayer;   //returning the number of players
}
