/******************************************************************************
filename    fractions.c
author      Haven Breithaupt
DP email    h.breithaupt@digipen.edu
course      CS120
assignment  13
due date    11/26/2014

Brief Description:
  Does multiplie operations with fractions such as finding the greatest common
  divisor addition, subtraction,multiplication, reducing improper fractions, 
  and a combination of all operations mentioned.
******************************************************************************/

#include "fractions.h" /* contains function and struct prototypes */

/******************************************************************************
   Function: GCD

Description: finds greatest common divisor of two numbers

     Inputs: a - an integer
             b - an integer
     
    Outputs: the greatest common divisor as type integer
******************************************************************************/
int GCD(int a, int b)
{
  int remainder;   /* remainder when dividing larger and smaller */
  int larger;      /* larger number, used in numerator position */
  int smaller;     /* smaller number, used in denominator position */
  
    /* special case when one number is 0 */
  if(a == 0 && b != 0)
    return b;
  
    /* special case when one number is 0 */
  if(a != 0 && b == 0)
    return a;
  
    /* special case when both numbers are 0 */
  if(a == 0 && b == 0)
    return 0;
  
    /* assigns larger and smaller */
  if(a > b)
  {
    larger = a;
    smaller = b;
  }
  else
  {
    larger = b;
    smaller = a;
  }
  
    /* calculates initial remainder */
  remainder = larger % smaller;
  
    /* if remainder isn't 0, keep going until it is */
  while(remainder != 0)
  {
    larger = smaller;
    smaller = remainder;
    remainder = larger % smaller;
  }
  
  return smaller;  /* smaller is now the gcd so return it */
}

/******************************************************************************
   Function: add_fractions

Description: adds two fractions together and reduces them

     Inputs: a - a pointer to a struct of type FRACTION
             b - a pointer to a struct of type FRACTION
     
    Outputs: a struct containing the reduced sum of the two fractions passed
******************************************************************************/
struct FRACTION add_fractions(const struct FRACTION *a, 
                              const struct FRACTION *b)
{
  struct FRACTION sum = {0}; /* new struct to hold answer */
  int numerator_part1;       /* first part of the numerator */
  int numerator_part2;       /* second part of numerator */
  int gcd_reduction;         /* find gcd of new fraction to try and reduce */
  
    /* first part of numerator by multiplying first num + second denom */
  numerator_part1 = a->numerator * b->denominator;
    
    /* second part of numerator by multiplying second num + first denom */
  numerator_part2 = b->numerator * a->denominator;
  
    /* combines numerator parts for numerator of answer */
  sum.numerator = numerator_part1 + numerator_part2;
  
    /* denominator of answer */
  sum.denominator = a->denominator * b->denominator;
  
    /* finds gcd with answer numerator and denominator */
  gcd_reduction = GCD(sum.numerator, sum.denominator);
  
    /* if gcd is negative, change it to positive to not swap signs */
  if(gcd_reduction < 0)
    gcd_reduction *= -1;
  
    /* don't divide by 0, bad shit happens */
  if(gcd_reduction != 0)
  {
    sum.numerator /= gcd_reduction;
    sum.denominator /= gcd_reduction;
  }
  
  return sum;                /* returns struct containing reduced sum */
}

/******************************************************************************
   Function: subtract_fractions

Description: subtracts two functions 

     Inputs: a - a pointer to a struct of type FRACTION
             b - a pointer to a struct of type FRACTION
     
    Outputs: a struct containing the differnece of two fractions
******************************************************************************/
struct FRACTION subtract_fractions(const struct FRACTION *a,
                                   const struct FRACTION *b)
{
  struct FRACTION negate_b = {0}; /* struct to swap signs of b */
  
    /* swaps sign of fraction b to use addition function (a + -b) */
  negate_b.numerator = b->numerator * -1;
  
    /* don't negate denominator, just copy it */
  negate_b.denominator = b->denominator;
  
    /* returns struct from calling add_fractions, which is reduced */
  return add_fractions(a, &negate_b);
}

/******************************************************************************
   Function: multiply_fractions

Description: multiplies two fractions

     Inputs: a - a pointer to a struct of type FRACTION
             b - a pointer to a struct of type FRACTION
     
    Outputs: a struct containing the product of the fractions passed
******************************************************************************/
struct FRACTION multiply_fractions(const struct FRACTION *a,
                                   const struct FRACTION *b)
{
  struct FRACTION product = {0}; /* new struct to hold answer */
  int gcd_reduction;             /* gcd to reduce at end */
  
    /* numerator of product */
  product.numerator = a->numerator * b->numerator;
  
    /* denominator of product */
  product.denominator = a->denominator * b->denominator;
  
    /* gcd to reduce if possible */
  gcd_reduction = GCD(product.numerator, product.denominator);
  
    /* if gcd is negative, make it positive */
  if(gcd_reduction < 0)
    gcd_reduction *= -1;
  
    /* don't divide by 0, bad shit happens */
  if(gcd_reduction != 0)
  {
    product.numerator /= gcd_reduction;
    product.denominator /= gcd_reduction;
  }
  
  return product;                 /* return reduced product */
}

/******************************************************************************
   Function: reduced_to_mixed

Description: reduced an improper fraction to a mixed number

     Inputs: fraction - a pointer to a struct of type FRACTION
     
    Outputs: a struct containing the reduced number
******************************************************************************/
struct MIXED_FRACTION reduced_to_mixed(const struct FRACTION *fraction)
{
  struct MIXED_FRACTION reduced = {0}; /* new struct to hold answer */
  int remainder;                       /* remainder to use as new numerator */
  
    /* don't divide by 0, bad shit happens */
  if(fraction->denominator != 0)
  {
      /* modulo inital numerator and denominator to use as new numerator */
    remainder = fraction->numerator % fraction->denominator;
    
      /* divide initial numerand denomitor to pull out integer */
    reduced.whole_number = fraction->numerator / fraction->denominator;
      
      /* new numerator */
    reduced.proper_fraction.numerator = remainder;
  }
  
    /* just copies denominator since it doesn't change */
  reduced.proper_fraction.denominator = fraction->denominator;
  
  return reduced;                      /* returns answer in a struct */
}
