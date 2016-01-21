
/*******************************************************************************
filename    main.c
author      Artie Fufkin
DP email    afufkin2@digipen.edu
course      CS120
assignment  15
due date    11/26/2016

Brief Description:
  This file contains the test functions for the jumble assignment.

*******************************************************************************/
#include <stdio.h>  /* printf                           */
#include "jumble.h" /* mystrlen, jumble, ENCODE, DECODE */

void test0(void)
{
  unsigned char a[] = "a";
  unsigned char b[] = "abcd";
  unsigned char c[] = "";
  unsigned char d[] = "Four score and seven years ago our fathers brought "
             "forth on this continent a new nation, conceived in liberty and "
             "dedicated to the proposition that all men are created equal.";

  int length;

  printf("\nTest0 ======================================\n");
  length = mystrlen(a); /* should be 1   */
  printf("length of a is %i\n", length);

  length = mystrlen(b); /* should be 4   */
  printf("length of b is %i\n", length);

  length = mystrlen(c); /* should be 0   */
  printf("length of c is %i\n", length);

  length = mystrlen(d); /* should be 174 */
  printf("length of d is %i\n", length);
}

void test1(void)
{
  unsigned char phrase[] = "THIS IS A SECRET.";
  unsigned char password[] = "$#*!";

  printf("\nTest1 ======================================\n");
  printf("Original phrase:\n");
  printf("%s\n", phrase);
  jumble(phrase, password, ENCODE, 1);

  printf("\nEncoded phrase:\n");
  printf("%s\n", phrase);
}

void test2(void)
{
  unsigned char phrase[] = "xkstDl}AeC}fguouR";
  unsigned char password[] = "$#*!";

  printf("\nTest2 ======================================\n");
  printf("Encoded phrase:\n");
  printf("%s\n", phrase);

  jumble(phrase, password, DECODE, 1);
  printf("\nDecoded back:\n");
  printf("%s\n", phrase);
}

void test3(void)
{
  unsigned char phrase[] = "This is a secret.";
  unsigned char password[] = {1, 0};

  printf("\nTest3 ======================================\n");
  printf("Original phrase:\n");
  printf("%s\n", phrase);
  jumble(phrase, password, ENCODE, 1);

  printf("\nEncoded phrase:\n");
  printf("%s\n", phrase);
}

void test4(void)
{
  unsigned char phrase[] = "Uijt!jt!b!tfdsfu/";
  unsigned char password[] = {1, 0};

  printf("\nTest4 ======================================\n");
  printf("Encoded phrase:\n");
  printf("%s\n", phrase);

  jumble(phrase, password, DECODE, 1);
  printf("\nDecoded back:\n");
  printf("%s\n", phrase);
}

void test5(void)
{
  unsigned char phrase[] = "ABCDEFG";
  unsigned char password[] = {1, 2, 3, 0};

  printf("\nTest5 ======================================\n");
  printf("Original phrase:\n");
  printf("%s\n", phrase);
  jumble(phrase, password, ENCODE, 1);

  printf("\nEncoded phrase:\n");
  printf("%s\n", phrase);

  jumble(phrase, password, DECODE, 1);
  printf("\nDecoded back:\n");
  printf("%s\n", phrase);
}

void test6(void)
{
  unsigned char phrase[] = "ABCDEFG";
  unsigned char password[] = {1, 2, 3, 0};

  printf("\nTest6 ======================================\n");
  printf("Original phrase:\n");
  printf("%s\n", phrase);
  jumble(phrase, password, ENCODE, 1);

  printf("\nEncoded phrase:\n");
  printf("%s\n", phrase);

  jumble(phrase, password, ENCODE, 1);
  printf("\nEncoded again:\n");
  printf("%s\n", phrase);

  jumble(phrase, password, DECODE, 1);
  printf("\nDecoded once:\n");
  printf("%s\n", phrase);

  jumble(phrase, password, DECODE, 1);
  printf("\nDecoded twice:\n");
  printf("%s\n", phrase);
}

void test7(void)
{
  unsigned char phrase[] = "This is a secret.";
  unsigned char password[] = {1, 0};

  printf("\nTest7 ======================================\n");
  printf("Original phrase:\n");
  printf("%s\n", phrase);
  jumble(phrase, password, ENCODE, 5);

  printf("\nEncoded phrase:\n");
  printf("%s\n", phrase);

  jumble(phrase, password, DECODE, 5);
  printf("\nDecoded back:\n");
  printf("%s\n", phrase);
}

void test8(void)
{
  unsigned 
  char phrase[] = "Four score and seven years ago our fathers brought forth "
                  "on this continent a new nation, conceived in liberty and "
                  "dedicated to the proposition that all men are created "
                  "equal.";

  unsigned char password[] = {1, 0};

  printf("\nTest8 ======================================\n");
  printf("Original phrase:\n");
  printf("%s\n", phrase);
  jumble(phrase, password, ENCODE, 1);

  printf("\nEncoded phrase:\n");
  printf("%s\n", phrase);

  jumble(phrase, password, DECODE, 1);
  printf("\nDecoded back:\n");
  printf("%s\n", phrase);
}

void test9(void)
{
  unsigned 
  char phrase[] = "Four score and seven years ago our fathers brought forth "
                  "on this continent a new nation, conceived in liberty and "
                  "dedicated to the proposition that all men are created "
                  "equal.";

  unsigned char *password = (unsigned char *)"foobar";

  printf("\nTest9 ======================================\n");
  printf("Original phrase:\n");
  printf("%s\n", phrase);
  jumble(phrase, password, ENCODE, 3);

  printf("\nEncoded phrase:\n");
  printf("%s\n", phrase);

  jumble(phrase, password, DECODE, 3);
  printf("\nDecoded back:\n");
  printf("%s\n", phrase);
}

void test10(void)
{
  unsigned char phrase[] = "batman";
  unsigned char password[] = "cave";

  printf("\nTest10 ======================================\n");
  printf("Original phrase:\n");
  printf("%s\n", phrase);
  jumble(phrase, password, ENCODE, 2);

  printf("\nEncoded phrase:\n");
  printf("%s\n", phrase);

  jumble(phrase, password, DECODE, 2);
  printf("\nDecoded back:\n");
  printf("%s\n", phrase);
}

int main(void)
{
  int test = -1;
  
  switch (test)
  {
    case 0:
      test0();
      break;
    case 1:
      test1();
      break;
    case 2:
      test2();
      break;
    case 3:
      test3();
      break;
    case 4:
      test4();
      break;
    case 5:
      test5();
      break;
    case 6:
      test6();
      break;
    case 7:
      test7();
      break;
    case 8:
      test8();
      break;
    case 9:
      test9();
      break;
    case 10:
      test10();
      break;
    default:
      test0();
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
  }
  
  return 0;
}
