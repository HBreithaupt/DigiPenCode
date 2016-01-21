#include <string.h> /* strtok */
#include "Parser.h"

/*Function to Parse Input*/
unsigned int Parse(char* Input, char* Output[], unsigned int MaxWords)
{
	/*Define Delimiter Set*/
	char Delimiters[] = " \t";
	/*Tokenize*/
	unsigned int WordCount = 0;
	char* CurrentWord = strtok(Input, Delimiters);
	while(CurrentWord != NULL && WordCount < MaxWords)
	{
		/*Set Output*/
		Output[WordCount++] = CurrentWord;
		/*Get Next Word*/
		CurrentWord = strtok(NULL, Delimiters);
	}
	/*Return Words Count*/
	return WordCount;
}
