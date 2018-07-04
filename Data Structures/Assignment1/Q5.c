/* CS261- Assignment 1 - Q.5*/
/* Name: Brent Doil	
 * Date: 6/26/2016
 * Solution description: Sticky caps program implementation
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
     /*Convert to sticky caps*/
	for (int i = 0; word[i] != '\0'; i++)
	{
		if (i % 2 != 0)
		{
			if (word[i] >= 'A' && word[i] <= 'Z')
			{
				word[i] = toLowerCase(word[i]);
			}
		}
		else
		{
			
			if (word[i] >= 'a' && word[i] <= 'z')
			{
				word[i] = toUpperCase(word[i]);
			}
		}
	}
}

int main(){
    /*Read word from the keyboard using scanf*/
	char* input = malloc(50*sizeof(char));
	printf("Enter a word (max 50 letters).\n");
	scanf("%s", input);
    /*Call sticky*/
	sticky(input);
    /*Print the new word*/
	printf("%s\n", input);
    return 0;
}
