/******************************************************************************
filename    scantext.c
author      Haven Breithaupt
DP email    h.breithaupt@digipen.edu
course      CS120
assignment  6
due date    11/14/2014

Brief Description:
  Performs operations on strings such as replacing characters, calculating 
  length (strlen), counting tabs and counting words.
******************************************************************************/

#define TAB '\t'     /* tab character */
#define SPACE ' '    /* space character */
#define NEWLINE '\n' /* new line character */
#define TRUE 1       /* *string passes function test */
#define FALSE 0

/******************************************************************************
   Function: mystrlen

Description: calculates length of a string

     Inputs: string - a pointer to a string
     
    Outputs: number of characters in the string
******************************************************************************/
static int mystrlen(const char *string)
{
  int length = 0;   /* initialize length to 0 */
  
  while (*string++) /* while string !0 increment length */
    length++;

  return length;    /* returns length of the string */
}

/******************************************************************************
   Function: count_tabs

Description: counts the number of tabs in a string

     Inputs: string - a pointer to a string of characters
     
    Outputs: number of tabs found in the string
******************************************************************************/
int count_tabs(const char *string)
{ 
  int num_tabs = 0;  /* initialize tab counter to 0 */
  
    /* iterate string while it's not nul*/
  while(*string)
  {
      /* increment tabs counter if character is a tab */
    if(*string == TAB)
      num_tabs++;
    
    string++;
  }
  
  return num_tabs;   /* return number of tabs found */
}

/******************************************************************************
   Function: substitute character 

Description: looks for a certain character and replace it with a new character

     Inputs: string - a pointer to a string of characters
             old_char - the character we're looking for
             new_char - the character we want to replace old_char with
     
    Outputs: number of substitutions made
******************************************************************************/
int substitute_char(char *string, char old_char, char new_char)
{
  int substitutions = 0; /* initialze substitution counter to 0 */
  
  while(*string)
  {
      /* if character is old_char replace with new_char and increment 
       * substitutions */
    if(*string == old_char)
    {
      *string = new_char;
      substitutions++;
    }
    
    string++;            /* increment pointer to keep iterating */
  }
  
  return substitutions;   /* return number of substitutions made */
}

/******************************************************************************
   Function: calculate_lengths

Description: records string length while changing tabs characters to space 
             the size of tabsize and then prints out the string with 
             reformatted length

     Inputs: string - a pointer to a string of characters
             string_length - 
             display_length
     
    Outputs:
******************************************************************************/
void calculate_lengths(const char *string, int tabsize, int *string_length, 
                       int *display_length)
{
  *display_length = 0;               /* initialize display length to 0 */
  
  *string_length = mystrlen(string); /* grabs original length of string */
  
    /* iterates while string is not nul */
  while(*string)
  {
      /* if we encounter tab character add tab size to 
       * display length and go to next iteration */
    if(*string == TAB)
    {
      *display_length += tabsize;
      string++;
      continue;
    }
    
    *display_length += 1;            /* add one to display length */
    string++;                        /* move pointer to next character */
    
  }
}

/******************************************************************************
   Function: WhiteSpace

Description: checks if the character we're looking at is whitespace

     Inputs: string - a pointer to a character
     
    Outputs: true if it's whitespace, false if it isn't
******************************************************************************/
static int WhiteSpace(const char *string)
{
  if(*string == TAB || *string == SPACE || *string == NEWLINE)
    return TRUE;
  else
    return FALSE;
}

/******************************************************************************
   Function: NonWhiteSpace

Description: checks if a character is NOT whitespace

     Inputs: string - a pointer to a character
     
    Outputs: true is nonwhitespace, false if it is whitespace
******************************************************************************/
static int NonWhiteSpace(const char *string)
{
  if(*string != TAB || *string != SPACE || *string != NEWLINE)
    return TRUE;
  else
    return FALSE;
}

/******************************************************************************
   Function: PreviousCharacter

Description: checks to see if the previous character is white space,
             thus meaning we have come to a word

     Inputs: sring - a pointer to a character
     
    Outputs: true if previous character is whitespace, false if previous
             character is not whitespace
******************************************************************************/
static int PreviousCharacterIsWhiteSpace(const char *string)
{
  if(*(string - 1) == TAB || *(string - 1) == SPACE || 
     *(string - 1) == NEWLINE)
    return TRUE;
  else 
    return FALSE;
}

/******************************************************************************
   Function: count_words

Description: counts the number of words in a string. wordse are deliminated by 
             whitespace characters (space, tab, new line)

     Inputs: string - a pointer to a string of characters
     
    Outputs: number of words in a string
******************************************************************************/
int count_words(const char *string)
{
  int word = 0; /* counts words in string */
  int i;        /* loop counter */
    
    /* itereates over length of string */
  for(i = 0, ++string; *string; string++, i++)
  {
      /* if current character is white space */
    if(WhiteSpace(string))
     continue;
    
      /* special case for first iteration, if nonwhitespace must be a word */
    if(NonWhiteSpace(string) && i == 0)
      word += 1; 
   
      /* if current character is not whitespace and previous character is
       * white space then increment word */
    if(NonWhiteSpace(string) && PreviousCharacterIsWhiteSpace(string))
      word += 1;
  }
    
  return word; /* return number of words found */
}
