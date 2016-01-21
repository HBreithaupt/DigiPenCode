/******************************************************************************
filename    palindrome1.c
author      Haven Breithaupt
DP email    h.breithaupt@digipen.edu
course      CS120
assignment  Assignment 4
due date    10/29/2014

Brief Description:
  Tests if an array is a palindrome using subscript notation.
******************************************************************************/

#define TRUE 1  /* array is palindrome */
#define FALSE 0 /* array is not palindrome */

/******************************************************************************
   Function: is_palindrome1

Description: checks if an array is a palindrome

     Inputs: phrase - an array of constant characters passed from main.c
     
    Outputs: true - is palindrome
             false - is not palindrome
******************************************************************************/
int is_palindrome1(const char phrase[], int length)
{
  int front; /* loop counter, starts at beginning of array */
  int back; /* loop counter, starts at end of array */
  
    /* iterates through array starting from both ends */
  for(front = 0, back = length - 1; front < back; front++, back--)
  {
    if(phrase[front] != phrase[back])
      return FALSE;
  }
  return TRUE;
}