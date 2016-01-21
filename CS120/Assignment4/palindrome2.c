/******************************************************************************
filename    is_palindrome2.c
author      Haven Breithaupt
DP email    h.breithaupt@digipen.edu
course      CS120
assignment  Assignment 4
due date    10/28/2014

Brief Description:
  Checks if an array is a palindrome using only pointers.
******************************************************************************/

#define TRUE 1  /* array is a palindrome */
#define FALSE 0 /* array is not a palindrome */

/******************************************************************************
   Function: is_palindrome2

Description: tests if an array is a palindrome

     Inputs: phrase - pointer to a the first address in the array
             length - how long the array is
     
    Outputs: true - array is a palindrome
             false - array is not a palindrome
******************************************************************************/
int is_palindrome2(const char *phrase, int length)
{
    /* address of first index in the aray */
  const char *front = phrase;
    
    /* address of last index in the array */
  const char* back = phrase + (length - 1) * sizeof(char);
  
    /* iterates array from both sides */
  for(;front < back;front++, back--)
  {
      /* dereferencing pointers to check values of the index */
    if(*front != *back)
      return FALSE;
  }
  return TRUE;
}
