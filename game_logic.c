/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include "game_logic.h"
#include <stdio.h>
#include <stdlib.h>

void printLine();

/*
 * Returns the first letter associated with the color of the token
 *
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 */
char print_token(Token *t){
    if((*t).col== PINK) return 'P';
    if((*t).col== RED) return 'R';
    if((*t).col== BLUE) return 'B';
    if((*t).col== GREEN) return 'G';
    if((*t).col== ORANGE) return 'O';
    if((*t).col== YELLOW) return 'Y';
    return '\0';
}

/*
 * Prints the board
 *
 * Input: the board to be printed.
 */
void print_board(Square board[NUM_ROWS][NUM_COLUMNS]){
    printf("                THE BOARD\n");
    for(int i =0; i < NUM_ROWS; i++){

        //prints an horizontal line
        printLine();
        //prints the row number
        printf(" %d ", i);
        char c = '\0' ;
        //if the square (i,j) is occupied,
        //c is assigned the initial of the color of the token that occupies the square
        for (int j = 0; j < NUM_COLUMNS; j++){
            if(board[i][j].top_stack != NULL){
                c = print_token(board[i][j].top_stack);
            }
            //if the square (i,j) is empty
            else{
                //c is assigned 'X' if the square represents an obstacle
                if(board[i][j].type == OBSTACLE)
                    c = 'X';
                //c is assigned an empty space otherwise
                else c = ' ';
            }
            printf("| %c ", c);
        }
        printf ("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     0   1   2   3   4   5   6   7   8\n");
}

void printLine(){
  printf("   -------------------------------------\n");
}


//checking if the color chosen by player has been already taken by another player
int checkIfChosen(Player players[], int numPlayer)
{
    for(int cur_pl=0; cur_pl<numPlayer; ++cur_pl)
    {
        for(int nex_pl=cur_pl+1; nex_pl<numPlayer; ++nex_pl)
            {
                if (players[nex_pl].col == players[cur_pl].col)
                {
                   return 1;
                }
                else
                {
                    return 0;
                }
            }
    }
}

/*
 * Place tokens in the first column of the board
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */

void place_tokens(Square board[NUM_ROWS][NUM_COLUMNS], Player players[], int numPlayers){

    int tok = 0;    //initialising token number to zero
    while (tok !=4)
    {
        int pl = 0; //initialising player number to zero
        while ( pl != numPlayers)
        {
            int row_num;
            printf("Player %d: place token %d on a row of your choice from 0 to 5: ", pl+1, tok+1);
            scanf("%d", &row_num);  //scan row number from user

            Token *new_tok = malloc(sizeof(Token));
            new_tok->col = players[pl].col; //adding the colour of the player to the token
            new_tok->belowPtr = board[row_num][0].top_stack;
            board[row_num][0].top_stack = new_tok;  //new tok or newPtr???

            print_token(board[row_num][0].top_stack);
            print_board(board);
            pl++;   //incrementing player number
        }

        tok++;  //incrementing token number
    }

}


// returns the name of the color from an enum Color type
char *color_name(enum color color) {
    switch(color) {
        case 0: return "red";
        case 1: return "blue";
        case 2: return "green";
        case 3: return "yellow";
        case 4: return "pink";
        case 5: return "orange";
        default: return "color blind";
    }
}

// helper function to move any token from one location to another
void move_token(Square board[][NUM_COLUMNS], int cur_row, int cur_col, int new_row, int new_col) {
    Token *token = board[cur_row][cur_col].top_stack; // token we want to relocate
    board[cur_row][cur_col].top_stack = token->belowPtr; // remove the token

    // below is what's now the top token at the new location
    token->belowPtr = board[new_row][new_col].top_stack;
    board[new_row][new_col].top_stack = token; // place token on top of the new location
}

/*
 * Place tokens in the first column of the board
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
void play_game(Square board[NUM_ROWS][NUM_COLUMNS], Player players[], int numPlayers) {
    // for each player
    for (int i = 0; i < numPlayers; ++i) {
        printf("\nPlayer's turn: %s(%s)", players[i].player_name, color_name(players[i].col));
        // take his turn:
        // roll die and tell the player his die roll
        int die = rand() % 6;
        printf("You rolled: %d\n", die);

        // ask the player if he wants to move sideways
        int answer;
        puts("Do you want to move sideways? (1 for yes, 0 for no)");
        scanf("%d", &answer);

        // if he says yes
        if (answer == 1) {
            // ask which token he wants to move (in coordinates) (it must be his token)
            // and in which direction (up or down)
            // move the token
        }

        // once you're done with the sideways move
        // ask the player which token does he wants to move according the die result row (it doesn't have to be his token, but it has to be the top one)
        // move the token forward (one column ahead) ONLY IF IT IS NOT ON AN OBSTACLE SQUARE

        // check if he won and break

        // check if obstacles are still pbstacles

        // once the last player took his turn
        if (i == numPlayers - 1) {
            i = -1; // reset to the first player
        }
    }

}

//did this save



