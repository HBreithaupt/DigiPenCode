/******************************************************************************
filename    main2.c
author      Bobbi Fleckman
DP email    hostess@digipen.edu
course      CS120
section     D
assignment  15
due date    12/11/2036

Brief Description:
  This file contains another main function for the array assignment.

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

void reverse_test(void)
{
  /* What's the largest size that will work? */
  #define REV_SIZE 100

  int a[] = {8};
  int b[] = {1, 2, 3};
  int c[] = {1, 2, 3, 4};
  int d[REV_SIZE];
  int i;

  for (i = 0; i < REV_SIZE; i++)
    d[i] = RandomInt(1, REV_SIZE);

  printf("Reverse test =============================\n");
  printf("The original arrays:\n");
  print_array(a, 1);
  print_array(b, 3);
  print_array(c, 4);
  print_array(d, REV_SIZE);

  reverse_array(a, 1);
  reverse_array(b, 3);
  reverse_array(c, 4);
  reverse_array(d, REV_SIZE);
 
  printf("The reversed arrays:\n");
  print_array(a, 1);
  print_array(b, 3);
  print_array(c, 4);
  print_array(d, REV_SIZE);

  printf("\n");
}

void add_test(void)
{
  /* What's the largest size that will work? */
  #define ADD_SIZE 100

  int a[ADD_SIZE];
  int b[ADD_SIZE];
  int c[ADD_SIZE];
  int i;

  for (i = 0; i < ADD_SIZE; i++)
  {
    a[i] = RandomInt(-100, 100);
    b[i] = RandomInt(-100, 100);
  }

  printf("Add test =============================\n");
  printf("The original arrays:\n");
  print_array(a, ADD_SIZE);
  printf("\n");
  print_array(b, ADD_SIZE);

  add_arrays(a, b, c, ADD_SIZE);
 
  printf("The sum of the two arrays:\n");
  print_array(c, ADD_SIZE);

  printf("\n");
}

void scalar_multiply_test(void)
{
  /* What's the largest size that will work? */
  #define SCALAR_SIZE 100

  int a[SCALAR_SIZE];
  int multiplier;
  int i;

  for (i = 0; i < SCALAR_SIZE; i++)
    a[i] = RandomInt(-100, 100);

  printf("Scalar multiply test =============================\n");
  printf("The original array:\n");
  print_array(a, SCALAR_SIZE);

  multiplier = 2;
  scalar_multiply(a, SCALAR_SIZE, multiplier);

  printf("The array multiplied by %i:\n", multiplier);
  print_array(a, SCALAR_SIZE);

  multiplier = 5;
  scalar_multiply(a, SCALAR_SIZE, multiplier);

  printf("And now multiplied by %i:\n", multiplier);
  print_array(a, SCALAR_SIZE);

  printf("\n");
}

void dot_product_test(void)
{
  /* What's the largest size that will work? */
  #define ARRAY_SIZE 100

  int a[ARRAY_SIZE];
  int b[ARRAY_SIZE];
  int i;
  int product;

  for (i = 0; i < ARRAY_SIZE; i++)
  {
    a[i] = RandomInt(-10, 10);
    b[i] = RandomInt(-10, 10);
  }

  printf("Dot product test =============================\n");
  printf("The original arrays:\n");
  print_array(a, ARRAY_SIZE);
  printf("\n");
  print_array(b, ARRAY_SIZE);

  product = dot_product(a, b, ARRAY_SIZE);
  printf("The dot product of a and b is %i\n", product);

  product = dot_product(a, a, ARRAY_SIZE);
  printf("The dot product of a and a is %i\n", product);

  product = dot_product(b, b, ARRAY_SIZE);
  printf("The dot product of b and b is %i\n", product);

  printf("\n");
}

void cross_product_test(void)
{
  #define ARRAY_SIZE_X  3
  #define ITERATIONS   10

  int a[ARRAY_SIZE_X];
  int b[ARRAY_SIZE_X];
  int c[ARRAY_SIZE_X];
  int i, j;

  printf("Cross product test =============================\n");
  for (i = 0; i < ITERATIONS; i++)
  {
    for (j = 0; j < ARRAY_SIZE_X; j++)
    {
        /* Fill arrays with random values */
      a[j] = RandomInt(-10, 10);
      b[j] = RandomInt(-10, 10);
    }

      /* Print the arrays               */
    printf("The original arrays:\n");
    print_array(a, ARRAY_SIZE_X);
    printf("\n");
    print_array(b, ARRAY_SIZE_X);

    cross_product(a, b, c);
    printf("The cross product of a x b is:");
    print_array(c, ARRAY_SIZE_X);
    printf("\n");
  }
}

int main(void)
{
  srand(5);

  reverse_test();
  add_test();
  scalar_multiply_test();
  dot_product_test();
  cross_product_test();

  return 0;
}
