
/*******************************************************************************
filename    main.c
author      Artie Fufkin
DP email    afufkin2@digipen.edu
course      CS120
assignment  12
due date    12/11/2019

Brief Description:
  This file contains the main function for the palindrome assignment.

*******************************************************************************/
#include <stdio.h>  /* printf */

/* Prototypes */
int is_palindrome1(const char phrase[], int length);
int is_palindrome2(const char *phrase, int length);

/* print all elements of an array */
void print_array(const char a[], int size)
{
  int i;
  for (i = 0; i < size; i++)
    printf("%c", a[i]);
}

void test_palindrome(const char sentence[], int length, int which_one)
{
  int pal;
  if (which_one == 1)
  {
    printf("Testing #1: ");
    pal = is_palindrome1(sentence, length);
  }
  else
  {
    printf("Testing #2: ");
    pal = is_palindrome2(sentence, length);
  }

  print_array(sentence, length); 
  if (pal == 1)
    printf(" is a palindrome\n");
  else
    printf(" is not a palindrome\n");
}

void test1(void)
{
  const char a[] = {'a'};
  test_palindrome(a, sizeof(a), 1);
  test_palindrome(a, sizeof(a), 2);
  printf("\n");
}

void test2(void)
{
  const char a[] = {'a', 'b'};
  test_palindrome(a, sizeof(a), 1);
  test_palindrome(a, sizeof(a), 2);
  printf("\n");
}

void test3(void)
{
  const char a[] = {'a', 'a'};
  test_palindrome(a, sizeof(a), 1);
  test_palindrome(a, sizeof(a), 2);
  printf("\n");
}

void test4(void)
{
  const char a[] = {'a', 'b', 'c', 'd', 'c', 'b', 'a'};
  test_palindrome(a, sizeof(a), 1);
  test_palindrome(a, sizeof(a), 2);
  printf("\n");
}


void test5(void)
{
  const char a[] = {'m', 'a', 'd', 'a', 'm', 'I', 'm', 'a', 'd', 'a', 'm'};
  test_palindrome(a, sizeof(a), 1);
  test_palindrome(a, sizeof(a), 2);
  printf("\n");
}

void test6(void)
{
  const char a[] = {'m', 'a', 'd', 'a', 'm', 'I', 'a', 'm', 'a', 'd', 'a', 'm'};
  test_palindrome(a, sizeof(a), 1);
  test_palindrome(a, sizeof(a), 2);
  printf("\n");
}

void test7(void)
{
  const char a[] = {'a', 'B', 'c', 'D', 'E', 'D', 'c', 'B', 'a'};
  test_palindrome(a, sizeof(a), 1);
  test_palindrome(a, sizeof(a), 2);
  printf("\n");
}

void test8(void)
{
  const char a[] = {'a', 'B', 'c', 'D', 'E', 'E', 'D', 'c', 'B', 'a'};
  test_palindrome(a, sizeof(a), 1);
  test_palindrome(a, sizeof(a), 2);
  printf("\n");
}

void test9(void)
{
  const char a[] = {'a', 'B', 'c', 'D', 'E', 'e', 'D', 'c', 'B', 'a'};
  test_palindrome(a, sizeof(a), 1);
  test_palindrome(a, sizeof(a), 2);
  printf("\n");
}

void test10(void)
{
  const char a[] = {'h', 'e', 'l', 'i', 'v', 'e', 'd', 'a', 's', 'a',
                    'd', 'e', 'v', 'i', 'l', 'e', 'h'};
  test_palindrome(a, sizeof(a), 1);
  test_palindrome(a, sizeof(a), 2);
  printf("\n");
}

void test11(void)
{
  const char a[] = {'b', 'o', 't', 't', 'o', 'm'};
  test_palindrome(a, sizeof(a), 1);
  test_palindrome(a, sizeof(a), 2);
  printf("\n");
}

void test12(void)
{
  const char a[] = {'1', '2', '3', '2', '1'};
  test_palindrome(a, sizeof(a), 1);
  test_palindrome(a, sizeof(a), 2);
  printf("\n");
}

int main(void)
{
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  test8();
  test9();
  test10();
  test11();
  test12();

  return 0;
}
