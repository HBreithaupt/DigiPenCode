/******************************************************************************
filename    dumpit.c
author      Haven Breithaupt
DP email    h.breithaupt@digipen.edu
course      CS120
assignment  12
due date    11/19/2014

Brief Description: prints out the bytes in a file as a hexadecimal table

******************************************************************************/

#include <stdio.h>        /* sprintf */
#include <string.h>       /* strcat */
#define MAX_STR_LENGTH 75 /* max length a string can be */
#define MIN_PRINT 31      /* minimun ASCII value for printable characters */
#define MAX_PRINT 127     /* max ASCII value for printable characters */
#define COLUMNS 16        /* number of bytes to print each line */


/******************************************************************************
   Function: format

Description: formats an array of characters as a line of hexadecimal numbers

     Inputs: inbuf - an array of characters to format
             outbuf - the formated array
             count - number of characters in inbuf
             offset - value of 6-digit offset

     
    Outputs: n/a
******************************************************************************/
void format(const char* inbuf, char *outbuf, int count, int offset)
{
  int i, j;              /* loop counters */
  char next[3] = {0};    /* array for next byte */
  int char_printed = 0;  /* counter to make sure we print every column */
  
    /* put offset into outbuf */
  sprintf(outbuf, "%06X ", offset); 
  
    /* prints out each byte in hexadecimal */
  for(i = 0; i < count; i++)
  {
    sprintf(next, "%02X", (unsigned char)inbuf[i]);
    strcat(outbuf, next);
    strcat(outbuf, " ");
    char_printed++;
    
    if(char_printed == 8)
      strcat(outbuf, " ");
  }
  
    /* print whitespace in rest of the columns if count was < 16 */
  if(char_printed < COLUMNS)
  {
    for(j = 0;char_printed < COLUMNS; char_printed++, j++)
    {
      if(char_printed == 8 && j != 0)
        strcat(outbuf, " ");
        
      strcat(outbuf, "   ");
      
    }
  }
  
  strcat(outbuf, "  ");
  
    /* print out string on the right, if characters are unprintable 
     * print a . instead */
  for(j = 0; j < count; j++)
  {
    if(MIN_PRINT < inbuf[j] && inbuf[j] < MAX_PRINT)
    {
      sprintf(next, "%c", inbuf[j]);
      strcat(outbuf, next);
    }
    else
      strcat(outbuf, ".");
      
  }
}

/******************************************************************************
   Function: dumpt

Description: opens a file in binary read and calss format function above to 
             display information about the file

     Inputs: filename - a pointer to a file
     
    Outputs: n/a
******************************************************************************/
void dump(const char *filename)
{
  FILE *fp;                     /* file pointer */
  char inbuf[16] = {0};         /* buffer array, max 16 characters */
  char outbuf[MAX_STR_LENGTH];  /* formatted array */
  int length_fread;             /* number of characters actually read */
  int i, j;                     /* loop counters */
  int offset = 0;               /* offset counter */
  
  
    /* initialize file pointer */
  fp = fopen(filename, "rb");
  
  if(fp)
  {
    printf("\n");
    
      /* prints name of file as first line */
    printf("%s:\n", filename);

      /* leading white space */
    printf("%7c", ' ');

      /* prints 01 - 0F */
    for(i = 0; i < COLUMNS; i++)
    {
      if(i == 8)
        printf(" ");

      if(i == COLUMNS -1)
      {
        printf("%02X", i);
        break;
      }

      printf("%02X ", i);
    }

      /* new line after 0F isprinted */
    printf("\n");

      /* prints dashed line */
    for(j = 0; j < 74; j++)
      printf("-");

      /* new line after dashes */
    printf("\n");
    
    while(!feof(fp))
    {
      length_fread = fread(inbuf, 1, 16, fp);
      
    format(inbuf, outbuf, length_fread, offset);
      
      /* printf("\n|%i|\n", length_fread);*/
      printf("%s\n", outbuf);
      
      offset += 16;
    }
    
    fclose(fp);
  }
  else
    printf("Can't open %s for binary read.", filename);
}