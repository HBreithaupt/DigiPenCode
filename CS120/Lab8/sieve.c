/******************************************************************************
filename    sieve.c
author      Haven Breithaupt
DP email    h.breithaupt@digipen.edu
course      CS120
assignment  lab 8
due date    10/22/2014

Brief Description: Three functions are included, the first is to find prime 
                   numbers by eliminating multiples of a bse number, second
                   function find twin primes and the third function calculates
                   Brun's Constant.
  
******************************************************************************/

/******************************************************************************
   Function: sieve

Description: finds prime numbers by crossing out multiples of numbers

     Inputs: array - array of integers passed from main.c 
             size - number of elements in the array
     
    Outputs: n/a
******************************************************************************/
#include <stdio.h> /* printf      */
#include <math.h>  /* sqrt        */
#include "sieve.h" /* TRUE, FALSE */

void sieve(int array[], int size)
{
  int i, j;                   /* loop counter */
  int max_check = sqrt(size); /* max number to check multiples of */

  array[0] = FALSE;           /* 0 is not prime */

  array[1] = FALSE;           /* 1 is not prime */

  for(i = 2; i <= size; i++)  /* sets all numbers from 2 - size to true */
  array[i] = TRUE;

  /* starts at base factor of 2 and goes until square root of size
   * and resets j when kicked back from nested while loop */
  for(i = 2; i <= max_check; i++)
  {
    j = 1;
    
    if(array[i] == FALSE)
      continue;
    
    while(i * j < size)
    {
      j++;
      array[i * j] = FALSE;
    }
  }
}

/******************************************************************************
   Function: twin_primes

Description: finds prime numbers that are only 2 'spaces' apart (ex. 5 and 7)

     Inputs: primes - a constant array of integers
             size - number of elements in the array
     
    Outputs: number of twin primes found
******************************************************************************/
int twin_primes(const int primes[], int size)
{
  int i;         /* loop counter */
  int count = 0; /* counts number of twin pairs found */
  
  /* iterates through the array to find twin primes */
  for(i = 2; i < size; i++)
  {
    if(primes[i] && primes[i + 2])
    {  
      count++;
      printf("twin prime #%4i: %4i and %4i\n",count, i, i + 2);
    }
  }
  
  return count;
}

/******************************************************************************
   Function: brun_constant

Description: finds brun constant within a range of numbers

     Inputs: primes - a constant array of integers
             size - number of elements in the array
     
    Outputs: bruns constant
******************************************************************************/
double brun_constant(const int primes[], int size)
{
  int i;                  /* loop counter */
  double bruns_const = 0; /* value of bruns constant */
  
  /* finds twin primes and sums the two numbers as 1/number */
  for(i = 2; i < size; i++)
  {
    if(primes[i] && primes[i + 2])
    {
      bruns_const += 1.0/i + 1.0/(i + 2);
    }
  }
  
  return bruns_const;    /* value of brun's constant */
}