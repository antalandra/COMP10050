
/*
 * Prints the board
 *
 * Input: the board to be printed.
 */
void print_board(Square board[NUM_ROWS][NUM_COLUMNS]);

/*
 * returns value 1 if two or more players have the same color
 *
 * Input: the color of each player and the number of players
 */
int checkIfChosen(Player players[], int numPlayer);

/*
 * Place tokens in the first column of the board
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
void place_tokens(Square board[NUM_ROWS][NUM_COLUMNS], Player players[], int numPlayers);



/*
 *  * Manages the logic of the game
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
int play_game(Square board[NUM_ROWS][NUM_COLUMNS], Player players[], int numPlayers);


/*
 *Moves the token from one location to another
 *Input: the board
 *       current row and column location of token
 *       future row and column location of token
 */

void move_token(Square board[][NUM_COLUMNS], int cur_row, int cur_col, int new_row, int new_col);

/*
 *Checks which player won
 *
 *Input: the board
 *      the players
 *      number of players
 */

int checkWhoWon(Square board[NUM_ROWS][NUM_COLUMNS], Player players[], int numPlayers);

