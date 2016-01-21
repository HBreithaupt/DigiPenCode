/*****************************************************************************/
/*!
\file parent-matrix.c
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS180
\par assignment 3
\date   6/17/2015

\brief
  Implementation of parent process to perform matrix multiplication.
  This will spawn childrent to do the labor while the parent does
  nothing but wait.


Hours spent on assignment: 10

Specific portions that gave you the most trouble: 
  - understanding how exec works when passing parameters was tricky
    examples from class showed only no paramters so it took some
    research to understand how that works
*/
/*****************************************************************************/

#include <stdio.h>   /* fopen, fscanf, fclose 			*/
#include <stdlib.h>  /* exit, malloc          			*/
#include <sys/shm.h> /* shmat,shmdt,shmctl          */
#include <unistd.h>  
#include <sys/wait.h>

/*****************************************************************************/
/*!

\brief
  Gets matrix data from a file.

\param filename
  Pointer to file to retrieve information from.
  
\param width
  Width of the matrix ( matrices will be square)

\return
  Pointer to matrix data.
*/
/*****************************************************************************/
int *get_matrix(const char *filename, int *width)
{
  int value, *matrix;
  FILE *fp;
  
    /* Open the file in text/translated mode */  
  fp = fopen(filename, "rt");
  if (!fp)
  {
    printf("Can't open file: %s\n", filename);
    exit(-1);
  }
  
    /* Read the width and allocate the matrix */
  fscanf(fp, "%d", width);
  matrix = malloc(*width * *width * sizeof(int));
  if (!matrix)
  {
    printf("Can't malloc matrix\n");
    fclose(fp);
    exit (-2);
  }
  
    /* Read the vaules and put in the matrix */
  while (!feof(fp))
  {
    int result = fscanf(fp, "%d", &value);
    if (result == -1)
      break;
    *matrix++ = value;
  }
  fclose(fp);
  
    /* Return the address of the matrix */
  return matrix - (*width * *width);
}

/*****************************************************************************/
/*!

\brief
  Prints out a matrix.

\param matrix
  Pointer to the matrix to print

\param width
  Width of the matrix

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
  Handles spawning all the children and waiting for their return from
  the labor they perform.

\param argc
  Number of arguments from cmd line
  
\param argv
  Array of strings that are the arguments from the cmd line

\return
  Normal return from main
*/
/*****************************************************************************/
int main(int argc, char **argv) 
{
  int width;       /* width of the matrix           */
  int *matrix;     /* the matrix read in            */
  int *buffer;     /* shared memory area            */
  char *child_exe; /* name of the child exe         */
  char *args[6];   /* holds arguments for exec call */
  char args_1[8];  /* buffer to use in args assignment */
  char args_2[8];  /* buffer to use in args assignment */
  char args_3[8];  /* buffer to use in args assignment */
  char args_4[8];  /* buffer to use in args assignment */
  int *children;   /* array to hold children ids     */
  int shmid;        /* shared memory id               */
  int i, j;        /* loop counters                 */
  key_t key = 123; /* key for shmget                */ 
  int shmget_size; /* # of bytes to allocate for shared memory */

  if (argc < 3)
  {
    printf("Insufficient parameters supplied\n");
    return -1;
  }

    /* The user-supplied the name of the child exe */
  child_exe = argv[2];
  
    /* read in matrix values from file */
    /* don't forget to free the memory */  
  matrix = get_matrix(argv[1], &width);
  
    /* print the matrix */
  print_matrix(matrix, width);
  
     /* calculate number of bytes to allocate */
  shmget_size = (1 + width * width * 2) * sizeof(int);
    
    /* get shared memory */
  shmid = shmget(key, shmget_size, 0600 | IPC_CREAT);
  
    /* error checking */
  if(shmid == -1)
  {
    printf("shmget failed\n");
    return 0;
  }
  
    /* attach to shared memory */
  buffer = (int *) shmat(shmid, NULL, 0);
  
    /* manually insert width into shared memory */
  buffer[0] = width;
  
    /* fill in matrix data */
  for(i = 0; i < width * width; i++)
    buffer[1 + i] = matrix[i];
  
    /* allocate array to hold children ids */
  children = malloc(width * width * sizeof(int));
  
    /* check malloc */
  if(!children)
    return 0;
  
    /* zeroth element name of child executable */
  args[0] = child_exe;
  
    /* last element null terminator */
  args[5] = 0;
  
    /* Fork a child for each matrix entry          */
    /* You'll need an array to hold the child pids */
  for (i = 0; i < width; i++)
  {
    for(j = 0; j < width; j++)
    {
        /* fork a process */
      children[i * width + j] = fork(); 
      
        /* if child */                  
      if(children[i * width + j] == 0) 
      { 
          /* first element shared memory id */
        sprintf(args_1, "%d", shmid);
        args[1] = args_1;
        
          /* child number to store result */
        sprintf(args_2, "%d", i * width + j);
        args[2] = args_2;
        
          /* row to work on */
        sprintf(args_3, "%d", i);
        args[3] = args_3;
        
          /* column to work on */
        sprintf(args_4, "%d", j);
        args[4] = args_4;
        
          /* exec child program to perform multiplication */
        execv(child_exe, args);
        
          /* if we got here exec failed */
        return 0;
      }
      
      /* parent does nothing here */
    }
  }
  
    /* wait for children */
  for(i = 0; i < width * width; i++)
  {
    int status;
    
    waitpid(children[i], &status, 0);
    
    if(WIFEXITED(status))
      continue;
  }
  
    /* print matrix from shared buffer */
  print_matrix(buffer + 1 + width * width, width);
  
    /* detach from shared memory */
  shmdt(buffer);
  
    /* delete memory block */
  shmctl(shmid, IPC_RMID, 0);
  
    /* delete children array */
  free(children);
  
    /* free matrix */
  free(matrix);
  
  return 0;
}

