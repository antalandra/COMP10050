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


//function that counts number of tokens in each square of a column
//and stores number as elements of an array
void countNoOfTokens(Square board[NUM_ROWS][NUM_COLUMNS], int column_loc)
{
    //declaring an array of 6 elements and initializing it to zero: corresponds to the amount of
    //tokens in each square of a column
    int array_of_num_of_tokens[6] = {0, 0, 0, 0, 0, 0};


	for ( int i = 0; i < NUM_ROWS; ++i)
	{
		Token *token = board[i][column_loc].top_stack;

		while (token != NULL)
		{
			array_of_num_of_tokens[i] += 1;
			token = token->belowPtr;
		}

	}

	//determining the minimum amount of tokens in a column
    //and changing the global variable min_num_of_tokens
	min_num_of_tokens = array_of_num_of_tokens[0];

	for ( int i = 0; i < NUM_ROWS; ++i)
	{
		if (array_of_num_of_tokens[i] < min_num_of_tokens)
		{
			min_num_of_tokens = array_of_num_of_tokens[i];
		}
	}
}

//function that counts number of tokens in a square
//and storing number in an integer variable
int NoOfTokensInSquare(Square board[NUM_ROWS][NUM_COLUMNS], int row_loc, int column_loc)
{
	Token *token = board[row_loc][column_loc].top_stack;

	int num_of_tokens = 0;

	while ( token != NULL)
	{
		num_of_tokens++;
		token = token->belowPtr;
	}

	return num_of_tokens;

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

void place_tokens(Square board[NUM_ROWS][NUM_COLUMNS], Player players[], int numPlayers)
{

    int tok = 0;    //initializing token number to zero
    while (tok !=4)
    {
        int pl = 0; //initializing player number to zero
        while ( pl != numPlayers)
        {
            countNoOfTokens(board, 0);

            int row_num;
            printf("Player %s: place token %d on a row of your choice from 0 to 5: ", players[pl].player_name, tok+1);
            scanf("%d", &row_num);  //scan row number from player

            while (NoOfTokensInSquare(board, row_num, 0) > min_num_of_tokens)
            {
                printf("\nYou cannot place a token here until all smaller stacks are filled first!\n"
                       "Player %s: place token %d on a row corresponding to one of the smaller stacks.\n", players[pl].player_name, tok+1);
                scanf("%d", &row_num);

            }

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

//function that checks if squares before obstacle are filled.
int check_if_obstacle(Square board[NUM_ROWS][NUM_COLUMNS], int num_row, int num_col)
{
    int i = 0;
    int j = 0;
    while(i < NUM_ROWS)
    {
        while(j < num_col)
        {
                if (board[i][j].top_stack != NULL )
                {
                    return 0;
                }
            j++;

        }
        j=0;
        i++;
    }

    return 1;
}




int checkWhoWon(Square board[NUM_ROWS][NUM_COLUMNS], Player players[], int numPlayers)
{
    //creating dynamic array to hold the counters for each token color of each player in the last column at the end of the game
    int *NumOfColors = (int*)calloc(numPlayers, sizeof(int));

    for ( int num = 0; num < numPlayers; ++num)
    {
        //going through the rows of last column to see if the colors in the square match to the player's color
        for (int i = 0; i < NUM_ROWS; ++i)
        {

            Token *token = board[i][8].top_stack;
            while (token != NULL)
            {
                if(token->col == players[num].col)
                {
                    NumOfColors[num] += 1; //incrementing every time color of token matches that of player's
                }

                token = token->belowPtr;    //going to next element in the stack (if there is any)

                }

            }

        }


        //running through array to check if there is 3 or more tokens of the same color
		for ( int i = 0; i < numPlayers; ++i)
		{
			if ( NumOfColors[i] >= 3)
			{
				return i;  //if there is, returning the player's name who has 3 or more tokens in the last column
                                                //->returning winner
			}
		}

    return 7; //returning a number that is bigger than the potential maximum number of players
}

/*
 * Place tokens in the first column of the board
 *s
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
int play_game(Square board[NUM_ROWS][NUM_COLUMNS], Player players[], int numPlayers)
{

    //creating variables for row, column values, and choice value for the sideways move
    int row_loc, column_loc, side_move, side_move_new_choice;

    // for each player
    for (int i = 0; i < numPlayers; ++i)
        {

        int die;
        printf("\nEnter die: ");
        scanf("%d", &die);

        printf("\nPlayer's turn: %s (%s)", players[i].player_name, color_name(players[i].col));
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

                countNoOfTokens(board, column_loc);

                if (board[row_loc][column_loc].top_stack != NULL)
                {
                    //while token doesn't belong to the player
                    while (players[i].col != board[row_loc][column_loc].top_stack->col)
                    {
                        printf("You can only move your own token!\n");
                        printf("Player %s: Which token do you wish to move sideways (it must be your token)\n"
                           "\nPlease give your answer in co-ordinates (row number followed by column number)\n", players[i].player_name);
                        scanf("%d %d", &row_loc, &column_loc);
                    }


                       printf("Please enter 1 if you wish to go upwards or 2 for downwards: ");
                       scanf("%d", &side_move);

                        if(side_move == 1)
                        {
                            if (NoOfTokensInSquare(board, row_loc-1, column_loc) > min_num_of_tokens)
                            {
                                printf("\nYou cannot place a token here until all smaller stacks are filled first!\n"
                                        "Player %s: place token on a row corresponding to one of the smaller stacks.\n"
                                        "Do you wish to go downwards instead?\n"
                                        "If yes, enter 2, if not then enter 0.\n", players[pl].player_name);
                                scanf("%d", &side_move_new_choice);

                                if (side_move_new_choice == 2)
                                {
                                    if (NoOfTokensInSquare(board, row_loc+1, column_loc) <= min_num_of_tokens)
                                    {
                                        move_token(board, row_loc, column_loc, row_loc+1, column_loc);
                                        print_token(board[row_loc+1][column_loc].top_stack);
                                        print_board(board);
                                    }

                                    else
                                    {
                                        ;
                                    }

                                }

                                else if (side_move_new_choice == 0)
                                {
                                        ;
                                }

                            }

                            else
                            {
                                move_token(board, row_loc, column_loc, row_loc-1, column_loc);
                                print_token(board[row_loc-1][column_loc].top_stack);
                                print_board(board);
                            }


                        }

                        else if (side_move == 2)
                        {


                            if (NoOfTokensInSquare(board, row_loc+1, column_loc) > min_num_of_tokens)
                            {
                                printf("\nYou cannot place a token here until all smaller stacks are filled first!\n"
                                        "Player %s: place token on a row corresponding to one of the smaller stacks.\n"
                                        "Do you wish to go upwards instead?\n"
                                        "If yes, enter 2, if not then enter 0.\n", players[pl].player_name);
                                scanf("%d", &side_move_new_choice);

                                if (side_move_new_choice == 2)
                                {
                                    if (NoOfTokensInSquare(board, row_loc-1, column_loc) <= min_num_of_tokens)
                                    {
                                        move_token(board, row_loc, column_loc, row_loc-1, column_loc);
                                        print_token(board[row_loc-1][column_loc].top_stack);
                                        print_board(board);
                                    }

                                    else
                                    {
                                        ;
                                    }

                                }

                                else if (side_move_new_choice == 0)
                                {
                                        ;
                                }

                            }

                            else
                            {
                                move_token(board, row_loc, column_loc, row_loc+1, column_loc);
                                print_token(board[row_loc+1][column_loc].top_stack);
                                print_board(board);
                            }


                        }


                        printf("Player %s: Move token from row %d forward.\n"
                                "It doesn't have to be your token, but it must be on top!\n"
                                "Please specify column number.\n", players[i].player_name, die);
                        scanf("%d", &column_loc);

                        countNoOfTokens(board, column_loc);

                        if(board[die][column_loc].type == OBSTACLE)
                        {
                          if(check_if_obstacle(board, die, column_loc) == 0)
                          {


                                print_board(board);
                                printf("\nThis is an obstacle square! You cannot move the token from here until every other token before the obstacle has reached column %d!\n"
                                       "\nDo you have any other tokens you could move on row %d", column_loc, die);

                                printf("Please enter 1 if you do, 0 if you don't: ");
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

                                }
                          }

                        else if (check_if_obstacle(board, die, column_loc) == 1)
                            {
                                board[die][column_loc].type = NORMAL;
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


                         if (checkWhoWon(board, players, numPlayers) != 7)
                        {
                printf("\nCongratulations, %s! You are the winner of the game with 3 %s tokens in the last column!!\n",
                       players[checkWhoWon(board, players, numPlayers)].player_name, players[checkWhoWon(board, players, numPlayers)].col);
                       return 1;
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


            if(board[die][column_loc].type == OBSTACLE)
              {
                  if(check_if_obstacle(board, die, column_loc) == 0)
                  {


                        print_board(board);
                        printf("\nThis is an obstacle square! You cannot move the token from here until every other token before the obstacle has reached column %d!\n"
                               "\nDo you have any other tokens you could move on row %d", column_loc, die);

                        printf("Please enter 1 if you do, 0 if you don't: ");
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

                        }
                  }

                else if (check_if_obstacle(board, die, column_loc) == 1)
                    {
                        board[die][column_loc].type = NORMAL;
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




            if (checkWhoWon(board, players, numPlayers) != 7)
            {
                printf("\nCongratulations, %s! You are the winner of the game with 3 %s tokens in the last column!!\n",
                       players[checkWhoWon(board, players, numPlayers)].player_name, players[checkWhoWon(board, players, numPlayers)].col);
                       return 1;
            }


           if (i == numPlayers - 1)
            {
            i = -1; // reset to the first player
            }
        }
    }
    return 0;
}
