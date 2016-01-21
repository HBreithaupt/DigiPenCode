/*****************************************************************************/
/*!
\file matrix-thread.h
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS180
\par assignment 4
\date 6/26/15

\brief
  Function prototype for threads to use and definition of struct to pass
  to threads.

*/
/*****************************************************************************/

  /*! struct to use when spawning threads */
typedef struct
{
  int row;              /*!< row to work on         */
  int column;           /*!< column to work on      */
  int width;            /*!< width of matrix        */
  int *matrix;          /*!< matrix to read from    */
  int *result_matrix;   /*!< matrix to store result */
} thread_info;


/*****************************************************************************/
/*!

\brief
  Performs single multplication on a matrix. Stores result in seperate matrix.

\param data
  Void pointer that is casted to usual information in implementation.

*/
/*****************************************************************************/
void *matrix_multiply(void *data);