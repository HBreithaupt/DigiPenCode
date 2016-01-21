/******************************************************************************
filename    tablen.c
author      Haven Breithaupt
DP email    h.breithaupt@digipen.edu
course      CS120
assignment  11
due date    11/12/2014

Brief Description:
  Makes tablen, our favorite and most important assignment to date. It counts
  the number of tabs in a program and if any lines are longer than 80 
  characters.
******************************************************************************/

#include <string.h>     /* strlen */
#include <stdio.h>      /* printf */
#define MAX_LENGTH 1000 /* max amount of characters per line */
#define TAB '\t'        /* tab character to search for */
#define NEWLINE '\n'    /* newline character */
#define MAXLINE 80      /* max amount of character you can have per line */

/******************************************************************************
   Function: findTabs

Description: finds and counts number of tabs per line in the file
             and gives a summary at the end of the file.

     Inputs: filename - a pointer to a file stream of characters
     
    Outputs: n/a
******************************************************************************/
void findTabs(const char *filename)
{
  FILE *fp;                /* file pointer */
  char buffer[MAX_LENGTH]; /* max buffer for each line */
  int line_num = 1;        /* line number counter, initialized to 1 */
  int line_tabs;           /* tabs in current line */
  int file_tabs = 0;       /* tabs in entire file */
  int i;                   /* loop counter */
  
  
    /* set pointer to open file in read mode */
  fp = fopen(filename, "r"); 
    
    /* if fp is not nul */
  if(fp)  
  {
    
      /* while not at end of file */
    while(!feof(fp))
    {    
        /* if next line isnt nul grab it and put it in buffer */
      if (fgets(buffer, MAX_LENGTH, fp))
      {
      
          /* resets tabs for this line to 0 when we start a new line */
        line_tabs = 0; 

          /* iterate through the array looking for tabs */
        for(i = 0; i < (signed)strlen(buffer); i++)
        {
            /* found a tab, increment tab counter */
          if(buffer[i] == TAB)
          {
            line_tabs++;
            file_tabs++;
          }
        }

            /* if this line has more than 0 tabs print the line */
          if(line_tabs > 0)
          {
              /* replace newline character at end with 0 */
            buffer[strlen(buffer) - 1] = 0;

              /* print the line with tabs in it */
            printf("#%3i: (tabs:%2i) |%s|\n", line_num, line_tabs, buffer);
          }

          /* increment line counter when done iterating the string */
        line_num++; 
      }
    }
    
      /* print file summary when all lines have been checked */
    if(file_tabs > 0)
      printf("*****  TABS IN USE  *****: Number of tabs in the file is %i.\n",
             file_tabs);
    
    
    
      /* close file */
    fclose(fp); 
      
  }
  else /* if file was nul print this message */
  {
    printf("Can't open %s for read.", filename);
    
  }
}

/******************************************************************************
   Function: LongLines

Description: finds lines longer than 80 characters and prints them out,
             at the end prints a summary of all the lines found to be longer
             than 80 characters

     Inputs: filename - pointer to a file stream
     
    Outputs: n/a
******************************************************************************/
static void LongLines(const char *filename)
{
  FILE *fp;                       /* file pointer */
  char buffer[MAX_LENGTH];        /* buffer for each line */
  int line_num = 1;               /* line number, starting at 1 */
  int char_this_line;             /* characters for this line */
  int total_long_lines = 0;       /* total lines longer than 80 in file */ 
  int line_num_longest = 0;       /* line number of longest line */
  
  int most_characters = MAXLINE;  /* assumes the max characters in line is 80 
                                   * for comparison */
            
    /* set pointer to open file in read mode */
  fp = fopen(filename, "r");
  
    /* if file pointer isn't nul */
  if(fp)
  {
      /* while not at end of file */
    while(!feof(fp))
    {
        /* if next line isn't nul grab it and put it in buffer */
      if (fgets(buffer, MAX_LENGTH, fp))
      {

          /* uses strlen - 1 (to not count newline at end) */
        char_this_line = (signed)strlen(buffer) - 1;
        

          /* if this line is longer than 80 characters */
        if(char_this_line > MAXLINE)
        {
            /* is this the longest line we've seen? */
          if(char_this_line > most_characters)
          {
            most_characters = char_this_line;
            line_num_longest = line_num;
          }

            /* replace newline at end with 0 */
          buffer[strlen(buffer) - 1] = 0;
          
            /* print this line if longer than 80 with all info displayed */
          printf("#%3i: (%3i) |%s|\n", line_num, char_this_line, buffer);
            
            /* increment total lines longer than 80 */
          total_long_lines++;
        }

          /* increment line number after we're done with this line */
        line_num++;
      }
    }
       /* if we have more than 0 long lines print summary message */
      if(total_long_lines > 0)
      {
        printf("***** LINE TOO LONG *****:");
        printf(" %i lines longer than 80. Longest line is %i at %i chars.\n", 
                total_long_lines, line_num_longest, most_characters);
      }
    
      /*close file when we're doen */
    fclose(fp);
  }  
}

/******************************************************************************
   Function: tablen

Description: calls two function to find tabs and long lines in a file

     Inputs: filename - apointer to a file stream
     
    Outputs: n/a
******************************************************************************/
void tablen(const char *filename)
{
    /* calls functions to find tabs */
  findTabs(filename);
  
    /* calls function to look for long lines */
  LongLines(filename);
}
