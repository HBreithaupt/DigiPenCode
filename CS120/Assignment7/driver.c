/*******************************************************************************
 driver-dev.c.cpp
*******************************************************************************/
#include <stdio.h>      /* printf                           */
#include <string.h>     /* strcpy                           */

/* check, info, words_starting_with, word_lengths, mystrupr */
/* FILE_OK, FILE_ERR_OPEN, WORD_OK, WORD_BAD, LONGEST_WORD  */
#include "spellcheck.h" 

void test1(void)
{
  int i;
  const char *words[] = {"Four", "score", "and", "seven", "years", "ago", "our",
                         "fathers", "brought", "forth", "on", "this",
                         "continent", "a", "new", "NATION", "fast123",
                         "123  abc", "Hello!!", "", "*&^%$#8UPPERlower"
                        };

  int num_words = sizeof(words) / sizeof(*words);

  printf("\nTest1--------------------------------------------------------\n");
  for (i = 0; i < num_words; i++)
  {
    char buffer[LONGEST_WORD + 1];
    strcpy(buffer, words[i]);
    mystrupr(buffer);
    printf("Word: %s (%s)\n", words[i], buffer);
  }
}

void test2(const char *dictionary)
{
  struct DICTIONARY_INFO dinfo; /* To hold the info from the dictionary */
  int file_result;              /* For file errors                      */

  printf("\nTest2--------------------------------------------------------\n");
  file_result = info(dictionary, &dinfo);
  if (file_result == FILE_ERR_OPEN)
  {
    printf("Can't open %s\n", dictionary);
    return;
  }

  printf("Dictionary: %s\n", dictionary);
  printf("Number of words: %i\n", dinfo.count);
  printf("Shortest word: %i letters\n", dinfo.shortest);
  printf("Longest word: %i letters\n", dinfo.longest);
}

void test3(const char *dictionary, char letter)
{
  int file_result;

  printf("\nTest3--------------------------------------------------------\n");
  file_result = words_starting_with(dictionary, letter);

  if (file_result == FILE_ERR_OPEN)
  {
    printf("Can't open %s\n", dictionary);
    return;
  }

  printf("Dictionary: %s\n", dictionary);
  printf("Number of words starting with %c: %i\n", letter, file_result);
}

void test4(const char *dictionary, const char *word)
{
  int file_result;

  printf("\nTest4--------------------------------------------------------\n");
  file_result = spell_check(dictionary, word);
  if (file_result == FILE_ERR_OPEN)
  {
    printf("Can't open %s\n", dictionary);
    return;
  }

  if (file_result == WORD_OK)
    printf("The word %s is spelled correctly.\n", word);
  else
    printf("The word %s is misspelled.\n", word);
}

void test5(void)
{
  int i;
  int file_result;
  const char *words[] = {"Four", "score", "and", "seven", "years", "ago", "our",
                   "fathers", "brought", "forth", "on", "this", "continent",
                   "a", "new", "nation"
                  };

  int num_misspelled = 0;
  int num_words = sizeof(words) / sizeof(*words);

    /* Name of the dictionary file */
  const char *dictionary = "allwords.txt";

  printf("\nTest5--------------------------------------------------------\n");
  printf("Misspelled words: ");
  for (i = 0; i < num_words; i++)
  {
    file_result = spell_check(dictionary, words[i]);
    if (file_result == FILE_ERR_OPEN)
    {
      printf("Can't open %s\n", dictionary);
      return;
    }

    if (file_result == WORD_BAD)
    {
      printf("%s ", words[i]);
      num_misspelled++;
    }
  }
  if (!num_misspelled)
    printf("*** None ***");
  printf("\n");
}

void test6(void)
{
  int i;
  int file_result;
  const char *words[] = {"Four", "SCORE", "and", "sevn", "years", "ago", "ar",
                   "fawthers", "brought", "foarth", "on", "this", "contnent",
                   "a", "gnu", "nashun"
                  };

  int num_misspelled = 0;
  int num_words = sizeof(words) / sizeof(*words);

    /* Name of the dictionary file */
  const char *dictionary = "allwords.txt";

  printf("\nTest6--------------------------------------------------------\n");
  printf("Misspelled words: ");
  for (i = 0; i < num_words; i++)
  {
    file_result = spell_check(dictionary, words[i]);
    if (file_result == FILE_ERR_OPEN)
    {
      printf("Can't open %s\n", dictionary);
      return;
    }

    if (file_result == WORD_BAD)
    {
      printf("%s ", words[i]);
      num_misspelled++;
    }
  }
  if (!num_misspelled)
    printf("*** None ***");
  printf("\n");
}

void test7(int max_length)
{
  int file_result; /* For file errors                       */
  int total = 0;
  int length;
  int lengths[21] = {0};

    /* Name of the dictionary file */
  const char *dictionary = "allwords.txt";

  printf("\nTest7--------------------------------------------------------\n");
  printf("Dictionary: %s\n", dictionary);
  file_result = word_lengths(dictionary, lengths, max_length);
  if (file_result == FILE_ERR_OPEN)
  {
    printf("Can't open %s\n", dictionary);
    return;
  }
  for (length = 1; length <= max_length; length++)
  {
    printf("Number of words of length %2i is %6i\n", length, lengths[length]);
    total += lengths[length];
  }
  printf("Total number of words counted: %i\n", total);
}


int main(void)
{
  test1();

  test2("lexicon.txt");
  test2("small.txt");
  test2("allwords.txt");

  test3("lexicon.txt", 'a');
  test3("lexicon.txt", 'A');
  test3("lexicon.txt", 'l');
  test3("lexicon.txt", '$');
  test3("lexicon.txt", 'e');

  test3("allwords.txt", 'M');
  test3("allwords.txt", 'q');
  test3("allwords.txt", '5');

  test4("lexicon.txt", "APPLE");
  test4("lexicon.txt", "Apple");
  test4("lexicon.txt", "apple");
  test4("lexicon.txt", "appl");
  test4("small.txt", "abalone");
  test4("allwords.txt", "interdigitation");
  test4("allwords.txt", "interdigalizing");

  test5();
  test6();
  test7(5);
  test7(20);

  return 0;
}

