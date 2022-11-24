#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#define max_char 5
#define fifty_under "--------------------------------------------------"
// #define clear "\e[1;1H\e[2J"
#define green "\033[32m"
#define yellow "\033[33m"
#define end "\033[0m"

/*
TODO:
========================
DONE (I have officially solved my first memory overflow i'm so happy lol)
1) Fix the fuckin buffer overflow... After 5 char next variable will be overwritten by previous input's indexs bigger than 5.
ie: if naughty user enters 12345guess as goalword, the guess has become "guess" without asking user input.
Same thing happens if user enters aaaaabbbbb as guess then it will count it as 2 guess.

CHANGED IT TO 4
2) Remove the letters from wrong_placed_letters if that letter will located correctly in next attemps.

DONE 
3) Can't win the game. Make it possible.

4) Put some colors in it and give it a better look.
*/

/* Function Declarations */
void toLowerCase();
char *removeDuplicate();
bool checkDupe();
bool isEqual();
void randomword();
void chooseOwnWord();
void introScreen();
void mainGame();


/* Variable Declarations */
int chances = 6;
char goalWord[max_char];
char guess_input[max_char];
char last_state_word[] = "_____";
char temp[max_char];


int main(int argc, char *argv[])
{
	introScreen();
	
	mainGame();
	return 0;
}

bool isEqual(char word1[], char word2[]){
	int sizew1 = strlen(word1);
	int sizew2 = strlen(word2);
	if (sizew1 > sizew2) /* making word2 a larger one. */
	{
		char tmp[strlen(word1)];
		strcpy(tmp, word1); 
		strcpy(word1, word2); 
		strcpy(word2, tmp); 
	}
	
	for (int i = 0; word2[i] != '\0'; i++)
	{
		if (word2[i] != word1[i])
			return false;
	}
	return true;
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

bool checkDupe(char word[]){
	for (int i = 0; word[i] != '\0'; i++)
	{
		for (int j = i+1; word[j] != '\0'; j++)
		{
			if (word[i] == word[j])
				return false;
		}
	}
	return true;
}

char *removeDuplicate(char word[]){
    char *new_word = malloc(sizeof(char) * strlen(word));
	/* I do not know if there is better way to do this but it looks really *loopy*... */
	strcpy(new_word, word);
	while (!checkDupe(new_word)) /* Continue to run until no more duplicate */
	{
		for (int i = 0; i < new_word[i] != '\0'; i++)
		{
			for (int j = i+1; new_word[j] != '\0'; j++)
			{
				if (new_word[i] == new_word[j])
				{
					for (int k = j; k <= (int)strlen(new_word); k++)
					{
						new_word[k] = new_word[k+1];
					}
				}		
			}	
		}
	}
    return new_word;
}

void randomWord(){

}

char *colorfulChar(char color[], char known_char){
	char *colored_text = malloc(strlen(color) + sizeof(end) + sizeof(known_char));
	strcat(colored_text, color);
	strncat(colored_text, &known_char, 1);
	strcat(colored_text, end);
	return colored_text;
}

void chooseOwnWord(){
	char goalWord[max_char];
	char temp[max_char];
	printf("Please enter the goal word: ");
	scanf("%s", temp);
	system("clear");
	printf("Well okay you have choose your word.\n");
	strncpy(goalWord, temp, max_char);
	toLowerCase(goalWord);
}

void introScreen(){
	system("clear");
	// printf(clear);
	printf(" %s\n|\t\t\t\t\t\t   |\n|\t    Welcome to the Wordle game.\t\t   |\n|\t\t\t\t\t\t   |\n %s\n", fifty_under, fifty_under);
	CHOOSE:printf("Please choose an option:\n  \033[34m1)\033[0m Choose a certain word\n  \033[34m2)\033[0m Let program choose a random word\n  \033[34m3)\033[0m Instructions\n\n  >> ");
	int option;
	scanf("%d", &option);
	switch (option)
	{
	case 1: printf("Okay then choose a 5 letter word\n");
		chooseOwnWord();
		break;
	case 2: printf("Computer choose a word for you\n");
		randomWord();
		break;
	case 3: printf("There is a secret word which contains exacly 5 characters. You have 6 chances for match the secret word. If you can match the exact spot for a character, it will turn to green. And it will turn to yellow if you can't. That's all about this game. Now please choose a option to start a game. \n\n\n");
		goto CHOOSE;
		break;
	default: printf("Invalid option\n");
		goto CHOOSE;
	}
}


void startScreen(){
	system("clear");
	// printf(clear);
	
}


void mainGame(){
	while (chances != 0){
		RESET:printf("Please enter your guess: \n");
		scanf("%s", temp);
		if (strlen(temp) != max_char)
		{
			printf("\nPlease enter 5 character world\n");
			goto RESET;
		}
		strncpy(guess_input, temp, max_char);
		toLowerCase(guess_input);
	    char *guess = removeDuplicate(guess_input);


		if (isEqual(guess_input, goalWord)) 
		{
			printf("Congratulations. You've won.\n");
			break;
		}
		for (int i = 0; i < max_char; ++i)
		{
			for (int j = 0; j < max_char; ++j)
			{
				if ((guess[i] == goalWord[j]) && (i==j))
				{
					// printf("Letter %c is in correct place.\n", guess[i]);
					colorfulChar(green, guess[i]);
				}
				else if (guess[i] == goalWord[j])
				{
					// printf("Letter %c is exist but in wrong place.\n", guess[i]);
					colorfulChar(yellow, guess[i]);
				}
			}
		}
        free(guess);
		chances--;
		printf("\n\nThe last state of the word is:\n");
		printf(" \t%s\t\t\t\t\t\t%s\n", guess);
		printf("\nYou have %d chances left.\n%s\n\n", chances, fifty_under);
}

}

