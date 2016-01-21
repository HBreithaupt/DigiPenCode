#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

void matrix_print( Matrix m, int num_rows, int num_columns ) 
{
    int i, j;
    for ( i=0; i<num_rows; ++i ) 
    {
      for ( j=0; j<num_columns; ++j ) {
          printf( "%4i ", m[i][j] );
      }
        printf( "\n" );
    }
}


Matrix matrix_create( int num_rows, int num_columns )
{
	Matrix create;
	int row_counter;
	
	create = (int **)malloc(num_rows * sizeof(int *));
	
	for(row_counter = 0; row_counter < num_rows; row_counter++)
		create[row_counter] = (int *)malloc(num_columns * sizeof(int));
	
	return create;
}

Matrix matrix_add( Matrix m1, Matrix m2, Matrix result, int num_rows, int num_columns )
{
	int i, j;
	
	for(i = 0; i < num_rows; i++)
	{
		for(j = 0; j < num_columns; j++)
			result[i][j] = m1[i][j] + m2[i][j];
	}
	
	return result;
}


Matrix matrix_transpose( Matrix m, int num_rows, int num_columns )
{
	int i, j;
	
	Matrix result;
	
	result = matrix_create(num_columns, num_rows);
	
	for(i = 0; i < num_rows; i++)
	{
		for(j = 0; j < num_columns; j++)
			result[j][i] = m[i][j];
	}
	
	return result;
}

void matrix_delete( Matrix m, int num_rows )
{
	int i;
	
	for(i = 0; i < num_rows; i++)
		free(m[i]);
	
	free(m);
}


void matrix_delete_row( Matrix m, int r, int num_rows )
{
	int i;
	
	free(m[r]);
	
	for(i = r; i < num_rows - 1; i++)
		m[i] = m[i + 1];
}

void matrix_delete_column( Matrix m, int c, int num_rows, int num_columns )
{
	int i;
	
	if(c < num_columns - 1)
	{
		for(i = 0 ; i < num_rows; i++)
			m[i][c] = m[i][c + 1];
	}
}




























