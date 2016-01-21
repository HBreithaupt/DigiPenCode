#include "spvector.h"
#include <stdio.h>  /* printf, NULL   */
#include <stdlib.h>
#include <string.h>
#include <time.h>

int Random(int low, int high);
void test0(void);
void test1(void);
void test2(void);
void test3(void);
void test4(void);
void test5(void);
void test6(void);
void test7(void);
void test8(void);
void test9(void);
void test10(void);
void test11(void);
void test12(void);
void test13(void);
void test14(void);
void test15(void);
void test16(void);
void test17(void);
void test18(void);
void test19(void);
void test20(void);
void test21(void);
void test22(void);
void test23(void);
void test24(void);

int Random(int low, int high) { /* [ low,high ) */
  int r = rand();
  return r % (high - low ) + low;
}

void test0(void) {
  ElementNode_handle pE1=0;
  int i;
  printf("\n====== INSERTS BACK =============================\n");
  for(i=0;i<20;++i) insert_element(&pE1,3*i,i*i);
  printf("vector 1 formatted:\n");
  printf_elements(pE1,"%4d",80); printf("\n");
  printf("vector 1 raw:\n");
  print_elements(pE1); printf("\n");

  free_elements(pE1);
}

void test1(void) {
  ElementNode_handle pE2=0;
  int i;
  printf("\n====== INSERTS BACK =============================\n");

  for(i=0;i<20;++i) insert_element(&pE2,20-i,i);
  printf("vector 2 formatted:\n");
  printf_elements(pE2,"%4d",20); printf("\n");
  printf("vector 2 raw:\n");
  print_elements(pE2); printf("\n");
 
  free_elements(pE2);
}

void test2(void) {
  ElementNode_handle pE3=0;
  int i;
  printf("\n====== INSERTS MIDDLE =============================\n");
 
  for(i=0;i<20;++i) {
    if (i%2) insert_element(&pE3,i,i);
    else     insert_element(&pE3,20-i,-i);
  }
  printf("vector 3 formatted:\n");
  printf_elements(pE3,"%4d",20); printf("\n");
  printf("vector 3 raw:\n");
  print_elements(pE3); printf("\n");

  free_elements(pE3);
}

void test3(void) {
  ElementNode_handle pE2=0;
  int i;
  printf("\n====== DELETE FRONT ====================\n");
  for(i=0;i<5;++i) insert_element(&pE2,i,i+1); /*no 0s in the list*/
  printf("vector 2 formatted:\n");
  printf_elements(pE2,"%4d",5); printf("\n");
  printf("vector 2 raw:\n");
  print_elements(pE2); printf("\n");
 
  delete_element(&pE2,0);
  printf("vector 2 formatted:\n");
  printf_elements(pE2,"%4d",5); printf("\n");
  printf("vector 2 raw:\n");
  print_elements(pE2); printf("\n");

  free_elements(pE2);
}

void test4(void) {
  ElementNode_handle pE2=0;
  int i;
  printf("\n====== DELETE BACK ====================\n");
  for(i=0;i<5;++i) insert_element(&pE2,i,i+1); /*no 0s in the list*/
  printf("vector 2 formatted:\n");
  printf_elements(pE2,"%4d",5); printf("\n");
  printf("vector 2 raw:\n");
  print_elements(pE2); printf("\n");
 
  delete_element(&pE2,4);
  printf("vector 2 formatted:\n");
  printf_elements(pE2,"%4d",5); printf("\n");
  printf("vector 2 raw:\n");
  print_elements(pE2); printf("\n");

  free_elements(pE2);
}

void test5(void) {
  ElementNode_handle pE2=0;
  int i;
  printf("\n====== DELETE MIDDLE ====================\n");
  for(i=0;i<5;++i) insert_element(&pE2,i,i+1); /*no 0s in the list*/
  printf("vector 2 formatted:\n");
  printf_elements(pE2,"%4d",5); printf("\n");
  printf("vector 2 raw:\n");
  print_elements(pE2); printf("\n");
 
  delete_element(&pE2,2);
  printf("vector 2 formatted:\n");
  printf_elements(pE2,"%4d",5); printf("\n");
  printf("vector 2 raw:\n");
  print_elements(pE2); printf("\n");

  free_elements(pE2);
}


void test6(void) {
  ElementNode_handle pE1=0,pE2=0,pE3=0;
  int i;
  printf("\n==== SCALAR MULTIPLICATION =================\n");
  for(i=0;i<20;++i) insert_element(&pE1,i,i*i);
  printf("vector pE1 formatted:\n");
  printf_elements(pE1,"%4d",20); printf("\n");

  for(i=0;i<20;++i) insert_element(&pE2,40-2*i,i);
  printf("vector pE2 formatted:\n");
  printf_elements(pE2,"%4d",40); printf("\n");
 
  for(i=0;i<20;++i) {
    if (i%2) insert_element(&pE3,2*i,i);
    else     insert_element(&pE3,41-2*i,-i);
  }
  printf("vector pE3 formatted:\n");
  printf_elements(pE3,"%4d",40); printf("\n");
  printf("scalar product pE1 and pE2 = %i\n",scalar_product(pE1,pE2));
  printf("scalar product pE2 and pE3 = %i\n",scalar_product(pE2,pE3));
  printf("scalar product pE3 and pE1 = %i\n",scalar_product(pE3,pE1));
  printf("scalar product pE1 and pE1 = %i\n",scalar_product(pE1,pE1));

  free_elements(pE1);
  free_elements(pE2);
  free_elements(pE3);
}

void test7(void) {
  ElementNode_handle pE1=0,pE2=0;
  int i;
  printf("\n==== SCALAR MULTIPLICATION 2 =================\n");
  for(i=0;i<20;++i) insert_element(&pE1,1000*i,i*i);

  for(i=0;i<20;++i) insert_element(&pE2,500*i,i);
 
  printf("scalar product pE1 and pE2 = %i\n",scalar_product(pE1,pE2));
  printf("scalar product pE2 and pE1 = %i\n",scalar_product(pE2,pE1));
  printf("scalar product pE1 and pE1 = %i\n",scalar_product(pE1,pE1));

  free_elements(pE1);
  free_elements(pE2);
}

void test8(void) {
  ElementNode_handle pE1=0,pE2=0,pE3=0,pRes;
  int i;
  printf("\n==== VECTOR ADDITION =================\n");
  for(i=0;i<20;++i) insert_element(&pE1,i,i*i);
  printf("vector pE1 formatted:\n");
  printf_elements(pE1,"%4d",20); printf("\n");

  for(i=0;i<10;++i) insert_element(&pE2,20-2*i,i);
  printf("vector pE2 formatted:\n");
  printf_elements(pE2,"%4d",20); printf("\n");
 
  for(i=0;i<5;++i) {
    if (i%2) insert_element(&pE3,4*i,i);
    else     insert_element(&pE3,21-4*i,-i);
  }
  printf("vector pE3 formatted:\n");
  printf_elements(pE3,"%4d",20); printf("\n");

  pRes=add(pE1,pE2);
  printf("pE1 + pE2 = \n"); printf_elements(pRes,"%4d",20); printf("\n");
  /* printf("raw:\n"); print_elements(pRes); printf("\n"); */
  free_elements(pRes);
  pRes=add(pE2,pE3);
  printf("pE2 + pE3 = \n"); printf_elements(pRes,"%4d",20); printf("\n");
  /* printf("raw:\n"); print_elements(pRes); printf("\n"); */
  free_elements(pRes);
  pRes=add(pE3,pE1);
  printf("pE3 + pE1 = \n"); printf_elements(pRes,"%4d",20); printf("\n");
  /* printf("raw:\n"); print_elements(pRes); printf("\n"); */
  free_elements(pRes);
  pRes=add(pE1,pE3);
  printf("pE1 + pE3 = \n"); printf_elements(pRes,"%4d",20); printf("\n");
  /* printf("raw:\n"); print_elements(pRes); printf("\n"); */
  free_elements(pRes);
  free_elements(pE1);
  free_elements(pE2);
  free_elements(pE3);
}

void test9(void) {
  ElementNode_handle pE1=0,pE2=0,pRes;
  int i;
  printf("\n==== VECTOR ADDITION 2 =================\n");
  for(i=0;i<5;++i) insert_element(&pE1,2000*i,i);

  for(i=0;i<10;++i) insert_element(&pE2,1000*i,i);
 

  pRes=add(pE1,pE2);
  printf("pE1 + pE2 = \n"); 
  printf("raw:\n"); print_elements(pRes); printf("\n");
  free_elements(pRes);

  pRes=add(pE2,pE1);
  printf("pE2 + pE1 = \n"); 
  printf("raw:\n"); print_elements(pRes); printf("\n"); 
  free_elements(pRes);

  pRes=add(pE1,pE1);
  printf("pE1 + pE1 = \n");
   printf("raw:\n"); print_elements(pRes); printf("\n"); 
  free_elements(pRes);

  free_elements(pE1);
  free_elements(pE2);
}

void test10(void) {
  ElementNode_handle pE1=0,pE2=0,pRes;
  int i;
  printf("\n==== VECTOR ADDITION (ZEROES) ========\n");
  for(i=0;i<20;++i) insert_element(&pE1,i,i*i);
  printf("vector pE1 formatted:\n");
  printf_elements(pE1,"%4d",20); printf("\n");

  for(i=0;i<20;++i) insert_element(&pE2,i,-i*i);
  printf("vector pE2 formatted:\n");
  printf_elements(pE2,"%4d",20); printf("\n");
 

  pRes=add(pE1,pE2);
  printf("pE1 + pE2 = \n"); printf_elements(pRes,"%4d",20); printf("\n");
  printf("raw:\n"); print_elements(pRes); printf("\n");
  free_elements(pRes);
  pRes=add(pE2,pE1);
  printf("pE2 + pE1 = \n"); printf_elements(pRes,"%4d",20); printf("\n");
  printf("raw:\n"); print_elements(pRes); printf("\n");
  free_elements(pRes);
  free_elements(pE1);
  free_elements(pE2);
}

void test11(void) {
  ElementNode_handle pE1=0;
  int i;
  printf("\n==== TESTING FIND ========\n");
  for(i=0;i<20;i+=2) insert_element(&pE1,i,i*i);
  printf_elements(pE1,"%4d",20); printf("\n");
  printf("print vector using get - very inefficient!!!\n");
  for(i=0;i<20;++i) printf("index %i, value %i\n",i,get(pE1,i));
  free_elements(pE1);
}

void test12(void) {
  ElementNode_handle pE1=0;
  int pos=10000;
  printf("\n==== TESTING FIND 2 ========\n");
  insert_element(&pE1,pos,5);
  print_elements(pE1); printf("\n");

  printf ("value %i at position %i\n",get(pE1,pos),pos);
  free_elements(pE1);
}

void test13(void) {
  ElementNode_handle pE1=0,pE2=0,pE3=0;
  RowNode_handle pR=0; 
  int i;
  printf("\n====== INSERT ROWS FRONT =========================\n");
  for(i=0;i<5;++i) insert_element(&pE1,2*i,10*i-50);
  printf_elements(pE1,"%4d",10); printf("\n");

  for(i=0;i<20;++i) insert_element(&pE2,20-i,i);
  printf_elements(pE2,"%4d",10); printf("\n");
 
  for(i=0;i<10;++i) {
    if (i%2) insert_element(&pE3,i,i);
    else     insert_element(&pE3,10-i,-i);
  }
  
  insert_row(&pR,8,pE3);
  printf("after insert:\n"); printf_rows(pR,"%4i",10); printf("\n");
  insert_row(&pR,5,pE2);
  printf("after insert:\n"); printf_rows(pR,"%4i",10); printf("\n");
  insert_row(&pR,0,pE1);
  printf("after insert:\n"); printf_rows(pR,"%4i",10); printf("\n");

  free_rows(pR);
}

void test14(void) {
  ElementNode_handle pE1=0,pE2=0,pE3=0;
  RowNode_handle pR=0; 
  int i;
  printf("\n====== INSERT ROWS BACK =========================\n");
  for(i=0;i<5;++i) insert_element(&pE1,2*i,10*i-50);
  printf_elements(pE1,"%4d",10); printf("\n");

  for(i=0;i<20;++i) insert_element(&pE2,20-i,i);
  printf_elements(pE2,"%4d",10); printf("\n");
 
  for(i=0;i<10;++i) {
    if (i%2) insert_element(&pE3,i,i);
    else     insert_element(&pE3,10-i,-i);
  }
  
  insert_row(&pR,1,pE3);
  printf("after insert:\n"); printf_rows(pR,"%4i",10); printf("\n");
  insert_row(&pR,5,pE2);
  printf("after insert:\n"); printf_rows(pR,"%4i",10); printf("\n");
  insert_row(&pR,7,pE1);
  printf("after insert:\n"); printf_rows(pR,"%4i",10); printf("\n");

  free_rows(pR);
}

void test15(void) {
  ElementNode_handle pE1=0,pE2=0,pE3=0;
  RowNode_handle pR=0; 
  int i;
  printf("\n====== INSERT ROWS MIDDLE =========================\n");
  for(i=0;i<5;++i) insert_element(&pE1,2*i,10*i-50);
  printf_elements(pE1,"%4d",10); printf("\n");

  for(i=0;i<20;++i) insert_element(&pE2,20-i,i);
  printf_elements(pE2,"%4d",10); printf("\n");
 
  for(i=0;i<10;++i) {
    if (i%2) insert_element(&pE3,i,i);
    else     insert_element(&pE3,10-i,-i);
  }
  
  insert_row(&pR,8,pE3);
  printf("after insert:\n"); printf_rows(pR,"%4i",10); printf("\n");
  insert_row(&pR,0,pE1);
  printf("after insert:\n"); printf_rows(pR,"%4i",10); printf("\n");
  insert_row(&pR,5,pE2);
  printf("after insert:\n"); printf_rows(pR,"%4i",10); printf("\n");

  free_rows(pR);
}

void test16(void) {
  RowNode_handle pR=0; 
  int i,j;
  printf("\n====== INSERT ELEMENTS IN ROW LIST =========\n");

  for(i=0;i<15;++i) {
    for(j=0;j<10;++j) {
      insert_element2(&pR,2*i,3*j,1+7*( (i+j)%2) );
    }
  }
  printf_rows(pR,"%i",30);
  printf("\n");
  print_rows(pR);
  free_rows(pR);
}

void test17(void) {
  RowNode_handle pR=0; 
  int i,j;
  printf("\n====== INSERT ELEMENTS IN ROW LIST (WITH ZEROES) ===\n");

  for(i=0;i<30;++i) {
    for(j=0;j<30;++j) {
      insert_element2(&pR,i,j,(i+j)%2);
    }
  }
  printf_rows(pR,"%i",30); printf("\n");
  print_rows(pR); printf("\n");
  free_rows(pR);
}

void test18(void) {
  RowNode_handle pR=0; 
  int i,j;
  printf("\n== INSERT ELEMENTS IN ROW LIST (WITH ZEROES AND OVERWRITES) ==\n");

  for(i=0;i<30;++i) {
    for(j=0;j<30;++j) {
      insert_element2(&pR,i,j,(i+j)%2);
    }
  }
  printf_rows(pR,"%i",30); printf("\n");
  /* overwrite some */
  for(i=0;i<10;++i) {
    for(j=0;j<10;++j) {
      insert_element2(&pR,3*i,3*j,(3*i+2*j)%5);
    }
  }
  /* overwrite with 0 */
  for(i=0;i<30;++i) {
    for(j=0;j<30;++j) {
      if ((i+j)%8==0) insert_element2(&pR,i,j,0);
    }
  }
  printf_rows(pR,"%i",30); printf("\n");
  print_rows(pR);
  printf("\n");
  free_rows(pR);
}

void test19(void) {
	RowNode_handle pR=0; 
	int i,j=0;
	printf("\n== OVERWRITE ENTIRE ROW 0 WITH ZEROES ==\n");

	for(i=0;i<10;++i) {
		for(j=0;j<10;++j) {
			insert_element2(&pR,i,j,(i+j)%3);
		}
	}
	printf_rows(pR,"%i",10); printf("\n");

	insert_element2(&pR,3*i,3*j,(3*i+2*j)%5);

	insert_element2(&pR,0,0,0);
	insert_element2(&pR,0,1,0);
	insert_element2(&pR,0,2,0);
	insert_element2(&pR,0,3,0);
	insert_element2(&pR,0,4,0);
	insert_element2(&pR,0,5,0);
	insert_element2(&pR,0,6,0);
	insert_element2(&pR,0,7,0);
	insert_element2(&pR,0,8,0);
	insert_element2(&pR,0,9,0);

	printf_rows(pR,"%i",10); printf("\n");
	print_rows(pR);
	printf("\n");
	free_rows(pR);
}

void test20(void) {
	RowNode_handle pR=0; 
	int i,j=0;
	printf("\n== OVERWRITE ENTIRE ROW 1 WITH ZEROES ==\n");

	for(i=0;i<10;++i) {
		for(j=0;j<10;++j) {
			insert_element2(&pR,i,j,(i+j)%3);
		}
	}
	printf_rows(pR,"%i",10); printf("\n");

	insert_element2(&pR,3*i,3*j,(3*i+2*j)%5);

	insert_element2(&pR,1,0,0);
	insert_element2(&pR,1,1,0);
	insert_element2(&pR,1,2,0);
	insert_element2(&pR,1,3,0);
	insert_element2(&pR,1,4,0);
	insert_element2(&pR,1,5,0);
	insert_element2(&pR,1,6,0);
	insert_element2(&pR,1,7,0);
	insert_element2(&pR,1,8,0);
	insert_element2(&pR,1,9,0);

	printf_rows(pR,"%i",10); printf("\n");
	print_rows(pR);
	printf("\n");
	free_rows(pR);
}

void test21(void) {
	RowNode_handle pR=0; 
	int i,j=0;
	printf("\n== OVERWRITE ENTIRE ROW 9 WITH ZEROES ==\n");

	for(i=0;i<10;++i) {
		for(j=0;j<10;++j) {
			insert_element2(&pR,i,j,(i+j)%3);
		}
	}
	printf_rows(pR,"%i",10); printf("\n");

	insert_element2(&pR,3*i,3*j,(3*i+2*j)%5);

	insert_element2(&pR,9,0,0);
	insert_element2(&pR,9,1,0);
	insert_element2(&pR,9,2,0);
	insert_element2(&pR,9,3,0);
	insert_element2(&pR,9,4,0);
	insert_element2(&pR,9,5,0);
	insert_element2(&pR,9,6,0);
	insert_element2(&pR,9,7,0);
	insert_element2(&pR,9,8,0);
	insert_element2(&pR,9,9,0);

	printf_rows(pR,"%i",10); printf("\n");
	print_rows(pR);
	printf("\n");
	free_rows(pR);
}

void test22(void) {
  RowNode_handle pR=0,pR2; 
  int i,j;
  printf("\n===== TRANSPOSITION ========================\n");
  for(i=0;i<10;++i) {
    for(j=0;j<10;++j) {
      if ((i+j)%4) insert_element2(&pR,1000*i,1000*j,10*i+j);
    }
  }
  pR2 = transpose(pR);

  printf("original as list of rows\n");
  print_rows(pR);
  printf("\n");
  printf("transposed as list of rows\n");
  print_rows(pR2);
  printf("\n");

  free_rows(pR);
  free_rows(pR2);
}

void test23(void) {
  RowNode_handle pR1=0,pR2=0,pR3,pR4,pR5, pT;
  int i;
  printf("\n===== MULTIPLICATION =======================\n");
  for(i=0;i<7;++i) insert_element2(&pR1,i,i,1);
  insert_element2(&pR1,0,6,1); 
  printf("Matrix 1\n");
  printf_rows(pR1,"%i ",7); printf("\n");

  for(i=0;i<7;++i) insert_element2(&pR2,i,i,1);
  insert_element2(&pR2,0,6,1); 
  printf("Matrix 2\n");
  printf_rows(pR2,"%i ",7); printf("\n");
	
	pT = transpose(pR2);
	printf("Transpose2\n");
	printf_rows(pT, "%i ", 7);
	printf("\n");

  pR3=mult(pR1,pR2); 
  printf("Power 2\n");
  printf_rows(pR3,"%i ",7); printf("\n");

  pR4=mult(pR1,pR3); 
  printf("Power 3\n");
  printf_rows(pR4,"%i ",7); printf("\n");

  
  pR5=mult(pR4,pR4); 
  printf("Power 6\n");
  printf_rows(pR5,"%i ",7); printf("\n");
 /* 
  for(i=0;i<1;++i) {
    printf("Power %d\n",i+3);
    temp=pR3; 
    pR3=mult(pR1,pR3); 
    free(temp);
    printf_rows(pR3,"%i ",7); 
    printf("\n");
  }
 */

  free_rows(pR1);
  free_rows(pR2);
  free_rows(pR3);
  free_rows(pR4);
  free_rows(pR5);
}

void test24(void) {
  RowNode_handle pR1=0; 
  int i,j;
  printf("\n===== DETERMINANT ==========================\n");
  for(i=0;i<7;++i) {
    insert_element2(&pR1,i,i,2);
    for(j=i+1;j<7;++j) {
      insert_element2(&pR1,i,j,i+j);
    }
  }

  printf("Matrix \n");
  printf_rows(pR1,"%i ",7); printf("\n");
  printf("Determinant = %i\n",determinant(pR1,7));
  free_rows(pR1);

  pR1=0;
  for(i=0;i<5;++i) {
    for(j=0;j<5;++j) {
      int s=i+j;
      if( s==2 || s==3 || s==7 || s==8 ) insert_element2(&pR1,i,j,1);
    }
  }

  printf("Matrix \n");
  printf_rows(pR1,"%i ",5); printf("\n");
  printf("Determinant = %i\n",determinant(pR1,5));
  free_rows(pR1);
}

void (*pTests[])(void) = { 
test0, test1, test2, test3, 
test4, test5, test6, test7, test8, 
test9, test10, test11, test12, test13, 
test14, test15, test16, test17, test18, 
test19, test20, test21, test22, test23, test24}; /*extra*/

int main(int argc, char *argv[] ) {
  if (argc!=2) return 1;
  pTests[atoi(argv[1])]();
  return 0;
}
