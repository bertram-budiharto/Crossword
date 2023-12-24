// Name: Joseph Bertram
// Class: Fundamentals of Computing Lab
// Assignment: Lab 8: Crossword Anagram
// Purpose: A program that, given a list of words, will create a crossword anagram puzzle, with both the board and the anagram clues, that can be played on paper and pencil (Functions file).

#define _GNU_SOURCE 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#include "crossfunc.h"

void convert_letters(char arr[20][16], int count) {

	for (int i = 0; i < count; i++) { // goes through the rows of the array 
		for (int j = 0; j < strlen(arr[i]); j++) { // goes through the letters of the word 
			arr[i][j] = toupper(arr[i][j]); // converts each letter to upper case 
		}
	}
	
}

void sorting_algorithm(char words[20][16], int n) {

	char tempVal1[16]; 
	char tempVal2[16];
	char currentVal[16];

	for (int i = 0; i < n - 1; i++) { // goes through the list of words from index 0 to index n - 2
		int posVal2;
		int exist = 0;
		for (int j = i + 1; j < n; j++) { // goes through the list of words from index i + 1 to n - 1
			if (strlen(words[i]) > strlen(words[j])) { // checks if the string length of word at index i is greater than the string length of word at index j
				continue;
			}
			else if (exist == 0 && (strlen(words[i]) < strlen(words[j]))) { // checks if exists still equals zero and checks if the string length of word at index i is smaller than the string length of word at index j
				exist = 1;
				strcpy(tempVal1, words[j]); // copies the word at index j to the array tempVal
				posVal2 = j; // saves the position of index j to posVal2
			}
			else if (exist == 1 && (strlen(words[i]) < strlen(words[j]))) { // checks if exists equals one and checks if the string length of word at index i is smaller than the string length of word at index j
				strcpy(tempVal2, words[j]); // copies the word at index j to the array tempVal2
				if (strlen(tempVal1) >= strlen(tempVal2)) { // checks if string length of tempVal1 is greater than or equal to the string length of tempVal2
					strcpy(tempVal1, tempVal1); // techinically proceeds to do noting
				}
				else if (strlen(tempVal1) < strlen(tempVal2)) { // checks if the string length of tempVal1 is smaller than the string length of tempVal2
					strcpy(tempVal1, tempVal2); // copies tempVal2 into tempVal1
					posVal2 = j; // saves the updated position of index j to posVal2
				}
			}
		}
		if (exist == 1) { // checks if exists equals one 
			strcpy(currentVal, words[i]); // copies the word at index i to the array currentVal
			strcpy(words[i], tempVal1); // copies tempVal1 into the array words at index i
			strcpy(words[posVal2], currentVal); // copies the currentVal to the array words at index posVal2
		}
	}

}

int check_valid(char words[20][16], FILE* input, FILE* output) {

	int n = 0; // initializes the variable n to zero

	while (1) {
		
		char buffer[50]; // establishes a buffer array
		fgets(buffer, 49, input); // reads in line by line the word according to the specified user's input (either from stdin or from a data file)
		if (buffer[strlen(buffer) - 1] == '\n') { // checks if buffer at index string length of buffer minus one equals the new line character
			buffer[strlen(buffer) - 1] = '\0'; // replaces the new line character at buffer at index string length of buffer minus one with the null character
		}

		int size = strlen(buffer); // stores the size of the string in buffer

		if (strcmp(buffer, ".") == 0) { // checks if buffer equals the string period
			strcpy(words[n], "\0"); // appends the words array at index n with the null character
			break;
		}
		else {
			int j;
			int error = 0; // initializes the error variable to zero
			for (j = 0; j < size; j++) { // goes through each of the letters at buffer from index zero to index size minus one
				if ((((int)(buffer[j]) >= 65 && (int)(buffer[j]) <= 90) || ((int)(buffer[j]) >= 97 && (int)(buffer[j]) <= 122)) && (size >= 2 && size <= 15)) { // checks if buffer at index j corresponds to just only alphabets and checks if the size of the string is at least greater than two and less than or equal to fifteen
					continue;
				}
				else {
					error = 1; // the error variable becomes one
					fprintf(output, "The word you enter is either too short, too long, or consists of an invalid character!");
					fprintf(output, "\n");
					break;
				}
			}
			if (error == 0) { // checks if the error variable is still equal to zero 
				strncpy(words[n], buffer, 16); // copies buffer into the array words at index n
				n++; // increments the value of n by one
			}
		}
		if (n == 20) { // checks if n equals to twenty
			break;
		}
	}
	
	return n;
	
}
	
void init_board(char arr[15][15]) {

	for (int i = 0; i < 15; i++) { // goes through each rows of arr
		for (int j = 0; j < 15; j++) { // goes through each letters in arr
			arr[i][j] = '.'; // initializes all index of the board to just periods
		}
	}

}

int crossword (char arr_words[20][16], char arr_board[15][15], Board arr_clues[20], FILE* output, int count) {
	
	int n_words_passed = 0; // initializes n_words_passed to zero
	int n_word = 0; // initializes n_word to zero
	char board_words[20][16]; 

	int longest_word_column = floor(((15 - strlen(arr_words[0])) / 2)); // finds the first column in the board of where the word can be placed
	arr_clues[n_words_passed].row = 7; // stores the row of the first word in the struct arr_clues at index n_words_passed
	arr_clues[n_words_passed].column = longest_word_column; // stores the column of the first word in the struct arr_clues at index n_words_passed
	strcpy(arr_clues[n_words_passed].direction, "Across"); // stores the direction of the first word in the struct arr_clues at index n_words_passed
	strcpy(board_words[n_word], arr_words[n_word]); // copies the first word from arr_words at index n_word to board_words at index n_word
	strcpy(arr_clues[n_words_passed].scrambled, strfry(board_words[n_word])); // copies the anagram of the first word from board_words at index n_word to arr_clues at index n_words_passed

	for (int i = 0; i < strlen(arr_words[0]); i++) { // goes through each letter of the first word 
		arr_board[7][longest_word_column] = arr_words[0][i]; // stores the first word into the arr_board
		longest_word_column++; // increments the value of longest_word_column by one
	}

	while (n_word < count) { // checks if n_word is less than count

		n_word++; // increments the value of n_word by one
		
		int fit_horizontal = 0; // initializes the flag variable fit_horizontal to zero
		int fit_vertical = 0; // initializes the flag variable fit_vertical to zero
		int row_intersect, col_intersect, char_intersect; 

		for (int board_row = 0; board_row < 15; board_row++) { // goes through the rows of the board
			for (int board_col = 0; board_col < 15; board_col++) { // goes through the columns of the board
				if ((int) arr_board[board_row][board_col] >= 65 && (int) arr_board[board_row][board_col] <= 90) { // checks if arr_board at row board_row and column board_col is an upper case alphabet letter
					for (int char_word = 0; char_word < strlen(arr_words[n_word]); char_word++) { // goes through the letters of the word 
						if (arr_board[board_row][board_col] == arr_words[n_word][char_word]) { // checks if arr_board at row board_row and column board_col is equal to arr_words at row n_word and column char_word
							fit_horizontal = 1; // sets the variable fit_horizontal to one
							if (fit_horizontal == 1) { // checks if fit_horizontal is equal to one
								if (board_col - char_word < 0 || board_col + strlen(arr_words[n_word]) - char_word - 1 > 14) { // checks if the column of the first letter of the word is less than zero or the column of the last letter of the word is greater than fourteen 
									fit_horizontal = 0; // initalizes the flag variable fit_horizontal to zero
								}
							}
							if (fit_horizontal == 1) { // checks if fit_horizontal equals one
								for (int neighbor_row = board_row - 1; neighbor_row <= board_row + 1; neighbor_row++) { // goes through the previous intersecting row up until a row after the intersecting row 
									for (int neighbor_col = board_col - char_word; neighbor_col < board_col + strlen(arr_words[n_word]) - char_word; neighbor_col++) { // goes through the column in the board in which the first letter of the word will be placed up until the column in which the last letter of the word will be placed
										if ((int) arr_board[board_row][neighbor_col] >= 65 && (int) arr_board[board_row][neighbor_col] <= 90) { // checks if the arr_board at row board_row and column neighbor_col corresponds to the upper case alphabet letters
											if (arr_words[n_word][neighbor_col - board_col + char_word] == arr_board[board_row][neighbor_col]) { // checks if there is any more intersecting letters at arr_board and arr_word
												continue;
											}
											else {
												fit_horizontal = 0; // sets the value of fit_horizontal to zero
											}
										}
										else if ((int) arr_board[board_row][neighbor_col] == 46) { // checks if the arr_board at row board_row and column neighbor_col is equal to a period
											if (board_row - 1 < 0) { // checks if the row before the intersecting row is less than zero
												if (neighbor_row == board_row - 1) { // checks if the neighbor_row equals the board_row minus one
													continue;
												}
												else {
													if ((int) arr_board[neighbor_row][neighbor_col] == 46) { // checks if the arr_board at row neighbor_row and column neighbor_col equals to a period
														continue;
													}
													else {
														fit_horizontal = 0; // sets the value of fit_horizontal to zero
													}
												}
											}
											else if (board_row + 1 > 14) { // checks if the row after the intersecting row is greater than fourteen
												if (neighbor_row == board_row + 1) { // checks if the neighbor_row equals the board_row plus one
													continue;
												}
												else {
													if ((int) arr_board[neighbor_row][neighbor_col] == 46) { // checks if the arr_board at row neighbor_row and column neighbor_col is equal to a period
														continue;
													}
													else {
														fit_horizontal = 0; // sets the value of fit_horizontal to zero
													}
												}
											}
											else {
												if ((int) arr_board[neighbor_row][neighbor_col] == 46) { // checks if the arr_board at row neighbor_row and column neighbor_col is equal to a period 
													continue;
												}
												else {
													fit_horizontal = 0; // sets the value of fit_horizontal to zero
												}
											}
										}
									}
								}
							}
							if (fit_horizontal == 1) { // checks if fit_horizontal is equal to one
								if (board_col - char_word - 1 < 0) { // checks if board_col minus the char_word minus one is less than zero
									fit_horizontal = 1; // sets the value of fit_horizontal to one
								}
								else {
									if (arr_board[board_row][board_col - char_word - 1] == 46) { // checks if the arr_board at row board_row and column board_col minus char_word minus one is equal to a period
										fit_horizontal = 1; // sets the value of fit_horizontal to one
									}
									else {
										fit_horizontal = 0; // sets the value of fit_horizontal to zero
									}
								}
							}
							if (fit_horizontal == 1) { // checks if fit_horizontal is equal to one 
								if (board_col + strlen(arr_words[n_word]) - char_word > 14) { // checks if the board_col plus the string length of arr_words at index n_word minus the char_word is greater than fourteen
									fit_horizontal = 1; // sets the value of fit_horizontal to one
								}
								else {
									if (arr_board[board_row][board_col + strlen(arr_words[n_word]) - char_word] == 46) { // checks if the arr_board at row board_row and column board_col plus the string length of arr_words at index n_word minus char_word is equal to a period
										fit_horizontal = 1; // sets the value of fit_horizontal to one
									}
									else {
										fit_horizontal = 0; // sets the value of fit_horizontal to zero
									}
								}
							}
							if (fit_horizontal == 1) { // checks if fit_horizontal is equal to one
								row_intersect = board_row; // stores the board_row into the row_intersect
								col_intersect = board_col; // stores the board_col into the col_intersect
								char_intersect = char_word; // stores the char_word into char_intersect
								break;
							}
						}
					}
				}
				if (fit_horizontal == 1) { // checks if fit_horizontal is equal to one
					break;
				}
			}
			if (fit_horizontal == 1) { // checks if fit_horizontal is equal to one
				break;
			}
		}

		if (fit_horizontal == 0) { // checks if fit_horizontal is equal to zero
			for (int board_row = 0; board_row < 15; board_row++) { // goes through the row of the board
				for (int board_col = 0; board_col < 15; board_col++) { // goes through the column of the board
					if ((int) arr_board[board_row][board_col] >= 65 && (int) arr_board[board_row][board_col] <= 90) { // checks if arr_board at index board_row and column board_col is equal to upper case alphabet letters
						for (int char_word = 0; char_word < strlen(arr_words[n_word]); char_word++) { // goes through the letters of the word 
							if (arr_board[board_row][board_col] == arr_words[n_word][char_word]) { // checks if arr_board at row board_row and column board_col is equal to arr_words at row n_word and column char_word
								fit_vertical = 1; // initializes the flag variable fit_vertical to one
								if (fit_vertical == 1) { // checks if fit_vertical is equal to one
									if (board_row - char_word < 0 || board_row + strlen(arr_words[n_word]) - char_word - 1 > 14) { // checks if the row in the board that corresponds to the first letter of the word is less than zero or the row in the board that corresponds to the last letter of the word is greater than fourteen
										fit_vertical = 0; // sets the value of fit_vertical to zero
									}
								}
								if (fit_vertical == 1) { // checks if fit_vertical is equal to one
									if (board_row - char_word - 1 < 0) { // checks if the row in the board that corresponds to the first letter of the word is less than zero
										fit_vertical = 1; // sets the value of fit_vertical is equal to one
									}
									else {
										if (arr_board[board_row - char_word - 1][board_col] == 46) { // checks if arr_board at row board_row minus char_word minus one and column board_col is equal to a period
											fit_vertical = 1; // sets the value of fit_vertical to one
										}
										else {
											fit_vertical = 0; // sets the value of fit_vertical to zero
										}
									}
								}
								if (fit_vertical == 1) { // checks if fit_vertical is equal to one
									for (int neighbor_row = board_row - char_word; neighbor_row < board_row + strlen(arr_words[n_word]) - char_word; neighbor_row++) { // goes through the row that corresponds to the first letter of the word up until the row that corresponds to the last letter of the word
										for (int neighbor_col = board_col - 1; neighbor_col <= board_col + 1; neighbor_col++) { // goes through the column before the intersecting column up until the column after the intersecting column
											if ((int) arr_board[neighbor_row][board_col] >= 65 && (int) arr_board[neighbor_row][board_col] <= 90) { // checks if the arr_board at row neighbor_row and column board_col is equal to the upper case alphabet letters
												if (arr_words[n_word][neighbor_row - board_row + char_word] == arr_board[neighbor_row][board_col]) { // checks if there is any more intersecting letters in the board with the word 
													continue;
												}
												else {
													fit_vertical = 0; // sets the value of fit_vertical to zero
												}
											}
											else if ((int) arr_board[neighbor_row][board_col] == 46) { // checks if arr_board at row neighbor_row and column board_col is equal to a period
												if (board_col - 1 < 0) { // checks if the column before the intersecting column is less than zero
													if (neighbor_col == board_col - 1) { // checks if the neighbor_col equals the board_col minus one
														continue;
													}
													else {
														if ((int) arr_board[neighbor_row][neighbor_col] == 46) { // checks if the arr_board at row neighbor_row and column neighbor_col equals to a period
															continue;
														}
														else {
															fit_vertical = 0; // sets the value of fit_vertical to zero
														}
													}
												}
												if (board_col + 1 > 14) { // checks if the column after the intersecting column is greater than fourteen
													if (neighbor_col == board_col + 1) { // checks if the neighbor_col equals the board_col plus one
														continue;
													}
													else {
														if ((int) arr_board[neighbor_row][neighbor_col] == 46) { // checks if arr_board at row neighbor_row and column neighbor_col is equal to a period
															continue;
														}
														else {
															fit_vertical = 0; // sets the value of fit_vertical to zero
														}
													}
												}
												else {
													if ((int) arr_board[neighbor_row][neighbor_col] == 46) { // checks if arr_board at row neighbor_row and column neighbor_col is equal to a period
														continue;
													}
													else {
														fit_vertical = 0; // sets the value of fit_vertical to zero
													}
												}
											}
										}
									}
								}
								if (fit_vertical == 1) { // checks if fit_vertical is equal to one
									if (board_row + strlen(arr_words[n_word]) - char_word > 14) { // checks if board_row plus the string length of arr_words at index n_word minus char_word is greater than fourteen
										fit_vertical = 1; // sets the value of fit_vertical to one
									}
									else {
										if (arr_board[board_row + strlen(arr_words[n_word]) - char_word][board_col] == 46) { // checks if arr_board at row board_row plus string length of arr_words at index n_word minus char_word and column board_col is equal to a period
											fit_vertical = 1; // sets the value of fit_vertical to one
										}
										else {
											fit_vertical = 0; // sets the value of fit_vertical to zero
										}
									}
								}
								if (fit_vertical == 1) { // checks if fit_vertical is equal to one
									row_intersect = board_row; // stores the board_row into row_intersect
									col_intersect = board_col; // stores the board_col into col_intersect
									char_intersect = char_word; // stores the char_word into char_intersect
									break;
								}
							}
						}
					}
					if (fit_vertical == 1) { // checks if fit_vertical is equal to one
						break;
					}
				}
				if (fit_vertical == 1) { // checks if fit_vertical is equal to one
					break;
				}
			}
		}
		if (fit_horizontal == 1) { // checks if fit_horizontal is equal to one
			int print_char = 0; // initializes print_char to zero
			for (int n = col_intersect - char_intersect; n < col_intersect - char_intersect + strlen(arr_words[n_word]); n++) { // goes through the column that corresponds to the first letter of the word up until the column that corresponds to the last letter of the word
				arr_board[row_intersect][n] = arr_words[n_word][print_char]; // stores arr_word at row n_word and column print_char to arr_board at row row_intersect and column n
				print_char++; // increment the print_char value by one
			}
			n_words_passed++; // increment the n_words_passed value by one
			strcpy(board_words[n_words_passed], arr_words[n_word]); // copies the word from arr_words at index n_word to board_words at index n_words_passed
			arr_clues[n_words_passed].row = row_intersect; // sets the struct arr_clues at index n_words_passed of row to row_intersect
			arr_clues[n_words_passed].column = col_intersect - char_intersect; // sets the struct arr_clues at index n_words_passed of direction to col_intersect minus char_intersect
			strcpy(arr_clues[n_words_passed].direction, "Across"); // copies the string "Across" into the struct arr_clues at index n_words_passed of direction
			strcpy(arr_clues[n_words_passed].scrambled, strfry(board_words[n_words_passed])); // copies the anagram of the word from board_words at index n_words_passed to the struct arr_clues at index n_words_passed of scrambled
		}
		if (fit_vertical == 1) { // checks if fit_vertical is equal to one
			int print_char = 0; // initializes the print_char to zero
			for (int n = row_intersect - char_intersect; n < row_intersect - char_intersect + strlen(arr_words[n_word]); n++) { // goes through the row that corresponds to the first letter of the word up until the row that corresponds to the last letter of the word
				arr_board[n][col_intersect] = arr_words[n_word][print_char]; // stores the arr_words at row n_word and column print_char to arr_board at row n and column col_intersect
				print_char++; // increments the value of print_char by one
			}
			n_words_passed++; // increments the n_words_passed by one
			strcpy(board_words[n_words_passed], arr_words[n_word]); // copies the word from arr_words at index n_word to board_words at index n_words_passed
			arr_clues[n_words_passed].row = row_intersect - char_intersect; // sets the struct arr_clues at index n_words_passed of row to row_intersect minus char_intersect
			arr_clues[n_words_passed].column = col_intersect; // sets the struct arr_clues at index n_words_passed of column to col_intersect
			strcpy(arr_clues[n_words_passed].direction, "Down"); // copies the string "Down" to the struct arr_clues at index n_words_passed of direction
			strcpy(arr_clues[n_words_passed].scrambled, strfry(board_words[n_words_passed])); // copies the anagram of the word from board_words at index n_words_passed to the struct arr_clues at index n_words_passed of scrambled
		}
		if (fit_horizontal == 0 && fit_vertical == 0) { // checks if fit_horizontal and fit_vertical is equal to zero
			fprintf(output, "It is not possible to display %s in one go!", arr_words[n_word]);
			fprintf(output, "\n");	
		
		}
		if (n_word == count - 1) { // checks if the n_word is equal to count minus one
			break;
		}
	}

	return n_words_passed;

}		
		
void display_solution(char arr[15][15], FILE* output) {
	
	fprintf(output, "+");
	for (int i = 0; i < 15; i++) { 
		fprintf(output, "-");
	}
	fprintf(output, "+");
	fprintf(output, "\n");

	for (int i = 0; i < 15; i++) { // goes through the row of the board
		fprintf(output, "|");
		for (int j = 0; j < 15; j++) { // goes through the column of the board
			fprintf(output, "%c", arr[i][j]); // display the character stored at arr at row i and column j to the user
		}
		fprintf(output, "|");
		fprintf(output, "\n");
	}

	fprintf(output, "+");
	for (int i = 0; i < 15; i++) {
		fprintf(output, "-");
	}
	fprintf(output, "+");
	fprintf(output, "\n");	
	

}

void display_puzzle(char arr[15][15], FILE* output) {

	fprintf(output, "+");
	for (int i = 0; i < 15; i++) {
		fprintf(output, "-");
	}
	fprintf(output, "+");
	fprintf(output, "\n");

	for (int i = 0; i < 15; i++) { // goes through the row of the board
		fprintf(output, "|");
		for (int j = 0; j < 15; j++) { // goes through the column of the board
			if ((int) arr[i][j] >= 65 && (int) arr[i][j] <= 90) { // checks if arr at row i and column j is equal to the upper case alphabet letters
				fprintf(output, " ");
			}
			else if ((int) arr[i][j] == 46) { // checks if arr at row i and column j is equal to a period
			fprintf(output, "#");
			}
		}
		fprintf(output, "|");
		fprintf(output, "\n");
	}

	fprintf(output, "+");
	for (int i = 0; i < 15; i++) {
		fprintf(output, "-");
	}
	fprintf(output, "+");
	fprintf(output, "\n");	

}

void display_clues(Board arr[20], FILE* output, int count) {

	fprintf(output, "Location ");
	fprintf(output, "|");
	fprintf(output, " Direction ");
	fprintf(output, "|");
	fprintf(output, " Anagram ");
	fprintf(output, "\n");

	for (int i = 0; i < count + 1; i++) { // goes through the rows of the struct arr
		fprintf(output, "%5d,%2d ", arr[i].column, arr[i].row); // displays the column and row of each word to the user
		fprintf(output, "|");
		fprintf(output, " ");
		if (strcmp(arr[i].direction, "Across") == 0) {  // checks if arr at index i of direction is equal to the string "Across"
			fprintf(output, "   %s", arr[i].direction); // displays the direction of the word to the user
		}
		else if (strcmp(arr[i].direction, "Down") == 0) { // checks if arr at index i of direction is equal to the string "Down"
			fprintf(output, "     %s", arr[i].direction); // displays the direction of the word to the user
		}
		fprintf(output, " |");
		fprintf(output, " ");
		fprintf(output, "%s", arr[i].scrambled); // displays the anagram of the word to the user
		fprintf(output, "\n");
	}
	
	fprintf(output, "\n");
	

}
		
