// Name: Joseph Bertram
// Class: Fundamentals of Computing Lab
// Assignment: Lab 8: Crossword Anagram
// Purpose: A program that, given a list of words, will create a crossword anagram puzzle, with both the board and the anagram clues, that can be played on paper and pencil (Header file). 

#define _GNU_SOURCE 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

// declares a struct named Board
typedef struct {
	char word[16];
	int row;
	int column;
	char direction[16];
	char scrambled[16];
}	Board;

// a function to convert all the letters in the words to upper case alphabets
void convert_letters(char [20][16], int);

// a function to sort the words in the array in descending order
void sorting_algorithm(char [20][16], int);

// a function to check the validity of the words
int check_valid(char [20][16], FILE* , FILE* );

// a function to initialize the board to all periods
void init_board(char [15][15]);

// a function to apply the algorithm of the crossword
int crossword(char [20][16], char [15][15], Board [20], FILE* ,int);

// a function display the solved board
void display_solution(char [15][15], FILE* );

// a function to display the unsolved board
void display_puzzle(char [15][15], FILE* );

// a function to display the clues to the user
void display_clues(Board [20], FILE* ,int);
