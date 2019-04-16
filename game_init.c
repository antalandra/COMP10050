/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
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
            board[i][j].stack = NULL;
        }
    }
}


 /*
 * This function creates players for the first time
 *
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 */
int initialize_players(Player players[]){

    int numPlayer = 0; //initialising number of players to zero at beginning of the game

    //asking how many players will play and storing value in variable player_num
    printf("Please enter the number of players (between 2 and 6): ");
    scanf("%d", &numPlayer);

    //checking if the number of players is valid
    if(numPlayer < 2 || numPlayer > 6)
    {
        //error message when player number is too small or too high
        printf("Sorry, the game can accommodate only between 2 and 6 players.\n"
               "Please start again.\n");
        return -1;
    }

    else
    {
        //going through the number of players to fill in their names and color choices
        for (int pl = 0; pl < numPlayer; ++i)
        {
            printf("\nPlease enter name of player %d: ", pl+1);
            scanf("%s", &players[pl].player_name); //scanning name of player

            //asking user to pick color they wish to use
            printf("Please pick the color you wish to play with:\n"
                   "Input 1 for Red.\n"
                   "Input 2 for Blue.\n"
                   "Input 3 for Green\n"
                   "Input 4 for Yellow.\n"
                   "Input 5 for Pink.\n"
                   "Input 6 for Orange.\n");

            //scanning choice into a variable
           int color_choice;
           scanf("%d", &color_choice);
           color_choice--;  //decrementing choice as ENUMS are ordered from zero
           players[pl].col = color_choice;    //placing color choice in corresponding member of struct of that player

            //ASK IF THIS IS CORRECT FOR IMPLEMENTATION

            //checking if color is already taken

           /*if (players[pl-1].col == players[pl].col)
           {
               //error message to screen if color is already taken
               printf("Each player must have a different color!\n"
                      "Please pick a different color.\n
                       "Input 1 for Red.\n"
                       "Input 2 for Blue.\n"
                       "Input 3 for Green\n"
                       "Input 4 for Yellow.\n"
                       "Input 5 for Pink.\n"
                       "Input 6 for Orange.\n");
                //scanning new color choice
                scanf("%d", &color_choice);
                players[pl].col = color_choice;
           }
        }
*/
        return numPlayer;

}




