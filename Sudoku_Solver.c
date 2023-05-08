#include<stdlib.h>
#include<stdio.h>
#include<string.h>

// function to print a sudoku board
void print_sudoku(int sudoku[9][9]) {
        for (int y = 0; y < 9; y++) {
                for (int x = 0; x < 9; x++) {
                        printf("%d ", sudoku[y][x]);
                        if (x % 3 == 2) printf("  ");
                }
                printf("\n");
                if (y % 3 == 2) printf("\n");
        }
}

// determines if the board is filled, returns true (1) or false (0)
int complete(int sudoku[9][9]) {
	for (int i = 0; i < 81; i++) if (!sudoku[i/9][i%9]) return 0;
	return 1;
}

// determines if a given number (value) is valid in a given position (row, col) in a given sudoku (sudoku), returns true or false
int validCell(int sudoku[9][9], int row, int col, int value) {
	// determines which box the cell is in
	int boxrow = (row/3)*3;
	int boxcol = (col/3)*3;

	// checks 
	for (int i = 0; i < 9; i++) {
		// cycles through each cell in the same box as the target cell
		int temprow = boxrow+i/3;
		int tempcol = boxcol+i%3;
		
		// checks if there is another cell with the same value in the column of the target cell
		if (sudoku[i][col] == value && i != row) return 0;
		
		// checks if there is another cell with the same value in the row of the target cell
		if (sudoku[row][i] == value && i != col) return 0;
		
		// checks if there is another cell with the same value in the row of the target cell
		if (temprow != row && tempcol != col && sudoku[temprow][tempcol] == value) return 0;
	}
	return 1;
}

// function to solve sudoku boards
void solve_sudoku(int sudoku[9][9], int depth) {
	int row = depth%9;
	int col = depth/9;
	// if we hit the end and it's solved, tell everyone!
	if (depth > 80) return;
	// if the cell we're at is a hint (> 0) then it works fine! Just solve the rest :)
	else if (sudoku[row][col]) solve_sudoku(sudoku, depth + 1);
	// if we need to make a cell work
	else {
		// for all the values it could be...
		for (int i = 0; i < 9; i++) {
			sudoku[row][col]++;
			// check if increasing the value by one will work
			if (validCell(sudoku, row, col, sudoku[row][col])) {
				// then if we can solve the rest, we're done!
				solve_sudoku(sudoku, depth + 1);
				if (complete(sudoku)) return;
			// otherwise keep trying :)
			}
		}
		// if we finished trying all the values then it didn't work :( tell the previous guy he got something wrong
		sudoku[row][col] = 0;
	}
}

// checks if two sudoku boards are identical (for use with the test cases), returns true or false
int same(int puzzle[9][9], int solution[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (puzzle[i][j] != solution[i][j]) {
				// reports the first difference found in the puzzle
				printf("your solution has %d at [%d, %d], but it should have %d at [%d, %d]!\n", puzzle[i][j], i, j, solution[i][j], i, j);
				return 0;
			}
		}
	}
	return 1;
}

// generic sudoku solver test cases, returns 1 if all are passed and 0 if not
int test_sudoku(void (*solver)(int sudoku[9][9], int depth)) {
	printf("testing your sudoku solver 0_0\n Best of luck!\n");
	// TEST 1
  	int puzzle1[9][9] = {
		{5, 3, 0, 0, 7, 0, 0, 0, 0},
		{6, 0, 0, 1, 9, 5, 0, 0, 0},
		{0, 9, 8, 0, 0, 0, 0, 6, 0},
		{8, 0, 0, 0, 6, 0, 0, 0, 3},
		{4, 0, 0, 8, 0, 3, 0, 0, 1},
		{7, 0, 0, 0, 2, 0, 0, 0, 6},
		{0, 6, 0, 0, 0, 0, 2, 8, 0},
		{0, 0, 0, 4, 1, 9, 0, 0, 5},
		{0, 0, 0, 0, 8, 0, 0, 7, 9}
	};

	solver(puzzle1, 0);

	if (complete(puzzle1)) printf("passed test 1! This was the one they gave us :)\n");
	else {printf(":( failed test 1:\nYour solution was:\n"); print_sudoku(puzzle1); return 0;}

	// TEST 2
	int puzzle2[9][9] = {
		{0, 9, 0, 7, 0, 3, 0, 8, 0},
		{1, 6, 0, 0, 9, 5, 4, 0, 0},
		{0, 0, 3, 4, 1, 8, 0, 0, 9},
		{2, 3, 0, 0, 0, 4, 0, 0, 6},
		{0, 5, 7, 6, 0, 9, 1, 4, 0},
		{6, 0, 0, 1, 0, 0, 0, 5, 8},
		{3, 0, 0, 5, 8, 2, 9, 0, 0},
		{0, 0, 4, 3, 7, 0, 0, 6, 5},
		{0, 2, 0, 9, 0, 6, 0, 1, 0}
	};

	solver(puzzle2, 0);

	if (complete(puzzle2)) printf("passed test 2! I stole this from my sister's sudoku puzzle book. Supposedly it's medium difficulty. Should be easy for you though ;)\n");
	else {printf(":( failed test 2:\nYour solution was:\n"); print_sudoku(puzzle2); return 0;}

	// TEST 3
	int puzzle3[9][9] = {
		{0, 0, 1, 0, 2, 4, 0, 0, 0},
		{0, 0, 5, 0, 0, 0, 6, 0, 0},
		{0, 0, 0, 0, 0, 9, 0, 3, 4},
		{7, 8, 0, 0, 4, 0, 0, 5, 0},
		{0, 0, 0, 7, 0, 1, 0, 0, 0},
		{0, 4, 0, 0, 9, 0, 0, 6, 3},
		{3, 7, 0, 2, 0, 0, 0, 0, 0},
		{0, 0, 6, 0, 0, 0, 5, 0, 0},
		{0, 0, 0, 9, 1, 0, 3, 0, 0}
	};

	solver(puzzle3, 0);

	if (complete(puzzle3)) printf("passed test 3! This is one of the \"Expert\" puzzles from the book. I bet you've got it no problem.\n");
	else {printf(":( failed test 3:\nYour solution was:\n"); print_sudoku(puzzle3); return 0;}

	
	// TEST 4
	int puzzle4[9][9] = {0};

	solver(puzzle4, 0);

	if (complete(puzzle4)) printf("passed test 4! That one was an empty board, so it's kinda cool that your algorithm can solve that!\n");
	else {printf(":( failed test 4\n your solution was:\n"); print_sudoku(puzzle4); return 0;}

	// TEST 5
	int puzzle5[9][9] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{3, 8, 4, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 2}
	};

	solver(puzzle5, 0);

	if (complete(puzzle5)) printf("passed test 5! That one had only 4 hints at the start! How crazy is that?!\n");
	else {printf("failed test 5 :(\n Your solution was:\n"); print_sudoku(puzzle5); return 0;}

	printf("\nYou got it all! That's crazy! You should make a hot chocolate or something to celebrate :)\n\n");

	return 1;
}

// function containing tests designed to substantially slow "brute force" methods of solving sudoku, returns 1 if all are passed, 0 if not
int brute_force_tests(void (*solver)(int sudoku[9][9], int depth)) {
	// TEST 1
	int puzzle1[9][9] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 4, 0, 0, 0, 0, 0},

		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},

		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 7, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 9}
	};

	solver(puzzle1, 0);

	if (complete(puzzle1)) printf("passed test 1! This was just me learning to make hard sudoku solver breakers so it WILL get harder.\n");
	else return 0;

	// TEST 2
	int puzzle2[9][9] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 3, 0, 8, 5},
		{0, 0, 1, 0, 2, 0, 0, 0, 0},
		{0, 0, 0, 5, 0, 7, 0, 0, 0},
		{0, 0, 4, 0, 0, 0, 1, 0, 0},
		{0, 9, 0, 0, 0, 0, 0, 0, 0},
		{5, 0, 0, 0, 0, 0, 0, 7, 3},
		{0, 0, 2, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 4, 0, 0, 0, 9}
	};

	solver(puzzle2, 0);

	if (complete(puzzle2)) printf("passed test 2! That was the \"brute-force killer!\" If you got that guy, you're doing well. For added challenge, try a clever solution to avoid being slowed down by this guy.\n");
	else {printf(":( failed test 4:\nYour solution was:\n"); print_sudoku(puzzle2); return 0;}

	return 1;
}

int main(int argc, char* argv[]) {
	// SET TO 1 TO RUN THAT SET OF TESTS, 0 TO SKIP
		// general tests
	int gt = 0;
		// brute force tests
	int bf = 0;

	// to detemrine if a set of tests has been passed (1 by default, will be set to 0 if a test is failed)
	int passed = 1;

	// GENERAL TESTS
	if (gt) {
		printf("general tests:\n");
		passed = test_sudoku(solve_sudoku);

		if (passed) printf("passed general tests.\n");
		else return 0;
	}

	// BRUTE FORCE TESTS
	if (bf) {
		passed = brute_force_tests(solve_sudoku);

		if (passed) printf("passed brute force tests\n");
		else return 0;
	}


        // regular use case
        if (argc) {
                // check input
                if (argc > 2) {
                        printf("too many arguments. write the sudoku from left to right, top to bottom with no spaces\n");
                        exit(1);
                }
                
                // get sudoku from command line input
                int sudoku[9][9];
                for (int i = 0; i < strlen(argv[1]); i++) {
                        sudoku[i/9][i%9] = argv[1][i] - 48;
                }

                // solve sudoku
                printf("you input:\n");
                print_sudoku(sudoku);

                solve_sudoku(sudoku, 0);

                printf("the solution is:\n");
                print_sudoku(sudoku);
        }

}
