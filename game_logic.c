/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include "game_logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    //looking at each player's color and comparing it to every other player's color
    for(int cur_pl=0; cur_pl<numPlayer; ++cur_pl)
    {
        for(int nex_pl=cur_pl+1; nex_pl<numPlayer; ++nex_pl)
            {
                if (players[nex_pl].col == players[cur_pl].col)
                {
                   return 1;    //returning 1 to calling function when two/more players have the same color
                }
                else
                {
                    return 0;   //returning to calling function when each player has a different color
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

    int tok = 0;    //initializing token number to zero
    while (tok !=4)
    {
        int pl = 0; //initializing player number to zero
        while ( pl != numPlayers)
        {
            int row_num;
            printf("Player %s: place token %d on a row of your choice from 0 to 5: ", players[pl].player_name, tok+1);
            scanf("%d", &row_num);  //scan row number from user

            Token *new_tok = malloc(sizeof(Token)); //creating a pointer to the new token with the size of the Token structure on the heap
            new_tok->col = players[pl].col; //adding the color of the player to the token
            new_tok->belowPtr = board[row_num][0].top_stack;    //making the top of the stack as the token below the new token
            board[row_num][0].top_stack = new_tok;  //making new token the top of the stack

            print_token(board[row_num][0].top_stack);   //adding the top of the stack(token on top) to the board in the corresponding square
            print_board(board); //printing the board after each token placement
            pl++;   //incrementing player number
        }

        tok++;  //incrementing token number
    }

}


// returns the name of the color from an enum Color type
char *color_name(enum color color) {
    switch(color) {
        case 0: return "Red";
        case 1: return "Blue";
        case 2: return "Green";
        case 3: return "Yellow";
        case 4: return "Pink";
        case 5: return "Orange";
        default: return "NoColor";
    }
}

// function that moves any token from one location to another
void move_token(Square board[][NUM_COLUMNS], int cur_row, int cur_col, int new_row, int new_col) {
    Token *token = board[cur_row][cur_col].top_stack; // token we want to relocate (token on top of the stack)
    board[cur_row][cur_col].top_stack = token->belowPtr; // removing the token


    token->belowPtr = board[new_row][new_col].top_stack;    //making token below the new top of the stack
    board[new_row][new_col].top_stack = token; // placing token on top of the new location
}

//function that checks if squares before obstacle are filled. If they are not, turning the obstacle square into a normal square
int obstacle_to_normal(Square board[NUM_ROWS][NUM_COLUMNS], int num_row, int num_col)
{
    int i = 0;
    int j = 0;
    while(i < NUM_ROWS)
    {
        while(j < num_col)
        {
                if (print_token(board[i][j].top_stack) == 'R' ||
                    print_token(board[i][j].top_stack) == 'B' ||
                    print_token(board[i][j].top_stack) == 'G' ||
                    print_token(board[i][j].top_stack) == 'Y' ||
                    print_token(board[i][j].top_stack) == 'P' ||
                    print_token(board[i][j].top_stack) == 'O')
                {
                    printf("Obstacle square still cus there are tokens before it!\n");
                    return 0;
                }
                printf("\nJ = %d", j);
                j++;
                printf("\nJ = %d", j);

                }


            j=0;
            i++;

        }
    }


/*
 * Place tokens in the first column of the board
 *s
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
void play_game(Square board[NUM_ROWS][NUM_COLUMNS], Player players[], int numPlayers)
{
    //creating variables for row, column values, and choice value for the sideways move
    int row_loc, column_loc, side_move;

    // for each player
    for (int i = 0; i < numPlayers; ++i)
        {

        int die;
        printf("\nEnter die: ");
        scanf("%d", &die);

        printf("\nPlayer's turn: %s (%s)", players[i].player_name, color_name(players[i].col));
        // take his turn:
        // roll die and tell the player his die roll
        //int die = rand() % 6;
        printf("You rolled: %d\n", die);

        // ask the player if he wants to move sideways
        int answer;
        puts("Do you want to move sideways? (1 for yes, 0 for no)");
        scanf("%d", &answer);

        // if he says yes
        if (answer == 1)
            {
                printf("Player %s: Which token do you wish to move sideways (it must be your token)\n"
                       "\nPlease give your answer in co-ordinates (row number followed by column number)\n", players[i].player_name);

                scanf("%d %d", &row_loc, &column_loc);

                if (board[row_loc][column_loc].top_stack != NULL)
                {
                //checking if token belongs to the player
                if (players[i].col == board[row_loc][column_loc].top_stack->col)
                {
                   printf("Please enter 1 if you wish to go upwards or 2 for downwards: ");
                   scanf("%d", &side_move);

                    if(side_move == 1)
                    {
                        move_token(board, row_loc, column_loc, row_loc-1, column_loc);
                        print_token(board[row_loc-1][column_loc].top_stack);
                        print_board(board);
                    }

                    else if (side_move == 2)
                    {
                        move_token(board, row_loc, column_loc, row_loc+1, column_loc);
                        print_token(board[row_loc+1][column_loc].top_stack);
                        print_board(board);
                    }

                    printf("Player %s: Move token from row %d forward.\n"
                            "It doesn't have to be your token, but it must be on top!\n"
                            "Please specify column number.\n", players[i].player_name, die);
                    scanf("%d", &column_loc);


                    move_token(board, die, column_loc, die, column_loc+1);
                    print_token(board[die][column_loc+1].top_stack);
                    print_board(board);

                }

                else
                {
                    printf("You can only move your own token!\n"
                            "Do you wish to move another one of your tokens sideways\n?"
                            "Enter 1 if you do, 0 if you don't.\n");

                    int side_move_2;
                    scanf("%d", &side_move_2);
                    if (side_move_2 == 1)
                    {
                        printf("\nPlayer %s: which token do you wish to move sideways?\n"
                               "Please ensure it is your own token!\n", players[i].player_name);
                        printf("Give your answer in co-ordinates: row number followed by column number\n");
                        scanf("%d %d", &row_loc, &column_loc);

                        printf("Please enter 1 if you wish to go upwards or 2 for downwards: ");
                        scanf("%d", &side_move);

                        if(side_move == 1)
                        {
                            move_token(board, row_loc, column_loc, row_loc-1, column_loc);
                            print_token(board[row_loc-1][column_loc].top_stack);
                            print_board(board);
                        }

                        else if(side_move == 2)
                        {
                            move_token(board, row_loc, column_loc, row_loc+1, column_loc);
                            print_token(board[row_loc+1][column_loc].top_stack);
                            print_board(board);
                        }


                    }

                    else if (side_move_2 == 0)
                    {
                        ;
                    }

                }

            }
            }

        else if (answer == 0)
            //moving tokens forward according to number on die
        {
            printf("Player %s: Move token from row %d forward.\n"
                   "It doesn't have to be your token, but it must be on top!\n"
                   "Please specify column number.\n", players[i].player_name, die);
            scanf("%d", &column_loc);

            printf("\n%d", obstacle_to_normal(board, die, column_loc));

              if(board[die][column_loc].type == OBSTACLE)
              {
                  if(obstacle_to_normal(board, die, column_loc) == 0)
                  {


                        print_board(board);
                        printf("\nThis is an obstacle square! You cannot move the token from here until every other token before the obstacle has reached column %d!\n"
                               "\nDo you have any other tokens you could move on row %d", column_loc, die);

                        /*printf("Please enter 1 if you do, 0 if you don't: ");
                        int tokenOnRow;
                        scanf("%d", &tokenOnRow);

                        while(tokenOnRow != 0)
                        {
                            printf("%s, please specify column number.\n", players[i].player_name);
                            scanf("%d", &column_loc);

                            if(board[die][column_loc].type == OBSTACLE)
                            {

                                printf("This is an obstacle square! You cannot move the token from here until every other token before the obstacle has reached row %d!\n"
                                "Do you have any other tokens you could move on row %d", die, die);
                                print_board(board);

                                printf("Please enter 1 if you do, 0 if you don't: ");
                                scanf("%d", &tokenOnRow);

                            }

                            else if(board[die][column_loc].type == NORMAL)
                            {
                                tokenOnRow = 0;
                            }

                        move_token(board, die, column_loc, die, column_loc+1);
                        print_token(board[die][column_loc+1].top_stack);
                        print_board(board);

                        }*/


                        }

                    else if (obstacle_to_normal(board, die, column_loc) == 1)
                    {
                        //board[die][column_loc].type = NORMAL;
                        move_token(board, die, column_loc, die, column_loc+1);
                        print_token(board[die][column_loc+1].top_stack);
                        print_board(board);

                    }
              }

                else if (board[die][column_loc].type == NORMAL)
                {
                    move_token(board, die, column_loc, die, column_loc+1);
                    print_token(board[die][column_loc+1].top_stack);
                    print_board(board);

                }


        }


            if (i == numPlayers - 1)
            {
            i = -1; // reset to the first player
            }
            // ask which token he wants to move (in coordinates) (it must be his token)
            // and in which direction (up or down)
            // move the token
    }
}


        // once you're done with the sideways move
        // ask the player which token does he wants to move according the die result row (it doesn't have to be his token, but it has to be the top one)
        // move the token forward (one column ahead) ONLY IF IT IS NOT ON AN OBSTACLE SQUARE

        // check if he won and break

        // check if obstacles are still obstacles

        // once the last player took his turn







