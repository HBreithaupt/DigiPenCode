#include <stdio.h>  /* printf         */
#include <stdlib.h> /* atoi           */
#include <string.h> /* strcpy, strcat */
#include "histogram.h"

const char s0[] = "Real simple.";

const char s1[] = "This is simple - a sentence with spaces - and other "
                  "punctuations.";

const char s2[] = 
  "When in the Course of human events, it becomes necessary for one people to "
  "dissolve the political bands which have connected them with another, and to "
  "assume among the powers of the earth, the separate and equal station to "
  "which the Laws of Nature and of Nature's God entitle them, a decent respect "
  "to the opinions of mankind requires that they should declare the causes "
  "which impel them to the separation.";

const char s3a[] =
  "We hold these truths to be self-evident, that all men are created equal, "
  "that they are endowed by their Creator with certain unalienable Rights, "
  "that among these are Life, Liberty and the pursuit of Happiness. --That "
  "to secure these rights, Governments are instituted among Men, deriving "
  "their just powers from the consent of the governed, --That whenever any "
  "Form of Government becomes destructive of these ends, it is the Right of "
  "the People to alter or to abolish it, and to institute new Government, ";

const char s3b[] =
  "laying its foundation on such principles and organizing its powers in "
  "such form, as to them shall seem most likely to effect their Safety and " 
  "Happiness. Prudence, indeed, will dictate that Governments long "
  "established should not be changed for light and transient causes; and "
  "accordingly all experience hath shewn, that mankind are more disposed to "
  "suffer, while evils are sufferable, than to right themselves by "
  "abolishing the forms to which they are accustomed. But when a long train ";
  
const char s3c[] =
  "of abuses and usurpations, pursuing invariably the same Object evinces a "
  "design to reduce them under absolute Despotism, it is their right, it is "
  "their duty, to throw off such Government, and to provide new Guards for "
  "their future security.--Such has been the patient sufferance of these "
  "Colonies; and such is now the necessity which constrains them to alter "
  "their former Systems of Government. The history of the present King of "
  "Great Britain is a history of repeated injuries and usurpations, all ";

const char s3d[] =
  "having in direct object the establishment of an absolute Tyranny over "
  "these States. To prove this, let Facts be submitted to a candid world."; 

const char s4[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
                  "1234567890!@#$%^&*()<>?:\"{}_+ ssTT";

void GetAndPrintStatistics(const int letters[])
{
  int max;
  double average;
  char letter;

  GetStatistics(letters, &average, &letter, &max);
  printf("Average: %.5f, max letter: %c, max count: %i\n", 
         average, letter, max);

}

void DoTest(const char *string)
{
  int spaces, other;        /* These will be filled in by GetCounts     */
  int letters[NUM_LETTERS]; /* This will also be filled in by GetCounts */
  int count;                /* Number of letters in the sentence        */

  count = GetCounts(string, letters, &spaces, &other);
  printf("Count of letters is: %i, spaces: %i, other: %i\n", 
         count, spaces, other);

  PrintHistogram(letters);
  GetAndPrintStatistics(letters);
  printf("\n\n");
}

int main(int argc, char *argv[])
{
  char s3[2000]; /* We'll handle strings up to this size */
  int test = -1; /* Which test will we run? */

    /* Build a larger string */
  strcpy(s3, s3a);
  strcat(s3, s3b);
  strcat(s3, s3c);
  strcat(s3, s3d);

    /* Which test? */
  if (argc > 1)
    test = atoi(argv[1]);

  switch (test)
  {
    case 0:
      DoTest(s0);
      break;
    case 1:
      DoTest(s1);
      break;
    case 2:
      DoTest(s2);
      break;
    case 3:
      DoTest(s3);
      break;
    case 4:
      DoTest(s4);
      break;
    default:
      DoTest(s0);
      DoTest(s1);
      DoTest(s2);
      DoTest(s3);
      DoTest(s4);
      break;
  }

  return 0;
}