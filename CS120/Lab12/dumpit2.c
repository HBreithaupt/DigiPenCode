#include <stdio.h>  /* <put function names here> */
#include <string.h> /* <put function names here> */

/* Example: (This example has Unix end-of-line character: 0x0A)
 *
 *  If inbuf contains the first 16 characters from the poem.txt file and outbuf
 *  is an empty array large enough to hold the formatted string, this is how 
 *  you would call the format function:
 *   
 *     format(inbuf, outbuf, 16, 0);
 *  
 *  and this is what outbuf would contain when it returned:
 *  
 * 000000 52 6F 73 65 73 20 61 72  65 20 72 65 64 2E 0A 56   Roses are red..V
 *
 *
 *  The second 16 bytes would be formatted like this:
 *
 *     format(inbuf, outbuf, 16, 16);
 *
 *  and outbuf would look like this:
 *
 * 000010 69 6F 6C 65 74 73 20 61  72 65 20 62 6C 75 65 2E   iolets are blue.
 *
 */
 
/*******************************************************************************
   Function: format

Description: Given an array of characters, format the characters as a line of
             hexadecimal numbers, including file offset and ASCII letters. Only
             the printable ASCII characters are displayed. Non-printable 
             characters are displayed as a period. The file offset is shown
             as a hexadecimal number.

     Inputs:  inbuf - The array of characters to format.
             outbuf - The formatted array, including offset and ASCII letters. 
              count - The number of characters in the input array.
             offset - The value of the 6-digit offset.

    Outputs: None. However, the outbuf parameter has been modified for the
             client.
*******************************************************************************/
void format(const char* inbuf, char *outbuf, int count, int offset)
{
  unsigned int i, j;  /* loop variable */
  unsigned char next[3];
  
    /* e.g. 000010 */
  sprintf(outbuf, "%06X ", offset);

   /* e.g. 52 6F 73 65 73 20 61 72  65 20 72 65 64 2E 0A 56 */
  for (i = 0; i < count; i++)
  {
      /* Format each byte as a hex number using sprintf              */
    sprintf(next, "%02X", i);
      
      /* Add the hex number to the end of buffer using strcat        */  
    strcat(outbuf, next);
    
    strcat(outbuf, " ");
    /* Don't forget the extra space between the 8th and 9th number */
    if(i == 7)
      strcat(outbuf, " ");
  }
  
  strcat(outbuf, "  ");
  /* If you didn't get 16 characters, you have to add extra spaces */  
  if(i < 16)
  {
    for(;i < 16; i++)
    {
      if(i == 7)
        strcat(outbuf, " ");
      
      strcat(outbuf, "..");
      strcat(outbuf, " ");
    }
  }

  /* Using another loop, append the ASCII representation of the characters */
  for(j = 0; j < count; j++)
  {
    if(31 < inbuf[j] && inbuf[j] < 127)
    {
      sprintf(next, "%c", inbuf[j]);
      strcat(outbuf, next);
    }
    else
      strcat(outbuf, ".");
  }

}

void dump(const char *filename)
{
  FILE *infile;         /* File pointer for input         */
  char inbuf[16] = {0}; /* Read/format 16 bytes at a time */
  char outbuf[75];      /* The longest formatted string   */

    /* Open the file for read/binary, "rb" */
    /* If the file couldn't be opened, print error message and return */

    /* Print the filename to the screen followed by a colon */
    /* Print the first header line (offsets in hexadecimal) */
    /* Print the second header line (dashes)                */

    /* For each line in the file */
  while (!feof(infile))
  {
    /* Read in bytes (16 at a time) using fread     */
    /* Format bytes using the format function above */
    /* Print formatted string using printf or puts  */
  }

    /* Close the file */
}
