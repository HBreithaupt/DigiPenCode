/******************************************************************************
filename    main.c
author      Artie Fufkin
DP email    afufkin2@digipen.edu
course      CS120
section     D
assignment  15
due date    11/26/2036

Brief Description:
  This file contains the main function for the array assignment.

******************************************************************************/
#include <stdio.h>  /* printf */
#include <stdlib.h> /* rand, srand */

/* Prototypes for array manipulations */
void reverse_array(int a[], int size);
void add_arrays(const int a[], const int b[], int c[], int size);
void scalar_multiply(int a[], int size, int multiplier);
int dot_product(const int a[], const int b[], int size);
void cross_product(const int a[], const int b[], int c[]);

/* print all elements of an array */
void print_array(const int a[], int size)
{
  int i;
  for (i = 0; i < size; i++)
    printf("%5i", a[i]);
  printf("\n");
}

/* generate random numbers between low and high */
int RandomInt(int low, int high)
{
  int number;
  number = rand() % (high - low + 1) + low;
  return number;
}

/* more multiply tests */
void test1(void)
{
  #define SIZE1 10

  int a[SIZE1];
  int b[SIZE1];
  int i;
  int product;

  srand(2);
  for (i = 0; i < SIZE1; i++)
  {
    a[i] = RandomInt(-5, 5);
    b[i] = RandomInt(-5, 5);
  }
  printf("Array a:");
  print_array(a, SIZE1);
  printf("Array b:");
  print_array(b, SIZE1);

  product = dot_product(a, b, SIZE1);
  printf("The dot product of a * b is %i", product);
  printf("\n");
}

/* a bigger multiply test */
void test2(void)
{
  #define SIZE2 1000

  int a[SIZE2];
  int b[SIZE2];
  int i;
  int product;

  srand(2);
  for (i = 0; i < SIZE2; i++)
  {
    a[i] = RandomInt(-10, 10);
    b[i] = RandomInt(-10, 10);
  }

  /* Too much to print out */
  /*
  printf("Array a:\n");
  print_array(a, SIZE2);
  printf("Array b:\n");
  print_array(b, SIZE2);
  */

  product = dot_product(a, b, SIZE2);
  printf("The dot product of a * b is %i", product);
  printf("\n");
}

int main(void)
{
  int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int b[] = {4, 6, 8, 2, 4, 3, 5, 8};
  int c[8];
  int size = sizeof(a) / sizeof(a[0]);

  int v1[] = {1, 2, 3};
  int v2[] = {3, 4, 7};
  int vsize = sizeof(v1) / sizeof(v1[0]);
  int v3[sizeof(v1) / sizeof(v1[0])];
  int product;

    /* reverse an array */
  printf("Array a:\n");
  print_array(a, size);
  reverse_array(a, size);
  printf("Array a reversed:\n");
  print_array(a, size);
  printf("\n");

    /* add two arrays into a third array */
  printf("Array b:\n");
  print_array(b, size);
  add_arrays(a, b, c, size);
  printf("Array c (sum of array a and array b):\n");
  print_array(c, size);
  printf("\n");

    /* multiply each element by 10 */
  scalar_multiply(c, size, 10);
  printf("All values of c multiplied by 10:\n");
  print_array(c, size);  
  printf("\n");

    /* multiply two arrays (dot product) */
  printf("Array v1:");
  print_array(v1, vsize);
  printf("Array v2:");
  print_array(v2, vsize);
  product = dot_product(v1, v2, vsize);
  printf("The dot product of v1 * v2 is %i\n", product);
  printf("\n");

    /* multiply two arrays (cross product) */
  printf("Array v1:");
  print_array(v1, vsize);
  printf("Array v2:");
  print_array(v2, vsize);
  cross_product(v1, v2, v3);
  printf("The cross product of v1 x v2 is:");
  print_array(v3, 3);
  printf("\n");

    /* more tests */
  test1();
  test2();
  printf("\n");

  return 0;
}
