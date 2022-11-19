#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

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

4) Put some colors in it and use ncurses or ctypes to give it a better look.
*/

/* Function Declarations */
char *toUpperCase();
char *removeDuplicate();
bool checkDupe();
bool isEqual();


int main(int argc, char *argv[])
{
	int max_char = 5;
	int index = 0;
	int chances = 5;
	char goalWord[max_char];
	char guess_input[max_char];
	char wrong_placed_letters[] = "     ";
	char last_state_word[] = "_____";
	char fifty_under[] = "--------------------------------------------------";
	char temp[max_char];

	printf("Please enter the goal word: \n");
	scanf("%s", temp);
	strncpy(goalWord, temp, max_char);
	printf("%s\n\tThe game has been started\n%s\n\n", fifty_under, fifty_under);

	while (chances != 0){
		// free(goalWord);
		printf("Please enter your guess: \n");
		scanf("%s", temp);
		if (strlen(temp) < max_char)
		{
			printf("\nPlease enter 5 character world\n");
			chances++;
		}
		strncpy(guess_input, temp, max_char);
		printf("Your guess before remDupe is: %s\n", guess_input);
	    char *guess = removeDuplicate(guess_input);
		printf("Your guess after remDupe is: %s\n", guess_input);
		printf("%s\n\n", fifty_under);
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
					printf("Letter %c is in correct place.\n", guess[i]);
					last_state_word[i] = guess[i];
				}
				else if (guess[i] == goalWord[j])
				{
					printf("Letter %c is exist but in wrong place.\n", guess[i]);
					wrong_placed_letters[index] = guess[i];
					index++;
				}
			}
		}
        free(guess);
		chances--;
		printf("\n\nThe last state of the word is:\t\t\tLetters that in wrong places:\n");
		printf(" \t%s\t\t\t\t\t\t%s\n", last_state_word, wrong_placed_letters);
		printf("\nYou have %d chances left.\n%s\n\n", chances, fifty_under);
	}
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
					for (int k = j; k <= strlen(new_word); k++)
					{
						new_word[k] = new_word[k+1];
					}
				}		
			}	
		}
	}

    return new_word;
}




