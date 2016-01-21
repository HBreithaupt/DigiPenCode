/*****************************************************************************/
/*!
\file child-matrix.c
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS180
\par assignment 3
\date   6/17/2015

\brief
  Implementation of child exectuable to perform marix multiplication.

*/
/*****************************************************************************/

#include <sys/shm.h> /* shmat, shmdt          */
#include <stdlib.h>  /* exit, malloc          */

/*****************************************************************************/
/*!

\brief
  This is launched via exec from parent-matrix.c. The child will perform
  matrix multiplication on one row and column via shared memory.

\param argc
  Number of arguments given to the exectuable
  
\param argv
  Array of the arguments passed to child-matrix

\return
  Normal return from main
*/
/*****************************************************************************/
int main(int argc, char **argv)
{
  int *buffer;                    /* shared memory */
  int width;                      /* widht of matrix */
  int *row, *column;              /* arrays to hold values from matrix */
  int i;                          /* loop counter */
  int result = 0;                 /* result of multiplications */
  int shmid = atoi(argv[1]);      /* get id of shared memory */
  int row_op = atoi(argv[3]);     /* get row number to work on */
  int column_op = atoi(argv[4]);  /* get column number to work on */
  int child_num = atoi(argv[2]);  /* child num to store answer */
  
    /* if for some reason there were no arguments just return */
  if(!argc)
    return 0;
  
    /* attach to shared memory created by parent */
  buffer = (int *) shmat(shmid, NULL, 0);
  
  /*printf("child shmid is %i\n", shmid);*/
    /* record width of matrix from buffer */
  width = buffer[0];
  
    /* allocate space for arrays */
  row = malloc(width * sizeof(int));
  column = malloc(width * sizeof(int));
  
    /* fill in row array */
  for(i = 0; i < width; i++)
    row[i] = buffer[1 + width * row_op + i];
  
    /* fill in column array */
  for(i = 0; i < width; i++)
    column[i] = buffer[1 + (width * i) + column_op];
    
    /* multiply row by column and store result */
  for(i = 0; i < width; i++)
    result += row[i] * column[i];
  
    /* store result in shared memory */
  buffer[1 + (width * width) + child_num] = result;
    
    /* detach from shared memory */
  shmdt(buffer);
  
    /* free allocated arrays */
  free(row);
  free(column);
  
  return 0;
}
