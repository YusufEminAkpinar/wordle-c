#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

/*
TODO:
========================
1) Fix the fuckin buffer overflow... After 5 char next variable has overwritten by word[5:].
ie: if naughty user enters 12345guess as goalword, the guess has become "guess" without asking user input.
Same thing happens if user enters aaaaabbbbb as guess then it will count it as 2 guess.

2) Remove the letters from wrong_placed_letters if that letter will located correctly in next attemps.

3) Can't win the game. Make it possible.

*/


char *toUpperCase();
char *removeDuplicate();
bool checkDupe();


int main(int argc, char *argv[])
{
	int max_char = 6;
	int index = 0;
	int chances = 5;
	char goalWord[max_char];
	char guess_input[max_char];
	char wrong_placed_letters[] = "       ";
	char last_state_word[] = "_____";
	char fifty_under[] = "--------------------------------------------------";

	printf("Please enter the goal word: \n");
	fgets(goalWord, max_char, stdin);
	printf("%s\n\tThe game has been started\n%s\n\n", fifty_under, fifty_under);

	while (chances != 0){
		printf("Please enter your guess: \n");
		scanf("%5s", guess_input);
	    char *guess = removeDuplicate(guess_input);
		printf("Your guess is: %s\n", guess_input);
		// printf("Word was %s\n", goalWord);
		printf("%s\n\n", fifty_under);
		printf("%d\n", guess_input==goalWord);
		if (guess_input == goalWord)
		{
			printf("Congratulations. You've won.\n");
			break;
		}
		for (int i = 0; i < max_char-1; ++i)
		{
			for (int j = 0; j < max_char-1; ++j)
			{
				if ((guess[i] == goalWord[j]) && (i==j))
				{
					// printf("Letter %c is in correct place.\n", guess[i]);
					last_state_word[i] = guess[i];
				}
				else if (guess[i] == goalWord[j])
				{
					// printf("Letter %c is exist but in wrong place.\n", guess[i]);
					wrong_placed_letters[index] = guess[i];
					index++;
				}
			}
		}
        free(guess);
		chances--;
		// printf("\n\nThe last state of the word is:\t\t\tLetters that in wrong places:\n");
		// printf(" \t%s\t\t\t\t\t\t%s\n", last_state_word, wrong_placed_letters);
		// printf("\nYou have %d chances left.\n%s\n\n", chances, fifty_under);
		printf("You have %d chances left.\n", chances);
	}
	return 0;
}


char *toUpperCase(char string[]){
	char *upper = malloc(sizeof(char) * strlen(string));
	for (int i = 0; string[i] != '\0'; ++i)
	{
		if(string[i] >= 'a' && string[i] <= 'z')
			upper[i] = string[i] - 32;
		else 
			upper[i] = string[i];	
	}
	return upper;
}


bool checkDupe(char word[]){
	for (int i = 0; word[i] != '\0'; i++)
	{
		for (int j = i+1; word[j] != '\0'; j++)
		{
			if (word[i] == word[j])
				return true;
		}
	}
	return false;
}


char *removeDuplicate(char word[]){
    char *new_word = malloc(sizeof(char) * strlen(word));
	/* I do not know if there is better way to do this but it looks really *loopy*... */
	while (checkDupe(word)) /* Continue to run until no more duplicate */
	{
		for (int i = 0; i < word[i] != '\0'; i++)
		{
			for (int j = i+1; word[j] != '\0'; j++)
			{
				if (word[i] == word[j])
				{
					for (int k = j; k <= strlen(word); k++)
					{
						word[k] = word[k+1];
					}
				}		
			}	
		}
	}
	strcpy(new_word, word);

    return new_word;
}




