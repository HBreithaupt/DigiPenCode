#ifndef MATRIX_H
#define MATRIX_H

typedef int** Matrix;

/* allocate 2-dimentional array with the specified dimensions */
Matrix matrix_create( int num_rows, int num_columns );

/* matrix addition, assume result matrix is already allocated */
Matrix matrix_add( Matrix m1, Matrix m2, Matrix result, int num_rows, int num_columns );

/* matrix transposition, returns a new matrix, does not delete the original */
Matrix matrix_transpose( Matrix m, int num_rows, int num_columns );

/* deallocate matrix */
void   matrix_delete( Matrix m, int num_rows );

/* print */
void   matrix_print( Matrix m, int num_rows, int num_columns );

/* delete one row (index r) from matrix */
void   matrix_delete_row( Matrix m, int r, int num_rows );

/* delete one column (index c) from matrix */
void   matrix_delete_column( Matrix m, int c, int num_rows, int num_columns );


#endif
