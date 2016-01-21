/******************************************************************************
filename    primes1.c
author      Haven Breithaupt
DP email    h.breithaupt@digipen.edu
course      CS120
assignment  lab 4
due date    10/15/2014

Brief Description: first function checks if a number is prime. Second function 
  finds two prime numbers that sum to a given even number.
  
******************************************************************************/

/******************************************************************************
   Function: is_prime

Description: checks if a given number is prime

     Inputs: number - a number to be checked if it's prime
     
    Outputs: true - number is prime
             false - number is not prime
******************************************************************************/
#include <stdio.h> /* printf */

#define FALSE 0 /* number is not prime */
#define TRUE  1 /* number is prime */


int is_prime(int number)
{
  int i;          /* loop counter */
  int remainder;  /* remainder of given number % iteration of odd number */
  
  if(number == 2) /* special case: number 2 is prime */
    return TRUE;
  
  if(number == 1) /* special case: number 1 is not prime */
    return FALSE;
  
  if(number % 2 == 0) /* even numbers */
    return FALSE;
  
  for(i = 3; i < number/2; i += 2) 
  {
    remainder = number % i; /* divides number by iteration of odd number */
    
    if(remainder == 0)      /* if remainder is 0, then number can't be prime */
      return FALSE;
  }
  
  return TRUE;              /* given number is prime */
}


/*******************************************************************************
   Function: conjecture

Description: finds two prime numbers that sum to given even number

     Inputs: low - minimun prime number to check
             high - maximum number to check
             
    Outputs: two prime numbers that sum to even number
*******************************************************************************/
void conjecture(int low, int high)
{
  int i, j;                       /* loop counters */
  
  for(i = low; i <= high; i += 2) /* generates even numbers */
  {
    for(j = 2; j < i; j++)        /* generates number */
    {
        /* checks if j is prime and if the difference of i - j if prime
         * with a third check of i + the differece = i */
      if(is_prime(j) && is_prime(i - j) && i == j + (i - j)) 
      {
        printf("%3i = %3i + %3i\n", i, j, i - j); /* prints the found pair */
        break;                   /* breaks when first pair is found */
      }
    }
  }
}
