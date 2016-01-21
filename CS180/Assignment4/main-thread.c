/*****************************************************************************/
/*!
\file main-thread.c
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS180
\par assignment 4
\date 6/26/15

\brief
  Implmentation to spawn threads to perform matrix multplication on a 
  square matrix;
  
  Functions include:
    - get_matrix : retrives matrix data from a file
    - print_matrix : prints out a mtrix

Hours spent on assignment: 1

Specific portions that gave you the most trouble: 
  not much any trouble, algorithms were the same just converting
  process function to work with threads insted.
*/
/*****************************************************************************/


#include <stdio.h>         /* printf, fopen, fclose, fscanf */
#include <stdlib.h>        /* exit, malloc                  */
#include <pthread.h>       /* thread create/join/exit       */
#include "matrix-thread.h" /* thread data struct, thread fn */

/*****************************************************************************/
/*!

\brief
  Gets matrix data from a text file.

\param filename
  name of the file to read from
  
\param width
  this paramter is filled in from this function, actual use is in main

\return
  pointer to the matrix
  
*/
/*****************************************************************************/
int *get_matrix(const char *filename, int *width)
{
  int value, *matrix, result;
  FILE *fp;
  
  fp = fopen(filename, "rt");
  if (!fp)
  {
    printf("Can't open file: %s\n", filename);
    exit(-1);
  }
  
  result = fscanf(fp, "%d", width);
  if (result == -1)
  {
    printf("Can't read from file: %s\n", filename);
    fclose(fp);
    exit(-1);
  }

  matrix = malloc(*width * *width * sizeof(int));
  if (!matrix)
  {
    printf("Can't malloc matrix\n");
    fclose(fp);
    exit (-2);
  }
  
  while (!feof(fp))
  {
    result = fscanf(fp, "%d", &value);
    if (result == -1)
      break;
    *matrix++ = value;
  }
  fclose(fp);
  return matrix - (*width * *width);
}


/*****************************************************************************/
/*!

\brief
  Prints out a  matrix 

\param matrix
  Matrix to print out
  
\param width
  width of the matrix 

*/
/*****************************************************************************/
void print_matrix(int *matrix, int width)
{
  int i, size = width * width;
  for (i = 0; i < size; i++)
  {
    printf("%8i", matrix[i]);
    if ( (i + 1) % width == 0)
      printf("\n");
  }
  printf("\n");
}

/*****************************************************************************/
/*!

\brief
  Main fills out matrix information and spawns threads to perform the 
  multiplication

\param argc
  number of arguments passed to main from cmd line
  
\param argv 
  Strings of the arguments passed to main from cmd line
  

\return
  normal return from main
  
*/
/*****************************************************************************/
int main(int argc, char **argv) 
{
  int i, j;
  int width;          /* width of the matrix           */
  int matsize;        /* total matrix values           */
  int *input_matrix;  /* the matrix read in            */
  int *result_matrix; /* threads will put results here */
  thread_info *threads;
  pthread_t *thread_id;
  
  if (argc < 2)
  {
    printf("Insufficient parameters supplied\n");
    return -1;
  }
  
    /* Reading the input matrix from a file into it's memory. */
  input_matrix = get_matrix(argv[1], &width);
  
    /* record square of matrix */
  matsize = width * width;
  
    /* array of structs to fill in data for threads */
  threads = malloc(sizeof(thread_info) * matsize);
  
    /* array to hold thread ids */
  thread_id = malloc(sizeof(pthread_t) * matsize);
  
    /* Printing the input matrix. */
  print_matrix(input_matrix, width);
  
    /* allocate memory for result matrix */
  result_matrix = malloc(sizeof(int) * width * width);
  
  
    /* Creating all of the other threads and supplying them with */
    /* their parameters                                          */ 
  for (i = 0; i < width; i++)
  {
    for(j = 0; j < width; j++)
    {
        /* fill in paramters of struct to use in specific thread */
      threads[i * width + j].row = i;
      threads[i * width + j].column = j;
      threads[i * width + j].width = width;
      threads[i * width + j].matrix = input_matrix;
      threads[i * width + j].result_matrix = result_matrix;
      pthread_create(&thread_id[i * width + j], NULL, 
                     matrix_multiply, &threads[i * width + j]);
    }
  }

    /* Waiting for all of the threads to finish. */
  for(i = 0; i < matsize; i++)
  {
    pthread_join(thread_id[i], NULL);
  }
    
    /* Printing the resulting squared matrix. */
  print_matrix(result_matrix, width);
  
    /* Cleaning up any memory or resources the main thread created. */
  free(input_matrix);
  free(result_matrix);
  free(thread_id);
  free(threads);
  
  return 0;
}
