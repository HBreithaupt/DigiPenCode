/******************************************************************************
filename    histogram.c
author      Haven Breithaupt
DP email    h.breithaupt@digipen.edu
course      CS120
assignment  10
due date    11/5/2014

Brief Description:
  Multiple functions that use strings, first counts all characters in a string
  while categorizing them, second function prints out a diagram of how many 
  times a letter is repeated, final function finds the average of the letters
  and the letter used most and how mnay time said letter was used.
******************************************************************************/

#include <stdio.h>     /* printf      */
#include <ctype.h>     /* toupper     */
#include <string.h>    /* strlen      */
#include "histogram.h" /* lab defines */

/******************************************************************************
   Function: GetCounts

Description: counts the number of letters, spaces and other characters 
             in a string

     Inputs: sentence - a pointer to the first element in a string
     
    Outputs: number of letters (A..z)
******************************************************************************/
int GetCounts(const char *sentence, int letters[], int *spaces, int *other)
{
  int i;          /* loop counter */
  int counts = 0; /* initalizes all these values to 0 */
  *spaces = 0;    /* initalize to 0 */
  *other = 0;     /* initalize to 0 */
  
    /* sets all indexes to 0 */
  for(i = 0; i < NUM_LETTERS; i++)
    letters[i] = 0;
  
    /* stores value of all characters in the string in their correct variable */
  for(; *sentence; sentence++)
  {
    if('A' <= toupper(*sentence) && toupper(*sentence) <= 'Z')
    {
        /* keeps track of how many times a letter is repeated */
      letters[toupper(*sentence) - 'A']++;
      counts++;
    }
    else if(*sentence == SPACE)
      (*spaces)++;
    else
      (*other)++;
  }
  
  return counts;  /* number of letters in string */ 
}

/******************************************************************************
   Function: PrintHistogram

Description: prints a diagram of how many times a letter repeated in a string

     Inputs: letters - an array of integers
     
    Outputs: n/a
******************************************************************************/
void PrintHistogram(const int letters[])
{
  int i;          /* loop counter */
  int repeat;     /* keeps track of letter usage for each letter */ 
  
    /* iterates for each letter in alphabet */
  for(i = 0; i < NUM_LETTERS; i++)
  {
    printf("%c:", 'A' + i);
    repeat = 1;
    
      /* prints out * for each time letter is used */
    for(;repeat <= letters[i];)
    {
      printf("*");
      repeat++;
    }
    
    printf("\n"); /* new linw when done printing * for each letter */
  }
}

/******************************************************************************
   Function: GetStatistics

Description: calculates 'average' of the letters in the string and find finds
             finds the letter most used and how many times it was used.

     Inputs: letters - an array of constant integers
     
    Outputs: n/a
******************************************************************************/
void GetStatistics(const int letters[], double *average, char *max_letter, 
                   int *max_count)
{
  int i, j;     /* loop counter */
  
  *average = 0; /* initialize to 0 */
  
    /* calculate sum of letters */
  for(i = 0; i < NUM_LETTERS; i++)
    *average += (i + 1) * letters[i];
  
  *average /= NUM_LETTERS; /* divides total by NUM_LETTERS to get average */
  
  *max_count = letters[0]; /* assumes 'A' is max count for use loop */
  *max_letter = 'A';       /* also assumes 'A' is max letter for use in loop */
  
    /* finds max_count and then uses that index to assign max_letter */
  for(j = 0; j < NUM_LETTERS - 1; j++)
  {
    if(letters[j] > *max_count)
    {
      *max_count = letters[j];
      *max_letter = j + 'A';
    }
  }
}
  