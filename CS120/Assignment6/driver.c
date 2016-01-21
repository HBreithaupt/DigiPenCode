/*******************************************************************************
filename    driver.c
author      Artie Fufkin
DP email    afufkin2@digipen.edu
course      CS120
assignment  15
due date    12/24/2046

Brief Description:
  This file contains the test functions for the scan text program.

*******************************************************************************/
#include <stdio.h>    /* printf */

/* Prototypes */
int count_words(const char *string);
int count_tabs(const char *string);
int substitute_char(char *string, char old_char, char new_char);
void calculate_lengths(const char *string, int tabsize, int *string_length, 
                       int *display_length);

int mystrlen(const char *string)
{
  int length = 0;
  while (*string++)
    length++;

  printf("This should not be called.\n");
  return length;
}

static void test1(void)
{
  char string[] = "This\tstring\thas\tfive\twords.";
  int tabs;

  printf("\n== test1 ==========================================================\n");
  printf("|%s|\n", string);
  tabs = count_tabs(string);
  printf("Number of tabs is %i.\n", tabs);
}

static void test2(void)
{
  char string[] = "This\tstring\thas\tfive\twords.";
  int char_count;
  int print_length;
  int tabsize = 2;

  calculate_lengths(string, tabsize, &char_count, &print_length);

  printf("\n== test2 ==========================================================\n");
  printf("|%s|\n", string);
  printf("Number of characters in the string is %i.\n", char_count);
  printf("With tab size of %i, the print length is %i.\n", tabsize, print_length);

  tabsize = 3;
  calculate_lengths(string, tabsize, &char_count, &print_length);
  printf("With tab size of %i, the print length is %i.\n", tabsize, print_length);

  tabsize = 6;
  calculate_lengths(string, tabsize, &char_count, &print_length);
  printf("With tab size of %i, the print length is %i.\n", tabsize, print_length);

  tabsize = 8;
  calculate_lengths(string, tabsize, &char_count, &print_length);
  printf("With tab size of %i, the print length is %i.\n", tabsize, print_length);
}

static void test3(void)
{
  char string[] = "This\tstring\thas\tfive\twords.";
  int count;
  int tabs;
  int tabsize;
  int char_count;
  int print_length;

  printf("\n== test3 ==========================================================\n");
  printf("|%s|\n", string);
  tabs = count_tabs(string);
  printf("Number of tabs is %i.\n", tabs);

  tabsize = 4;
  calculate_lengths(string, tabsize, &char_count, &print_length);
  printf("Number of characters in the string is %i.\n", char_count);
  printf("With tab size of %i, the print length is %i.\n", tabsize, print_length);

  count = substitute_char(string, '\t', ' ');
  printf("Replacements made: %i. After replacing tabs with spaces:\n", count);
  printf("|%s|\n", string);
  printf("Number of characters in the string is %i.\n", char_count);
  printf("Number of tabs is %i\n", count_tabs(string));

  tabsize = 4;
  calculate_lengths(string, tabsize, &char_count, &print_length);
  printf("Number of characters in the string is %i.\n", char_count);
  printf("With tab size of %i, the print length is %i.\n", tabsize, print_length);
}

static void test4(void)
{
  char string[] = "\t\t\t\t\t\t";
  int count;
  int tabs;
  int tabsize;
  int char_count;
  int print_length;

  printf("\n== test4 ==========================================================\n");
  printf("|%s|\n", string);
  tabs = count_tabs(string);
  printf("Number of tabs is %i.\n", tabs);

  tabsize = 4;
  calculate_lengths(string, tabsize, &char_count, &print_length);
  printf("Number of characters in the string is %i.\n", char_count);
  printf("With tab size of %i, the print length is %i.\n", tabsize, print_length);

  count = substitute_char(string, '\t', ' ');
  printf("Replacements made: %i. After replacing tabs with spaces:\n", count);
  printf("|%s|\n", string);
  printf("Number of characters in the string is %i.\n", char_count);
  printf("Number of tabs is %i\n", count_tabs(string));

  tabsize = 4;
  calculate_lengths(string, tabsize, &char_count, &print_length);
  printf("Number of characters in the string is %i.\n", char_count);
  printf("With tab size of %i, the print length is %i.\n", tabsize, print_length);
}


static void test5(void)
{
  char string[] = "This is a simple string.";
  int count;

  printf("\n== test5 ==========================================================\n");
  printf("|%s|\n", string);
  count = count_words(string);
  printf("Word count is %2i\n", count);
}

static void test6(void)
{
  char string[] = "These\twords\tare\tseparated\tby\ttabs.";
  int count;

  printf("\n== test6 ==========================================================\n");
  printf("|%s|\n", string);
  count = count_words(string);
  printf("Word count is %2i\n", count);
}

static void test7(void)
{
  char string[] = "  This string has leading and trailing spaces.  ";
  int count;

  printf("\n== test7 ==========================================================\n");
  printf("|%s|\n", string);
  count = count_words(string);
  printf("Word count is %2i\n", count);
}

static void test8(void)
{
  char string[] = "  \t This\t  string  \t \t\t  has \t  \tfive\t\n  words.\n";
  int count;

  printf("\n== test8 ==========================================================\n");
  printf("|%s|\n", string);
  count = count_words(string);
  printf("Word count is %2i\n", count);
  printf("Number of tabs is %i\n", count_tabs(string));
}

static void test9(void)
{
  char string[] = "  \t This\t  string\n  \t \t\t  has\n \t\n  \t\"more\" than five \n\t\n  words.\n\n";
  int count;

  printf("\n== test9 ==========================================================\n");
  printf("|%s|\n", string);
  count = count_words(string);
  printf("Word count is %2i\n", count);
  printf("Number of tabs is %i\n", count_tabs(string));
}

static void test10(void)
{
  char string[] = "Four\nscore\tand\nseven\t"
                  "years\nago\nour fathers\tbrought\n"
                  "forth\ton\nthis\ncontinent a\n"
                  "new\tnation.";

  int count;
  int tabs;
  int tabsize;
  int char_count;
  int print_length;

  printf("\n== test10 ==========================================================\n");
  printf("|%s|\n", string);
  tabs = count_tabs(string);
  printf("Number of tabs is %i.\n", tabs);

  tabsize = 4;
  calculate_lengths(string, tabsize, &char_count, &print_length);
  printf("Number of characters in the string is %i.\n", char_count);
  printf("With tab size of %i, the print length is %i.\n", tabsize, print_length);

  count = substitute_char(string, '\n', ' ');
  printf("Replacements made: %i. After replacing newlines with spaces:\n", count);
  printf("|%s|\n", string);
  printf("Number of characters in the string is %i.\n", char_count);
  printf("Number of tabs is %i\n", count_tabs(string));

  count = substitute_char(string, '\t', ' ');
  printf("Replacements made: %i. After replacing tabs with spaces:\n", count);
  printf("|%s|\n", string);
  printf("Number of characters in the string is %i.\n", char_count);
  printf("Number of tabs is %i\n", count_tabs(string));
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
  return 0;
}
