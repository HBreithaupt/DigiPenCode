/******************************************************************************
filename    jumble.c
author      Haven Breithaupt
DP email    h.breithaupt@digipen.edu
course      CS120
assignment  5
due date    11/4/2014

Brief Description:
  Takes a string and encodes it with a given password and can also decode the
  encrypted string.
******************************************************************************/

#include "jumble.h" /* includes header file with functions prototypes */
#define ENCRYPT 1   /* performs addition to encrypt string */
#define DECRYPT -1  /* performs subtraction to decrypt string */

/******************************************************************************
   Function: mystrlen

Description: counts number of characters in a string

     Inputs: string - a string of characters
     
    Outputs: number of characters in the string
******************************************************************************/
int mystrlen(const unsigned char *string)
{
  int numchar = 0; /* counts the characters in the string */
  
    /* increments i while string isn't nul */
  while(*string) 
  {
    numchar++;
    string++;
  }
  
  return numchar;
}

/******************************************************************************
   Function: jumple

Description: encrypts or decrypts a string with a given number of passes and
             the password

     Inputs: string - pointer to the start of a string 
             password - pointer to first character of string 'password'
                        to encrypt/decrypt the string
             method - whether we want to encrypt or decrypt
             passes - number of times to pass over the string
     
    Outputs: n/a
******************************************************************************/
void jumble(unsigned char *string, 
            const unsigned char *password, 
            enum CODE_METHOD method, 
            int passes)
{
  int i, j;         /* loop counter */
  int operation;    /* encrypt or decrypt string */
  
    /* saves address of the first char in the string */
  unsigned char *string_start = string; 
  
    /* saves address of the first char in password */
  const unsigned char *password_start = password;
  
    /* records length of string */
  int string_length = mystrlen(string); 
  
    /* uses addition or subtraction depending on what is passed */
  if(method == ENCODE)
    operation = ENCRYPT;
  else
    operation = DECRYPT;
  
    /* algorithm for encrypting and decrypting string*/
  for(i = 0; i < passes; i++)
  {
      /* resets addresses of string and password when returning 
       * to top of loop for next pass */
    string = string_start;
    password = password_start;
    
      /* performs encryption or decryption on each char in the string */
    for(j = 0; j < string_length; j++)
    {
      *string += operation * *password;
      
      string++;
      password++;
      
        /* wraps password if string hasnt been fully iterated*/
      if(*password == 0)
        password = password_start;   
    }
  }
}

