/******************************************************************************
filename    array.c
author      Haven Breithaupt
DP email    h.breithaupt@digipen.edu
course      CS120
assignment  Assignment 3
due date    10/14/2014

Brief Description: Four different functions that use arrays: reverse
                   an array, adding two arrays, dot product of two arrays,
                   cross product of two arrays, and scaling an array by a 
                   multiplier.
  
******************************************************************************/

/******************************************************************************
   Function: reverse_array 

Description: Takes an array and reverses the elements.

     Inputs: int a[] - an array of integers (size given by main.c)
             size - number of elements in the array
     
    Outputs: none
******************************************************************************/
void reverse_array(int a[], int size)
{
  int i;     /* loop counters */
  int j = 1; /* counter to go backwards through array */
  int temp;  /* tempeorary variable */
  
  
  for(i = 0; i < size/2; i++)
  {
    temp = a[i];        /* puts current array value into temp */
    a[i] = a[size - j]; /* takes opposite array value into current iteration */
    a[size - j] = temp; /* puts current array value (now temp) 
                                into opposite side of array */
    j++; /* increments j to go backwards through the array each iteration */
  }
} 

/*******************************************************************************
   Function: add_arrays

Description: adds the elements of two arrays and puts output into third array

     Inputs: const a[] - a read only array of integers (size given in main.c)
             const b[] - a read only array if integers (size given in main.c)
             c[] - an array of integers
             size - number of elements in the array
     
    Outputs: third array with each element the sum of a[] and b[]
*******************************************************************************/
void add_arrays(const int a[], const int b[], int c[], int size)
{
  int i; /* loop counter */
  
  /* iterates through entire array */
  for(i = 0; i < size; i++)
  {
    c[i] = a[i] + b[i];
  }
  
}

/*******************************************************************************
   Function: scalar_multiply

Description: Scales an array by a multiplier.

     Inputs: a[] - an array of integers (size given in main.c)
             size - number of elements in the array
             multiplier - number to scale multiply the array
     
    Outputs: the given array scaled by the multiplier
*******************************************************************************/
void scalar_multiply(int a[], int size, int multiplier)
{
  int i; /* loop counter */
  
  /* iterates entire array */
  for(i = 0; i < size; i++)
  {
    a[i] *= multiplier; /* multiplies element in array by multiplier 
                              and then assigns elemtn new value */
  }
}

/*******************************************************************************
   Function: dot_product

Description: calculates the dot product of two arrays

     Inputs: const a[] - a read only array
             const b[] - a read only array
             size - number of elements in each array
             
    Outputs: the dot product of arrays a[] and b[], which is a scalar
*******************************************************************************/
int dot_product(const int a[], const int b[], int size)
{
  int i; /* loop counter */
  int dotproduct = 0; /* value of dot product */
  
  for(i = 0; i < size; i++)
  {
      /* multiples elements of both array and adds value to dout product */
    dotproduct += (a[i] * b[i]); 
  }
  
  return dotproduct; /* returns dot product */
}

/*******************************************************************************
   Function: cross_product

Description: calculates the cross product of two arrays.

     Inputs: const a[] - a read only array
             const b[] - a read only array
     
    Outputs: none
*******************************************************************************/
void cross_product(const int a[], const int b[], int c[])
{
  c[0] = (a[1] * b[2]) - (a[2] * b[1]); /* first element of the array */
    
  c[1] = -((b[2] * a[0]) - (b[0] * a[2])); /* second element of the array */
    
  c[2] = (a[0] * b[1]) - (a[1] * b[0]); /* third element of the array */
}
