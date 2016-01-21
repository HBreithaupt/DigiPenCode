#include <stdio.h>      /* printf                                         */
#include "jumble.h"     /* mystrlen, jumble, ENCODE, DECODE               */
#include "scantext.h"   /* count_tabs, calculate_lengths, substitute_char */
#include "spellcheck.h" /* spellcheck stuff                               */
#include "palindrome.h" /* palindrome stuff                               */

void test1(void)
{
  unsigned char a[] = "a";
  unsigned char b[] = "abcd";
  unsigned char c[] = "";
  unsigned char d[] = "Four score and seven years ago our fathers brought";

  int length;

  printf("\nTest1 ======================================\n");
  length = mystrlen(a); /* should be 1   */
  printf("length of a is %i\n", length);

  length = mystrlen(b); /* should be 4   */
  printf("length of b is %i\n", length);

  length = mystrlen(c); /* should be 0   */
  printf("length of c is %i\n", length);

  length = mystrlen(d); /* should be 174 */
  printf("length of d is %i\n", length);
}

void test2(void)
{
  unsigned char phrase[] = "C Programming";
  unsigned char password[] = "foo";

  printf("\nTest2 ======================================\n");
  printf("Original phrase:\n");
  printf("%s\n", phrase);

  jumble(phrase, password, ENCODE, 1);
  printf("\nEncoded phrase:\n");
  printf("%s\n", phrase);
  jumble(phrase, password, ENCODE, 1);
  printf("\nEncoded phrase:\n");
  printf("%s\n", phrase);
  jumble(phrase, password, ENCODE, 1);
  printf("\nEncoded phrase:\n");
  printf("%s\n", phrase);
}

static void test3(void)
{
  char string[] = "Four\nscore\tand\nseven\tyears";

  int count;
  int tabs;
  int tabsize;
  int char_count;
  int print_length;

  printf("\nTest3 ======================================\n");
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

static void test4(void)
{
  char s[] = "This is a string";
  mystrupr(s);
  printf("\nTest4 ======================================\n");
  printf("%s\n", s);
}

static void test5(void)
{
  char s1[] = "abba";
  char s2[] = "abbb";

  printf("\nTest5 ======================================\n");

  printf("%s is%sa palindrome.\n", s1, is_palindrome(s1, 4) ? " " : " not ");
  printf("%s is%sa palindrome.\n", s2, is_palindrome(s2, 4) ? " " : " not ");
}

int main(void)
{
  test1();
  test2();
  test3();
  test4();
  test5();
	  
  return 0;
}

