/******************************************************************************
filename    spellcheck.c
author      Haven Breithaupt
DP email    h.breithaupt@digipen.edu
course      CS120
assignment  7
due date    Nov 26, 2014

Brief Description:
  
******************************************************************************/
#include <string.h>      /* strlen, strcmp */
#include <stdio.h>       /* FILE                                */
#define TRUE 0           /* matching word has been found */
#define FALSE 1          /* matching word has NOT been found */
#define CHANGETOUPPER 32 /* value to add to lowercase letter to convert to 
                          * uppercase */

  /* FILE_OK, FILE_ERR_OPEN, WORD_OK, WORD_BAD, LONGEST_WORD */
#include "spellcheck.h"

/******************************************************************************
   Function: NewLineReplace

Description: replaces newline at end of string read from the dictionary file

     Inputs: string - a pointer to a string
     
    Outputs: n/a
******************************************************************************/
void NewLineReplace(char *string)
{
  string[strlen(string) - 1] = 0;  
}

/******************************************************************************
   Function: mystrupr

Description: makes a string of characters all upper case

     Inputs: string - a pointer to a character
     
    Outputs:
******************************************************************************/
char *mystrupr(char *string)
{
  int i;                              /* loop counter */
  char *first_address = string;       /* saves original pinter address */
  int stringlength = strlen(string);  /* saves length of string */
                             
    /* checks value of each character and converts to uppercase if necessary */
  for(i = 0; i < stringlength; i++, string++)
  { 
    if(*string >= 'a' && *string <= 'z')
      *string -= CHANGETOUPPER;
    else
      continue;
  }
  
  return first_address;               /* returns address of first character */
}

/******************************************************************************
   Function: info

Description: gives some information about a dictionary, how many words are in
             it and how many letters the longest and shortest words are

     Inputs: dictionary - a pointer to a file
             dinfo - a pointer to a struct
     
    Outputs: FILE_OK if the file was opened, FILE_ERR_OPEN if the file 
             couldn't be opened
******************************************************************************/
int info(const char *dictionary, struct DICTIONARY_INFO *dinfo)
{
  FILE *fp;                       /* file pointer */
  int word_length = 0;            /* length of the word we're looking at */
  char buffer[LONGEST_WORD];      /* buffer array to hold the next line */
  dinfo->shortest = LONGEST_WORD; /* set to longest word first for testing */
  dinfo->longest = 0;             /* initialize to 0 */
  dinfo->count = 0;               /* initialize to 0 */
  
  fp = fopen(dictionary, "rt");   /* initialize file pointer */
  
    /* file was opened */
  if(fp)
  {
      /* while not at end of file */
    while(!feof(fp))
    {
        /* if next line isn't nul grab it and put it in buffer */
      if(fgets(buffer, LONGEST_WORD, fp))
      {
          /* replaces newline character at the end */
        NewLineReplace(buffer); 
        
          /* gets length of the word */
        word_length = strlen(buffer); 
        
          /* test for shortest word */
        if(word_length < dinfo->shortest)
          dinfo->shortest = word_length;
        
          /* test for longest word */
        if(word_length > dinfo->longest)
          dinfo->longest = word_length;
        
          /* increment word counter after each word is read */
        dinfo->count++; 
      }  
    }
    
    fclose(fp);                   /* close the file */
    
    return FILE_OK;               /* return that the file was opened */
  }
  else
  {
    return FILE_ERR_OPEN;         /* file couldn't be opened */
  }
  
}

/******************************************************************************
   Function: spell_check

Description: when given a word, find it in a dictionary

     Inputs: diciontary - a pointer to a file 
             word - a const char pointer to a string
     
    Outputs: WORD_OK if word was found, WORD_BAD if word was not found
******************************************************************************/
int spell_check(const char *dictionary, const char *word)
{
  FILE *fp;                             /* file pointer */
  int compare_result = FALSE;           /* variable to toggle if word found */
  char file_word[LONGEST_WORD];         /* array for the string from file */
  char passed_word[LONGEST_WORD] = {0}; /* array for word passed to us */
  
  strcpy(passed_word, word);            /* copies word into our array */
  
    /* converts string to uppercase */
  passed_word[LONGEST_WORD] = *mystrupr(passed_word); 
  
  fp = fopen(dictionary, "rt");         /* initialize file pointer */
  
    /* if file pointer isn't null */
  if(fp)
  {
      /* while not at end of file */
    while(!feof(fp))
    {
        /* if next line line isn't null put it in file_word array */
      if(fgets(file_word, LONGEST_WORD, fp))
      {
          /* get rid of new line at end */
        NewLineReplace(file_word); 
        
          /* convert to uppercase */
        file_word[LONGEST_WORD] = *mystrupr(file_word);
        
          /* if first letter of dictionary word is greater than first letter
           * of passed word just stop looking */
        if(file_word[0] > passed_word[0])
          break;
        
          /* compares the passed word anf file word */
        compare_result = strcmp(file_word, passed_word); 
        
          /* if strings are the same we found a matching word so close the 
           * file and return word ok */
        if(compare_result == TRUE)
        {
          fclose(fp);
          return WORD_OK;
        }
      }
    }
    
    fclose(fp); /* close file when we're at the end if word wasn't found */
    return WORD_BAD; /* couldn't find matchinf word so return word bad */
  }
  else
  {
      /* file pointer was null so return file error */
    return FILE_ERR_OPEN; 
  }
}

/******************************************************************************
   Function: word_lengths

Description: finds number of words that are of length 1 - count 

     Inputs: dictionary - apointer to a file
             lengths - a pointer to an array to fill out
             count - word length to check up to 
     
    Outputs: the array length filled out with index value that match number of 
             words found (i.e length[1] = 10 words found)
******************************************************************************/
int word_lengths(const char *dictionary, int lengths[], int count)
{
  FILE *fp;                     /* file pointer */
  char buffer[LONGEST_WORD];    /* buffer array for the string file */
  int i;                        /* loop counter */
  int word_length = 0;          /* length of the word being looked at */
  
    /* initialize array to 0 to start with */
  for(i = 0; i < count + 1; i++)
    lengths[i] = 0;
  
  fp = fopen(dictionary, "rt"); /* initialize file pointer */
  
    /* if file pointer isn't null */
  if(fp)
  {
      /* while not at end of file */
    while(!feof(fp))
    {
        /* if next line isn't null put it in buffer */
      if(fgets(buffer, LONGEST_WORD, fp))
      {
          /* replace new line at with 0 */
        NewLineReplace(buffer); 
        
          /* find out word length */
        word_length = strlen(buffer); 
        
          /* if word length is less than count we care about it,
           * so increment corresponding array index*/
        if(word_length <= count)
          lengths[word_length]++;
      }
    }
    
      /* close file when we're done */
    fclose(fp);                 
    
      /* return that the file was found ok */
    return FILE_OK; 
  }
  else
  {
      /* return file error if pointer was null */
    return FILE_ERR_OPEN; 
  }
  
}

/******************************************************************************
   Function: words_starting_with

Description: checks words in a dictionary to see if they satar with a certain 
             letter

     Inputs: dictionary - a pointer a file 
             letter  -  a letter to check dictionary entries against
     
    Outputs: number of words that start with the letter given
******************************************************************************/
int words_starting_with(const char *dictionary, char letter)
{
  FILE *fp;                  /* file pointer */
  char buffer[LONGEST_WORD]; /* buffer array for each line */
  int words = 0;             /* word counter */
  
    /* initialize file pointer */
  fp = fopen(dictionary, "rt");
  
    /* if fle open was successful */
  if(fp)
  {
      /* while not at end of file */
    while(!feof(fp))
    {
        /* get the next line and put it in buffer */
      if(fgets(buffer, LONGEST_WORD, fp))
      {
          /* convert letter to upper case if necessary */
        if(letter >= 'a' && letter <= 'z')
          letter -= CHANGETOUPPER;
        
          /* convert string to all uppercase */
        buffer[LONGEST_WORD] = *mystrupr(buffer);
        
          /* if first letter in buffer matches letter given words++ */
        if(letter == *buffer)
          words++;
      }
    }
    fclose(fp);              /* close file whne we're done */
    
    return words;            /* return number of words we found */
  }
  else
  {
    return FILE_ERR_OPEN;    /* file couldnt be opened */
  }
}
