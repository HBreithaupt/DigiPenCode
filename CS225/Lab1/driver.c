#include "matrix.h"
#include <stdio.h>

void test0() {
    Matrix m1 = matrix_create( 3, 3 );
    int i,j;
    for ( i=0; i<3; ++i ) { for ( j=0; j<3; ++j ) { m1[i][j] = i+j; } }
    
    printf( "m1 =\n" );
    matrix_print( m1, 3, 3 );
    
    matrix_delete( m1, 3 );
}

void test1() {
    Matrix m1 = matrix_create( 3, 3 );
    Matrix m2 = matrix_create( 3, 3 );
    Matrix m3 = matrix_create( 3, 3 );
    int i,j;
    for ( i=0; i<3; ++i ) { for ( j=0; j<3; ++j ) { m1[i][j] = i+j; } }
    for ( i=0; i<3; ++i ) { for ( j=0; j<3; ++j ) { m2[i][j] = 5; } }
    
    printf( "m1 =\n" );
    matrix_print( m1, 3, 3 );
    printf( "m2 =\n" );
    matrix_print( m2, 3, 3 );
    
    matrix_add( m1, m2, m3, 3, 3 );
    printf( "m1 + m2 =\n" );
    matrix_print( m3, 3, 3 );
    
    matrix_delete( m1, 3 );
    matrix_delete( m2, 3 );
    matrix_delete( m3, 3 );
}

void test2() {
    Matrix m1 = matrix_create( 3, 3 );
    Matrix m1_t;
    int i,j;
    for ( i=0; i<3; ++i ) { for ( j=0; j<3; ++j ) { m1[i][j] = i+2*j; } }
    
    printf( "m1 =\n" );
    matrix_print( m1, 3, 3 );
    
    printf( "transpose m1 =\n" );
    m1_t = matrix_transpose( m1, 3, 3 );
    matrix_print( m1_t, 3, 3 );

    matrix_delete( m1, 3 );
    matrix_delete( m1_t, 3 );
}

void test3() {
    Matrix m1 = matrix_create( 3, 3 );
    int i,j;
    for ( i=0; i<3; ++i ) { for ( j=0; j<3; ++j ) { m1[i][j] = i+2*j; } }
    
    printf( "m1 =\n" );
    matrix_print( m1, 3, 3 );
    
    printf( "delete row 0 from m1 =\n" );
    matrix_delete_row( m1, 0, 3 );
    matrix_print( m1, 2, 3 );
    
    matrix_delete( m1, 2 );
}

void test4() {
    Matrix m1 = matrix_create( 3, 3 );
    int i,j;
    for ( i=0; i<3; ++i ) { for ( j=0; j<3; ++j ) { m1[i][j] = i+2*j; } }
    
    printf( "m1 =\n" );
    matrix_print( m1, 3, 3 );
    
    printf( "delete column 1 from m1 =\n" );
    matrix_delete_column( m1, 1, 3, 3 );
    matrix_print( m1, 3, 2 );
    
    matrix_delete( m1, 3 );
}

void test5() {
    Matrix m1 = matrix_create( 3, 3 );
    Matrix m1_t;
    int i,j;
    for ( i=0; i<3; ++i ) { for ( j=0; j<3; ++j ) { m1[i][j] = i+2*j; } }
    
    printf( "m1 =\n" );
    matrix_print( m1, 3, 3 );
    
    printf( "transpose m1 =\n" );
    m1_t = matrix_transpose( m1, 3, 3 );
    matrix_print( m1_t, 3, 3 );
    
    printf( "delete row 0 =\n" );
    matrix_delete_row( m1_t, 0, 3 );
    matrix_print( m1_t, 2, 3 );
    
    matrix_delete( m1, 3 );
    matrix_delete( m1_t, 2 );
}

void test6() {
    Matrix m1 = matrix_create( 3, 3 );
    Matrix m1_t;
    int i,j;
    for ( i=0; i<3; ++i ) { for ( j=0; j<3; ++j ) { m1[i][j] = 3*i-j; } }
    
    printf( "m1 =\n" );
    matrix_print( m1, 3, 3 );
    
    printf( "delete row 1 =\n" );
    matrix_delete_row( m1, 1, 3 );
    matrix_print( m1, 2, 3 );
    
    printf( "transpose =\n" );
    m1_t = matrix_transpose( m1, 2, 3 );
    matrix_print( m1_t, 3, 2 );
   
    matrix_delete( m1, 2 );
    matrix_delete( m1_t, 3 );
}

void test7() {
    Matrix m1 = matrix_create( 3, 3 );
    Matrix m1_t;
    int i,j;
    for ( i=0; i<3; ++i ) { for ( j=0; j<3; ++j ) { m1[i][j] = i+2*j; } }
    
    printf( "m1 =\n" );
    matrix_print( m1, 3, 3 );
    
    printf( "transpose m1 =\n" );
    m1_t = matrix_transpose( m1, 3, 3 );
    matrix_print( m1_t, 3, 3 );
    
    printf( "delete column 1 =\n" );
    matrix_delete_column( m1_t, 1, 3, 3 );
    matrix_print( m1_t, 3, 2 );
    
    matrix_delete( m1, 3 );
    matrix_delete( m1_t, 3 );
}

void test8() {
    Matrix m1 = matrix_create( 3, 3 );
    Matrix m1_t;
    int i,j;
    for ( i=0; i<3; ++i ) { for ( j=0; j<3; ++j ) { m1[i][j] = 3*i-j; } }
    
    printf( "m1 =\n" );
    matrix_print( m1, 3, 3 );
    
    printf( "delete column 2 =\n" );
    matrix_delete_column( m1, 2, 3, 3 );
    matrix_print( m1, 3, 2 );
    
    printf( "transpose =\n" );
    m1_t = matrix_transpose( m1, 3, 2 );
    matrix_print( m1_t, 2, 3 );
   
    matrix_delete( m1, 3 );
    matrix_delete( m1_t, 2 );
}

void test9() {
    Matrix m1 = matrix_create( 3, 3 );
    int i,j;
    for ( i=0; i<3; ++i ) { for ( j=0; j<3; ++j ) { m1[i][j] = 3*i-j; } }
    
    printf( "m1 =\n" );
    matrix_print( m1, 3, 3 );
    
    printf( "delete column 2 =\n" );
    matrix_delete_column( m1, 2, 3, 3 );
    matrix_print( m1, 3, 2 );

    printf( "delete row 1 =\n" );
    matrix_delete_row( m1, 1, 3 );
    matrix_print( m1, 2, 2 );

    printf( "delete column 1 =\n" );
    matrix_delete_column( m1, 1, 2, 2 );
    matrix_print( m1, 2, 1 );

    printf( "delete row 0 =\n" );
    matrix_delete_row( m1, 0, 2 );
    matrix_print( m1, 1, 1 );

    matrix_delete( m1, 1 );
}

void test10() {
    int dim = 5;
    Matrix m1 = matrix_create( dim, dim );
    Matrix m2;
    int i,j;
    for ( i=0; i<dim; ++i ) { for ( j=0; j<dim; ++j ) { m1[i][j] = 3*i-j; } }
    

    printf( "m1 =\n" );
    matrix_print( m1, dim, dim );
    
    while ( dim > 1 ) {
        printf( "delete row 0 =\n" );
        matrix_delete_row( m1, 0, dim );
        matrix_print( m1, dim-1, dim );

        printf( "transpose =\n" );
        m2 = matrix_transpose( m1, dim-1, dim );
        matrix_print( m2, dim, dim-1 );
        matrix_delete( m1, dim-1 );

        printf( "delete row 0 =\n" );
        matrix_delete_row( m2, 0, dim );
        matrix_print( m2, dim-1, dim-1 );

        printf( "transpose =\n" );
        m1 = matrix_transpose( m2, dim-1, dim-1 );
        matrix_print( m1, dim-1, dim-1 );
        matrix_delete( m2, dim-1 );
        --dim;
    }
   
    matrix_delete( m1, dim );
}

void test11() {
    int dim = 5;
    Matrix m1 = matrix_create( dim, dim );
    Matrix m2;
    int i,j;
    for ( i=0; i<dim; ++i ) { for ( j=0; j<dim; ++j ) { m1[i][j] = 3*i-j; } }
    

    printf( "m1 =\n" );
    matrix_print( m1, dim, dim );
    
    while ( dim > 1 ) {
        printf( "delete row %d =\n", dim-1 );
        matrix_delete_row( m1, dim-1, dim );
        matrix_print( m1, dim-1, dim );

        printf( "transpose =\n" );
        m2 = matrix_transpose( m1, dim-1, dim );
        matrix_print( m2, dim, dim-1 );
        matrix_delete( m1, dim-1 );

        printf( "delete row %d =\n", dim-1 );
        matrix_delete_row( m2, dim-1, dim );
        matrix_print( m2, dim-1, dim-1 );

        printf( "transpose =\n" );
        m1 = matrix_transpose( m2, dim-1, dim-1 );
        matrix_print( m1, dim-1, dim-1 );
        matrix_delete( m2, dim-1 );
        --dim;
    }
   
    matrix_delete( m1, dim );
}

void test_all();

void (*pTests[])() = { 
    test0,test1,test2,test3,test4,test5,test6,
    test7,test8,test9,test10,test11,
    test_all };

void test_all() {
    unsigned i;
	for (i = 0; i<sizeof(pTests)/sizeof(pTests[0])-1; ++i) 
		pTests[i]();
}


int main( int argc, char ** argv ) {
    if (argc >1) {
        int test = 0;
        sscanf(argv[1],"%i",&test);
        pTests[test]();
    }
	return 0;
}
