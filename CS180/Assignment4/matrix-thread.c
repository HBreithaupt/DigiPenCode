/*****************************************************************************/
/*!
\file matrix-thread.c
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS180
\par assignment 4 
\date 6/26/15

\brief
  Implementation of matrix multiplication function for threads to use.
  
*/
/*****************************************************************************/

#include <stdlib.h>           /* malloc, free      */
#include "matrix-thread.h"    /* struct definition */

/*****************************************************************************/
/*!

\brief
  Performs single multplication on a row and column of matrix 
  and stores result in seperate matrix.

\param data
  Void pointer to be casted into useful information.

*/
/*****************************************************************************/
void *matrix_multiply(void *data)
{
  int i;                    /* loop counters                             */
  int *row;                 /* array to store row information            */
  int *column;              /* array to store column information         */
  int width;                /* width of array                            */
  int product = 0;          /* product of multiplication                 */
  int row_op, column_op;    /* row and column to work on for this thread */
  
    /* cast parameter to useful struct */
  thread_info *thread = (thread_info *)data;
  
    /* record width of matrix */
  width = thread->width;
  
    /* record which row and column to work on */
  row_op = thread->row;
  column_op = thread->column;
  
    /* allocate memory for row and column data from matrix */
  row = malloc(sizeof(int) * width);
  column = malloc(sizeof(int) * width);
  
    /* fill in row matrix */
  for(i = 0; i < width; i++)
    row[i] = thread->matrix[width * row_op + i];
  
    /* fill in column array */
  for(i = 0; i < width; i++)
    column[i] = thread->matrix[width * i + column_op];
  
    /* perform multiplication */
  for(i = 0; i < width; i++)
    product += row[i] * column[i];
  
    /* store result */
  thread->result_matrix[width * row_op + column_op] = product;
  
    /* free up arrays */
  free (column);
  free (row);
  
    /* return from thread */
  return NULL;
}
