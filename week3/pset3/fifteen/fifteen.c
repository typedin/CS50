/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

/**
 * Added some comments
 */
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void swap(int a, int b);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    // initialize the tile to the highest value possible
	int tile = d*d - 1;

    // iterate over the grid
    for (int i = 0 ; i < d ; i++)
    {
        for (int j = 0 ; j < d ; j++)
        {
            board[i][j] = tile--;
		}
	}
	
	// assign last tile to empty space
	board[d - 1][d - 1] = 0;
	
	// d is even, then swap tile 1 and 2
	if(d % 2 == 0)
	{
		swap(1,2);
	}
		
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    
	// print the current state of the board
	for (int i = 0 ; i < d ; i++)
		for (int j = 0 ; j < d ; j++)
		{
			// deal with all one digit values
			if (board[i][j] < 10)
			{
				// display an empty tile for a value of 0
				if (board[i][j] == 0)
						printf(" _");
				// pad 1 digit values
				else
					printf("%2i", board[i][j]);
			}
			else
				printf("%i", board[i][j]);
				
		// if end of line: print a new line else print |
		printf("%s", j == d - 1 ? "\n":"|");
		}
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    // linear search implementation
	
	// declared outside the loop so they are accessible
	int blank_i, blank_j;
	int tile_i = -1;
	int tile_j = -1;
	
	// ensure the user doesn't try to move a tile that doesn't exist
	bool found = false;
	
	for (int i = 0 ; i < d ; i++)
	{
		for (int j = 0; j < d ; j++)
			{
				if (board[i][j] == tile)
				{
					tile_i = i;
					tile_j = j;
					found = true;
				}
				if (board[i][j] == 0)
				{
					blank_i = i;
					blank_j = j;
				}
			}
	}			
	
	// splited in two conditions, so it's easier to read
	if (found)
	{						
		// if same vertical axis
		if ( blank_i == tile_i && (blank_j == (tile_j - 1) || blank_j == (tile_j + 1)))
		{ 
			// swap tiles
			swap(board[blank_i][blank_j],board[tile_i][tile_j]);
			
			return true;
		}
		// if same horizontal axis
		if ( blank_j == tile_j && (blank_i == (tile_i - 1) || blank_i == (tile_i + 1)))
		{
			// swap tiles
			swap(board[blank_i][blank_j],board[tile_i][tile_j]);

			return true;
		}
	}
	
	// check against invalid values
	else if (tile_i == -1 && tile_j == -1)
	{
		return false;
	}
	
	// default return
	return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
	// value checked against each tile
	int counter = board[0][0];
	
	// return false if the first tile is not the lowest tile
	if (counter != 1)
		return false;
		
	for(int i = 0; i < d; i++)
	{
		for (int j = 0; j < d; j++)
		{
			if(counter++ != board[i][j])
			{
				// the grid is not in order
				return false;
			}
			else
			{
				/**
				 * last case :
				 * the penultimate is the highest tile (i.e. d*d - 1)
				 * AND
				 * the last is empty (i.e. 0)
				 * */
				if (board[i][j] == d*d - 1 && board[i][j + 1] == 0)
					return true;
			}
		}
	}

    return false;
}


/**
 * swap two tiles
 * takes two ints as input
 */
void swap(int a, int b)
{
	// coordonates of each parameters
	int a_i, a_j;
	int b_i, b_j;
	
	// loop over the array to find the coordonates of each number
	for (int i = 0; i < d; i++)
	{
		for (int j = 0; j < d; j++)
			{
				if (board[i][j] == a)
				{
					a_i = i;
					a_j = j;
				}
				if (board[i][j] == b)
				{
					b_i = i;
					b_j = j;
				}
			}
	}
	
	// swap the numbers
	board[a_i][a_j] = b;
	board[b_i][b_j] = a;
}