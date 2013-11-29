
#include "pa11.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define TRUE 1
// #define FALSE 0

int compare(const void * a, const void * b);
int searchdash(char * state);

/**
            IMPORTANT INFORMATION
  
This assignment comes with the following files:
+ "README", please read all of this before asking questions.
+ "pa11.c", do not edit this file. (See note below.)
+ "pa11.h", do not edit this header file.
+ "answer11.c", the file you must SUBMIT at the assignment deadline.
+ "tester", a binary (encrypted) file that runs tests on a compiled 
  executable.

You are responsible for testing your code as you write it. The tester
binary will run some tests; however, it is specifically designed to be
too slow to be executed in an edit-compile-test loop. You must set up
this loop yourself. This is EXTREMELY important if you want to learn
how to code faster and more accurately, which is why we do this.

TO TEST YOU CODE

You should set up your own "main(...)" function, in which you create
data an manipulate it with specific functions. For example, you can
run the "isValidState(...)" function as follows:

int main(int argc, char * * argv)
{
   isValidState("ABCDE");
   return 0;
}

 */


/** 
 * Return TRUE iff 'state' is a valid puzzle state.
 *
 * To do this, you have to check:
 * strlen(state) == 16
 * That 'state' only contains characters from "123456789ABCDEF-"
 * That 'state' contains no repeated characters
 *
 * The easiest way to do this is to:
 * (1) Copy 'state' into a buffer that you create
 * (2) Sort the characters in your buffer. (Use qsort.)
 * (3) Check that buffer is equal to "-123456789ABCDEF"
 */
int isValidState(const char * state)
{
	char * buffer = malloc(sizeof(char) * (strlen(state) + 1));
	//char * new = malloc(sizeof(char) * 17);
	char * check = "-123456789ABCDEF";
	strcpy(buffer, state);
	qsort(buffer, strlen(buffer), sizeof(char), compare);
	int a = 0;
	for(a = 0; a < strlen(buffer); a++)
	{
		printf(" %c ", buffer[a]);
	}
	printf("\n");
	//int num = 1;
	for(a = 0; a < strlen(buffer); a++)
	{
		if(check[a] != buffer[a])
		{
			return FALSE;
		}
	}
	free(buffer);
    return TRUE;
}
int compare(const void * a, const void * b)
{
	char* intp1 = (char*) a;
	char* intp2 = (char*) b;
	
	char val = *intp1;
	char val2 = *intp2;
	
	if(val < val2)
	{
		return -1;
	}
	
	if(val == val2)
	{
		return 0;
	}
	
	return 1;
   
}

/** 
 * Return TRUE iff all characters in 'moves' are in "RLUD"
 *
 * To do this you must iterate over the string, and check that
 * each character is one of { 'R', 'L', 'U', 'D' }
 */ 
int isValidMoveList(const char * moves)
{
	int len = strlen(moves);
	int a = 0;
	for(a = 0; a < len; a++)
	{
		if(moves[a] != 'R' && moves[a] != 'L' && moves[a] != 'U' && moves[a] != 'D')
		{
			return FALSE;
		}
	}
    return TRUE;
}

/**
 * Prints the puzzle-state as a 2d matrix. 
 *
 * This function is for debugging purposes only. It is strongly 
 * recommended that you write it; however, it is will not be graded.
 */
void printPuzzle(const char * state)
{
    int row, col;
    for(row = 0; row < SIDELENGTH; ++row) {
	for(col = 0; col < SIDELENGTH; ++col) {
	    printf(" %c", state[row*SIDELENGTH + col]);
	}
	printf("\n");
    }
}


/**
 * Apply move 'm' to puzzle-state 'state'. Return TRUE iff success.
 *
 * You can assume that 'm' is one of { 'U', 'D', 'L', 'R' }, and 
 * that 'state' is a valid state, which means it contains a '-' 
 * character.
 *
 * The simplest way to write this function is as follows:
 * (1) Find the row and column of the space character '-'
 *     (1.a) Search 'state' for the 'position' of the '-' character
 *     (1.b) The 'row' will be 'position / SIDELENGTH'
 *     (1.c) The 'col' will be 'position % SIDELENGTH'
 * (2) Look at the move 'm', and calculate the _new_ row and col
 *     (2.a) If 'm' == 'U', then 'new_row = row-1' and 'new_col = col'
 *     etc.
 * (3) Check that 'new_row' and 'new_col' are in bounds. They must
 *     be >= 0 and < SIDE_LENGTH. If they are _not_ in bounds, then
 *     return FALSE
 * (4) Calculate the 'target_position' for the '-' character. It will
 *     be 'new_row * SIDELENGTH + new_col'
 * (5) Swap the characters at 'position' and 'target_position'
 */
int move(char * state, char m)
{ 
	printf("COUNT \n");
	//int len = strlen(state);
	// int a = 0;
	int row = 0;
	int new_row = 0;
	int col = 0;
	int new_col = 0;
    int pos = 0;
    int new_pos = 0;
	// for(a = 0; a < len; a++)
	// {
		pos = searchdash(state);
		row = pos / SIDELENGTH;
		col = pos % SIDELENGTH;
		if(m == 'R')
		{
			new_col = col + 1;
			new_row = row;
		}
		if(m == 'L')
		{
			new_col = col - 1;
			new_row = row;
		}
		if(m == 'U')
		{
			new_col = col;
			new_row = row - 1;
		}
		if(m == 'D')
		{
			new_col = col;
			new_row = row + 1;
		}
		if(new_row < 0 || new_row >= SIDELENGTH || new_col < 0 || new_col >= SIDELENGTH)
		{
			return FALSE;
		}
		new_pos = (new_row * SIDELENGTH) + new_col;
		char temp = state[pos];
		state[pos] = state[new_pos];
		state[new_pos] = temp;
	// }
	
	return TRUE;
}

int searchdash(char * state)
{
	int len = strlen(state);
	// int pos = 0;
	int a = 0;
	for(a = 0; a < len; a++)
	{
		if(state[a] == '-')
		{
			return a;
		}
	}
	
	return a;
}
/**
 * Apply the moves in 'movelist' to state. 
 *
 * If the sequence is invalid, then print "I" on a single line.
 * Otherwise, print the new state after moves have been applied.
 *
 * To do this, you need:
 * (1) A for-loop to iterate over characters 'm' in 'movelist'
 *     (1.a) Call move(state, m)
 *     (1.b) If 1.a fails, then print "I" on a single line
 * (2) If you never failed in (1), then print the final state on a 
 *     single line.
 */
void processMoveList(char * state, const char * movelist)
{
	int len = strlen(movelist);
	int a = 0;
	for(a = 0; a < len; a++)
	{
		if(move(state, movelist[a]) == FALSE)
		{
			printf("I");
			return;
		}
	}
	for(a = 0; a < strlen(state); a++)
	{
		printf("%c", state[a]);
	}
	return;
}

/**
 * Initialise a new MoveTree
 */
MoveTree * MoveTree_create(const char * state, const char * moves)
{
    return NULL;
}

/**
 * Destroy a tree -- must be safe to call MoveTree_destroy(NULL)
 */
void MoveTree_destroy(MoveTree * node)
{
    
}

/**
 * Insert a new node into a tree, keeping in mind that:
 * (1) We do not allow duplicate states.
 * (2) If we attempt to insert a duplicate state, then we keep the
 *     node with the shortest move sequence.
 */
MoveTree * MoveTree_insert(MoveTree * node, const char * state,
			   const char * moves)
{
    return NULL;
}

/**
 * Search the tree (rooted at 'node') for a node whose
 * state is 'state'
 */
MoveTree * MoveTree_find(MoveTree * node, const char * state)
{
  
}

/**
 * Print the moves in a move-tree.
 * This function is supplied to you.
 */
void MoveTree_print(MoveTree * node)
{
    if(node == NULL)
	return;
    printf("%s\n", node -> state);
    MoveTree_print(node -> left);
    MoveTree_print(node -> right);
}

/**
 * Generate all possible states from 'state' after 0 to 'n_moves'.
 * Returns a 'MoveTree' which contains all of the unique states
 * reachable from 'state' after '0..n_moves' (inclusive). If the same
 * state can be reached by different move sequences, the prefer the
 * shorter of the two sequences.
 * 
 * To write this function you need to create a list of unique states.
 * To do this, you must store the states in a tree, so that when you
 * insert a new state, you can _quickly_ check if it already exists.
 *
 * You will need to create a 'helper' function. When I wrote this code
 * I used the function signature:
 * 
 * void generateAllHelper(MoveTree * root, // Root of the tree
 *         int n_moves,        // maximum length of a movelist
 *         const char * state, // the current state of the puzzle
 * 	   char * movelist,    // the current movelist
 *         int ind)            // the next index to write in movelist
 *
 * This recursive helper function works as follows:
 * (1) The base case: ind == n_moves. Do _nothing_ and return
 * (2) The recursive case:
 *    (2.a) Iterate over the possible moves { 'U', 'D', 'L', 'R'}
 *        (2.a.i) Duplicate 'state' and store it in 'dup_state'
 *                You do this because you don't want to corrupt 
 *                'state' for any other move sequences.
 *        (2.a.ii) Try to apply move 'm' to 'dup_state. If it doesn't
 *                 work, then do nothing and free 'dup_state'
 *        (2.a.iii) If the move was applied, then insert 'dup_state'
 *                  and 'movelist' into the tree 'root'. Be careful...
 *                  MoveTree_insert(...) expects 'movelist' to be a 
 *                  valid c-string, so you _must_ make sure that the
 *                  null-byte is correctly set.
 *        (2.a.iv) Recursively call generateAllHelper(...) with the
 *                 duplicated state, mutated movelist, and updated ind
 *        (2.a.v) Free 'dup_state'
 *
 * Once you have your helper function written, then you can:
 * (1) Create a 'movelist' buffer that can hold a string of length 
 *     n_moves. (Don't forget the null byte.)
 * (2) Create a MoveTree, with 'state' and an empty move list.
 * (3) Call your helper function.
 * (4) Return the tree.
 *
 * This is the most complex function to write... make sure you break
 * it down, and TEST EACH PART.
 */
MoveTree * generateAll(char * state, int n_moves)
{ 
    return NULL;
}

/**
 * To solve the puzzle:
 * (1) Generate all the possible states up to MAX_SEARCH_DEPTH
 * (2) Search the possibilities for FINAL_STATE
 * (3) If FINAL_STATE isn't found, return NULL
 * (4) If FINAL_STATE is found, then return a copy of the moves.
 */
char * solve(char * state)
{
    return NULL;
}

int main(int argc, char * * argv)
{

   printf("CHECKforstate = %d \n", isValidState(argv[1]));
   printf("CHECKformoves = %d \n", isValidMoveList(argv[2]));
   printPuzzle(argv[1]);
   processMoveList(argv[1], argv[2]);
   printf("\n");
   printPuzzle(argv[1]);
   
   return 0;
}


