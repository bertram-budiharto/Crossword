// Name: Joseph Bertram
// Class: Fundamentals of Computing Lab
// Assignment: Lab 8: Crossword Anagram
// Purpose: A program that, given a list of words, will create a crossword anagram puzzle, with both the board and the anagram clues, that can be played on paper and pencil (Main Driver file).

#define _GNU_SOURCE 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#include "crossfunc.h"

int main(int argc, char* argv[]) {
	
	char words[20][16]; 
	char board[15][15]; 
	Board clues[20]; // declares an array of struct
	

	if (argc == 1) { // in the case the user enters only one command line argument
		printf("Please enter list of words (up to 20), followed by a period: ");
		printf("\n");

		int size = check_valid(words, stdin, stdout); // calls in the check_valid function to see if the words entered by the user are valid

		sorting_algorithm(words, size); // calls in the sorting_algorithm function to sort the words in descending order
		convert_letters(words, size); // calls in the convert_letters function to convert all letters to upper case 

		init_board(board); // calls in the init_board function to initialize the crossword board to all periods

		int words_passed = crossword(words, board, clues, stdout, size); // calls in the crossword function to apply the algorithm of the crossword and places the word in the board
	
		printf("\n");
		printf("SOLUTION: \n");	
		display_solution(board, stdout); // calls in the display_solution function to display the board solved

		printf("\n");
		printf("PUZZLE: \n");
		display_puzzle(board, stdout); // calls in the display_puzzle function to display the board unsolved

		printf("\n");
		printf("CLUES: \n");
		display_clues(clues, stdout, words_passed); // calls in the display_clues function to display the clues to the user
	}
	else if (argc == 2) { // in the case the user enters exactly two command line arguments 
		FILE* fp = fopen(argv[1], "r"); // attempting to open the data file, which corresponds to argv[1]
		if (fp == NULL) { // in the case of invalid data file
			printf("Inappropriate file!");
			printf("\n");
		}
		else { // in the case of valid data file
			int size = check_valid(words, fp, stdout); // calls in the check_valid function to see if the words listed in the data file are valid

			sorting_algorithm(words, size); // calls in the sorting_algorithm function to sort the words in descending order
			convert_letters(words, size); // calls in the convert_letters function to convert all letters to upper case 

			init_board(board); // calls in the init_board function to initialize the crossword board to all periods

			int words_passed = crossword(words, board, clues, stdout, size); // calls in the crossword function to apply the algorithm of the crossword and places the word in the board
	
			printf("\n");
			printf("SOLUTION: \n");	
			display_solution(board, stdout); // calls in the display_solution function to display the board solved

			printf("\n");
			printf("PUZZLE: \n");
			display_puzzle(board, stdout); // calls in the display_puzzle function to display the board unsolved

			printf("\n");
			printf("CLUES: \n");
			display_clues(clues, stdout, words_passed); // calls in the display_clues function to display the clues to the user
		}
	}
	else if (argc == 3) {
		FILE* fp_in = fopen(argv[1], "r"); // attempting to open the data file, which corresponds to argv[1]
		if (fp_in == NULL) { // in the case of invalid data file
			printf("Inappropriate file!");
			printf("\n");
		}
		else { // in the case of valid data file
			
			char file_name[20];
			strcpy(file_name, argv[2]);
			FILE* fp_out = fopen(file_name, "w");
			if (fp_out == NULL) {
				printf("Inappropriate file!");
				printf("\n");
			}
			else {
				int size = check_valid(words, fp_in, fp_out); // calls in the check_valid function to see if the words listed in the data file are valid

				sorting_algorithm(words, size); // calls in the sorting_algorithm function to sort the words in descending order
				convert_letters(words, size); // calls in the convert_letters function to convert all letters to upper case 

				init_board(board); // calls in the init_board function to initialize the crossword board to all periods

				int words_passed = crossword(words, board, clues, fp_out, size); // calls in the crossword function to apply the algorithm of the crossword and places the word in the board
	
				fprintf(fp_out, "\n");
				fprintf(fp_out, "SOLUTION: \n");	
				display_solution(board, fp_out); // calls in the display_solution function to display the board solved

				fprintf(fp_out, "\n");
				fprintf(fp_out, "PUZZLE: \n");
				display_puzzle(board, fp_out); // calls in the display_puzzle function to display the board unsolved

				fprintf(fp_out, "\n");
				fprintf(fp_out, "CLUES: \n");
				display_clues(clues, fp_out, words_passed); // calls in the display_clues function to display the clues to the user
			}
		}
	}
	else { // in the case the user enters more than two command line arguments 
		printf("Too many inputs!");
		printf("\n");
	}
	

	
	return 0;
}			
