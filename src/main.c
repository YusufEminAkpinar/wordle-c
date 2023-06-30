#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "time.h"
#include "locale.h"

#define max_char 5
#define fifty_under "--------------------------------------------------"
// #define clear "\e[1;1H\e[2J"
#define green "\033[32m"
#define yellow "\033[33m"
#define pink "\033[35m"
#define end "\033[0m"

/*
TODO:
========================
DONE
1) Fix the buffer overflow... After 5 char next variable will be overwritten by previous input's indexs bigger than 5.
ie: if naughty user enters 12345guess as goalword, the guess has become "guess" without asking user input.
Same thing happens if user enters aaaaabbbbb as guess then it will count it as 2 guess.

CHANGED IT TO 4
2) Remove the letters from wrong_placed_letters if that letter will located correctly in next attemps.

DONE 
3) Can't win the game. Make it possible.

4) Put some colors in it and give it a better look.

DONE
5) Find a way for strings that contains same character twice.

DONE
6) Implement random chooser.

DONE
7) Seperate the known and wrong placed letters like previous commits and also print out the eliminated letters.

8) Add a Turkish language support.

9) I don't know why but guess can't be validated after third guess. Solve it.
*/

/* Function Declarations */
void toLowerCase(char string[]);
char *randomWord(void);
char *chooseOwnWord(void);
char *introScreen(void);
void mainGame(char *goalWord);
char *colorfulChar(char color[], char known_char[], int point);
int *arr_of_correct_places(char word1[], char word2[]);
bool isPresent(int num, int *arr, int arrSize);
int num_of_occur(char c, char word[]);
bool isValid(FILE *file, char *word);


/* Variable Declarations */
int chances = 6;


#define gets

int main(void) {
	mainGame(introScreen());
//	FILE *f = fopen("../words.txt", "r");
//	bool c = isValid(f, "phone");
    	return 0;
}

bool isValid(FILE *file, char *word){
	char line[7];
	if (file != NULL) {
		while (fgets(line, sizeof(line), file) != NULL) {
			//printf("line is %s", line);
			if (!(strncmp(line, word, 5))) {
				return true;
			}
		}
	}
	return false;
}

int num_of_occur(char c, char word[]){
	int k = 0;
	for (size_t i = 0; i<strlen(word); i++) {
		if (c == word[i]) {
			k++;
		}
	}
	return k;
}


int *arr_of_correct_places(char word1[], char word2[]){
	int *arr = malloc(sizeof(int)*5);
	int k = 0;
	for (size_t i = 0; i<strlen(word1); i++) {
		if (word1[i] == word2[i]) {
			arr[k+1] = i;
			k++;
		}
	}
	arr[0] = k; // first byte is the number of non-empty elements. like size of an array.
	return arr;
}

void toLowerCase(char string[]){
	for (int i = 0; string[i] != '\0'; ++i)
	{
		if(string[i] >= 'A' && string[i] <= 'Z')
			string[i] = string[i] + 32;
		else 
			string[i] = string[i];	
	}
}


char *colorfulChar(char color[], char known_char[], int point){
	char *colored_text = malloc(strlen(color) + strlen(end) + strlen(known_char));

	/* paint a spesific char */
	strcat(colored_text, color);
	strncat(colored_text, &known_char[point], 1);
	strcat(colored_text, end);

	/* before char word */
	char beforecolor[strlen(known_char)];
	strcpy(beforecolor, known_char);	
	beforecolor[point] = '\0';

	/* after char word */
	char aftercolor[strlen(known_char)];
	memmove(aftercolor, known_char+point+1, strlen(known_char)-point);


	strcat(beforecolor, colored_text);
	strcat(beforecolor, aftercolor);
	strcpy(colored_text, beforecolor);
	// printf("%s\n", beforecolor);
	return colored_text;
}


char *randomWord(void){
	char *word = malloc(sizeof(char) * 50);
	srand(time(NULL));
	int r = rand() % 5688;
	int k = 0;
	FILE *file = fopen("../words.txt", "r");
	if (file != NULL) {
		while (fgets(word, 50, file) != NULL){
			if(k == r){
				fclose(file);
				return word;	
			}
			k++;
		}
	}
	else {
		fprintf(stderr, "%s\n", "File can not be opened.");
	}
	fclose(file);
	return NULL;
}


char *chooseOwnWord(void){
	char *goalWord = malloc(sizeof(char) * max_char);
	char *temp = malloc(sizeof(char) * max_char);
	FILE *file = fopen("../words.txt", "r");
    RESET:printf("Please enter your guess: \n");
	scanf("%s", temp);
	if (strlen(temp) != max_char)
	{
		printf("\nPlease enter 5 character world\n");
		goto RESET;
	}
	if (!(isValid(file, temp))){
		printf("Please enter a valid word.\n");
		goto RESET;
	}
	system("clear");
	printf("The word has been choosed by thy almighty user.\n");
	strncpy(goalWord, temp, max_char);
	free(temp);
	fclose(file);
	toLowerCase(goalWord);
	return goalWord;
}

char *introScreen(void){
	system("clear");
	// printf(clear);
	printf(" %s\n|\t\t\t\t\t\t   |\n|\t    Welcome to the Wordle game.\t\t   |\n|\t\t\t\t\t\t   |\n %s\n", fifty_under, fifty_under);
	CHOOSE:printf("Please choose an option:\n  \033[34m1)\033[0m Choose a certain word\n  \033[34m2)\033[0m Let program choose a random word\n  \033[34m3)\033[0m Instructions\n\n  >> ");
	int option;
	char *goalWord;
	scanf("%d", &option);
	switch (option)
	{
	case 1: printf("Okay then choose a 5 letter word\n");
		goalWord = chooseOwnWord();
		break;
	case 2: printf("Computer will choose a word for you\n");
		goalWord = randomWord();
		break;
	case 3: printf("There is a secret word which contains exacly 5 characters. You have 6 chances for match the secret word. If you can match the exact spot for a character, it will turn to green. And it will turn to yellow if you can't. That's all about this game. Now please choose a option to start a game. \n\n\n");
		goto CHOOSE;
		break;
	default: printf("Invalid option\n");
		goto CHOOSE;
	}
	return goalWord;
}


bool isPresent(int num, int *arr, int arrSize){
	for (int i = 1; i<arrSize; i++) {
		if (num == arr[i]) {
			return true;
		}
	}
	return false;
}


bool isPresentStr(char c, char *str){
	for (size_t i = 0; i<strlen(str); i++) {
		if (c == str[i]) {
			return true;
		}
	}
	return false;
}


void mainGame(char *goalWord){
	char *tmp = malloc(sizeof(char) * max_char);
	char *guess = malloc(sizeof(char) * max_char);
	FILE *file = fopen("../words.txt", "r");
	char *last_state = malloc(sizeof(char) * max_char);
	char *eliminated = malloc(sizeof(char) * 50);
	int k = 0;
	bool is_elim;
	while (chances != 0){
		for (int i = 0; i<max_char; i++) {
			last_state[i] = '_';
		}
		RESET:printf("Please enter your guess: \n");
		scanf("%s", tmp);
		if (strlen(tmp) != max_char)
		{
			printf("\nPlease enter 5 character world\n");
			goto RESET;
		}
		strncpy(guess, tmp, max_char);
		free(tmp);
		if (!(isValid(file, guess))) {
			printf("The word %s, is not a valid word according to the dictionary. Please enter antoher one.\n", guess);
			goto RESET;
		}

		if (!(strncmp(guess, goalWord, 5))) {
			printf("Congratulations. You've won.\n");
			break;
		}

		int *arr = arr_of_correct_places(guess, goalWord);
		for (int i = 0; i < max_char; ++i)
		{
			is_elim = true;
			for (int j = 0; j < max_char; ++j)
			{
				if ((guess[i] == goalWord[j]) && (i==j))
				{
					/* printf("Letter %c is in correct place.\n", guess[i]); */
					last_state[i] = (char)(guess[i] - 32);
					is_elim = false;
					/* guess = colorfulChar(green, guess, i); */
				}
				else if (guess[i] == goalWord[j] && !(isPresent(j, arr, arr[0])) &&
						 !(num_of_occur(guess[i], guess) - num_of_occur(guess[i], goalWord) > 0))
				{
					/* printf("Letter %c is exist but in wrong place.\n", guess[i]); */
					last_state[i] = guess[i];
					is_elim = false;
					/* guess = colorfulChar(pink, guess, i); */
				}
			}
			if (is_elim && !(isPresentStr(guess[i], eliminated))) {
				eliminated[k] = guess[i];
				k++;
				eliminated[k] = ' ';
				k++;
			}
		}
		chances--;
		free(guess);
		free(arr);
		printf("\n\nThe last state of the word is:\n");
		printf(" \t%s\t\t\t\tYou have %d chances left.\t\tEliminated keys are: %s\t\n", last_state, chances, eliminated);
		free(last_state);
		// printf("\n\n%s\n\n", chances, fifty_under);
}
}
