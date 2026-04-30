// Author: Cole Sakai
// Date: 04/21/2026
// Purpose: Project 10

#include <stdio.h>

#define TEXT "mystery.txt"
#define WORD_MAX 6
#define MAX_GUESS 6

void openText(char word[]);
void lowerCase(char guess[]);
int guessCheck(char guess[]);
void guessToList(char guessList[], char guess[]);
void makeBoard(char guessList[MAX_GUESS][WORD_MAX], int guessCount, char word[]);
void wordCheck(char guess[], char word[]);
int checkWin(char guess[], char word[]);

int main(){
	char word[WORD_MAX];
	char guess[WORD_MAX];
	char guessList[MAX_GUESS][WORD_MAX];

	openText(word);

	int guessCount = 0;

	while(guessCount < MAX_GUESS){
		printf("GUESS %d! Enter your guess: ", guessCount + 1);
		scanf("%s", guess);

		lowerCase(guess);

		while(guessCheck(guess) == 0){
			printf("Your guess must be 5 letters long and contain only letters.\n");
			printf("Please try again: ");
			scanf("%s", guess);
			lowerCase(guess);
		}

		guessToList(guessList[guessCount], guess);
		guessCount++;

		printf("================================\n");
		makeBoard(guessList, guessCount, word);

		if(checkWin(guess, word) == 1){
			printf("================================\n");
			printf("            %s\n", word);
			printf("     You won in %d guesses", guessCount);

			printf("!\n");

			if (guessCount == 1){
				printf("            GOATED!\n");
			}
			else{
				printf("           Amazing!\n");
			}
			return 0;
		}
	}

    printf("You lost, better luck next time!\n");

    return 0;
}

void openText(char word[]){
	FILE *fp = fopen(TEXT, "r");

	if(fp == NULL){
		printf("Could not open %s, goodbye!\n", TEXT);
		return;
	}

	fscanf(fp, "%5s", word);
	fclose(fp);
}

void lowerCase(char guess[]){
	int i;

	for(i = 0; guess[i] != '\0'; i++){
		if(guess[i] >= 'A' && guess[i] <= 'Z'){
			guess[i] += 32;
		}
	}
}

int guessCheck(char guess[]){
	int i;
	int letters = 0;

	for(i = 0; guess[i] != '\0'; i++){
		letters++;

		if(!((guess[i] >= 'A' && guess[i] <= 'Z') || (guess[i] >= 'a' && guess[i] <= 'z'))){
			return 0;
		}
	}

	if(letters != 5){
		return 0;
	}

	return 1;
}

void guessToList(char guessList[], char guess[]){
	int i;

	for(i = 0; guess[i] != '\0'; i++){
		guessList[i] = guess[i];
	}

	guessList[i] = '\0';
}

void makeBoard(char guessList[MAX_GUESS][WORD_MAX], int guessCount, char word[]){
	int i;

	for(i = 0; i < guessCount; i++){
		wordCheck(guessList[i], word);
	}
}

void wordCheck(char guess[], char word[]){
	char display[WORD_MAX];
	char arrows[WORD_MAX];

	int i, j;

	for(i = 0; i < 5; i++){
		display[i] = guess[i];
		arrows[i] = ' ';
	}

	display[5] = '\0';
	arrows[5] = '\0';

	for(i = 0; i < 5; i++){
		if(guess[i] == word[i]){
			display[i] = guess[i] - 32;
		}
	}

	for(i = 0; i < 5; i++){
		if(guess[i] != word[i]){
			for(j = 0; j < 5; j++){
				if(guess[i] == word[j] && guess[j] != word[j]){
					arrows[i] = '^';
				}
			}
		}
	}

	printf("%s\n", display);
	printf("%s\n", arrows);
}

int checkWin(char guess[], char word[]){
	int i;

	for(i = 0; i < 5; i++){
		if(guess[i] != word[i]){
			return 0;
		}
	}

	return 1;
}
