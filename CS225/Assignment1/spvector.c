/*****************************************************************************/
/*!
\file        spvector.c
\author      Haven Breithaupt
\par DP email: h.breithaupt\@digipen.edu
\par Course: CS225
\par Assignment 1
\date  5/23/15

\brief
  Implementation of functions protoyped in spvector.h.
  Also includes definitions of Element Node and Row Node,
  which are hidden from interface file.
  
  
  Function list:
    Vector Functions
      - printf_elements : prints out a sparse vector (of specified dimension)
      - print_elements : prints out a sparse vector
      - print_rows : prints out a sparse matrix
      - printf_rows : prints out a sparse matrix (of specified dimension)
      - determinant : finds determinant of sparse matrix (not implemented)
      - make_node : makes an element node
      - insert_element : inserts an element node into sparse vector
      - delete_element : deletes node form sparse vector 
      - get : gets data from node at specified pos (if exists)
      - scalar_product : finds scalar product between two vectors
      - add : adds two vectors, returns a new vector
    
    Matrix Functions:
      - make_row : makes a RowNode
      - ZeroRowRemover : removes any zero'd out rows in a matrix 
                         (deletes all occurences in one call)
                         
      - insert_row : inserts a row into a matrix
      - insert_element2 : inserts an element node at specified row and column
      - find_row : retrieves a pointer to specified row
      - transpose : transposes a matrix, returns new matrix
      - mult : multiplies two matrices
      - free_rows : deallocates matrix
    
*/
/*****************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include "spvector.h"

/* definition of Node is hidden from the client (driver) so that client CANNOT
 * use INTERNALS of the Node.  this is poor-man encapsulations - hiding
 * implementation details.  The main reason for encapsulations -- if I ever
 * decide to change Node struct no client code will break. Example: I decide to
 * change "left" to "Left", all I do is change map.h and map.c, no client code
 * is effected, since clients were FORCED to use getleft(...) function, rather
 * than field name "left".  Also see typedef in map.h
 */

/*****************************************************************************/
/*!
  Definition of Element node, for use in sparse vector.
  
*/
/*****************************************************************************/
struct ElementNode {
    /* number to store */
  int    data;
  
    /* position in vector */
  int    pos;
    
    /* pointer to next node */  
  struct ElementNode* next;
};

struct RowNode {
    /* row pos in matrix */
  int pos;
  
    /* pointer to vector (columns of this row ) */
  struct ElementNode* elements;
  
    /* pointer to next row */
  struct RowNode* next;
};

typedef struct ElementNode ElementNode;
typedef struct RowNode RowNode;


/*****************************************************************************/
/*!
  
  Prints out a vector, inserts 0 for non-existent positions,
  assumes dim = length of vector, does not check for more values after
  dim.

\param p_e
  Pointer to the vector to print out.
  
\param fmt
  Format to print out each number.
  
\param dim
  Dimension of vecor (assumedly as passed from caller).

*/
/*****************************************************************************/
void printf_elements(ConstElementNode_handle p_e, char *fmt, int dim) {
  int i,last_pos=-1;
  while (p_e) {
    for (i=last_pos+1;i<p_e->pos;++i) { printf(fmt,0); }
    printf(fmt,p_e->data);
    last_pos=p_e->pos;
    p_e = p_e->next;
  }
  for (i=last_pos+1;i<dim;++i) { printf(fmt,0); }
}


/*****************************************************************************/
/*!
  
  Prints all elements in a vector, no zero.

\param p_e
  Pointer to vector to print out.

*/
/*****************************************************************************/
void print_elements(ConstElementNode_handle p_e) {
  while (p_e) {
    printf("%i at pos %i, ",p_e->data,p_e->pos);
    p_e = p_e->next;
  }
}


/*****************************************************************************/
/*!
  
  Prints out all non-zero elements in list of rows (matrix).

\param p_r
  Matrix to print out.

*/
/*****************************************************************************/
void print_rows(ConstRowNode_handle p_r) {
  while (p_r) {
    printf("row %i: ", p_r->pos);
    print_elements(p_r->elements);
    printf("\n");
    p_r = p_r->next;
  }
}


/*****************************************************************************/
/*!
  
  Prints out matrix, inserts 0 at non-existent positions.
  Assumes the number of rows and columns is dim, will not
  check for data after dim.

\param p_r
  Matrix to print out.

\param fmt
  Format to print out each element.

\param dim
  Dimension of matrix (used for rows and columns).

*/
/*****************************************************************************/
void printf_rows(ConstRowNode_handle p_r, char *fmt, int dim) {
  int i,j,last_pos=-1;
  while (p_r) {
    for (i=last_pos+1;i<p_r->pos;++i) { /* output row of 0's */
      for (j=0;j<dim;++j) printf(fmt,0); 
      printf("\n");
    }
    printf_elements(p_r->elements,fmt,dim);
    printf("\n");
    last_pos=p_r->pos;
    p_r = p_r->next;
  }
  for (i=last_pos+1;i<dim;++i) { /* output row of 0's */
    for (j=0;j<dim;++j) printf(fmt,0); 
    printf("\n");
  }
}


/*****************************************************************************/
/*!
  
  Finds determinant of matrix (NOT IMPLEMENTED).
  
\param p_r
  Matrix to use.

\param dim
  Dimension of matrix (used for rows and columns).

\return
  Determinant of the matrix.
  
*/
/*****************************************************************************/
int  determinant(ConstRowNode_handle p_r,int dim) {
  /* this is a meaningless code to get rid of "unsed argument" warnings in 
   * Borland an MS */
  int result=1;
  if (dim==0) ++result;
  if (p_r)    --result;
  return result;
}

/*/////////////////////////////
/////ELEMENT FUNCTIONS////////
/////////////////////////////*/


/*****************************************************************************/
/*!
  
  Makes a ElementNode to use in a vector.

\param data
  Data you wish to store in this node.
  
\param position
  Position in the list you want.
  
\return
  A pointer to the node created.
  
*/
/*****************************************************************************/
static ElementNode_handle make_node(int data, int position)
{
  ElementNode_handle create;
  
  create = (ElementNode_handle) malloc(sizeof(ElementNode));
  
  if(!create)
    return NULL;
    
  create->data = data;
  create->pos = position;
  create->next = 0;
  
  return create;
}


/*****************************************************************************/
/*!
  
  Inserts a node into vector. If value passed is 0 then delete node
  at pos, if it exists. If pos already occupied, update data with val.
  
\param p_e
  A pointer to a pointer to the vecotr used.
  
\param pos
  Position in the vector you want inserted.
  
\param val
  Data you want in the node being inserted.

\return
  An int based on operation. 0 if operation was successful. 1 if malloc failed.
  
*/
/*****************************************************************************/
int insert_element(ElementNode_handle * p_e,int pos,int val)
{
    /* pointer to start at head of list, another to follow behind it 
     * and one to use to insert a node */
  ElementNode_handle current = *p_e;
  ElementNode_handle previous = current, insert;
  
    /* if list doesnt exist and val isnt 0, insert node to start list */
  if(!(*p_e) && val != 0)
  {
      /* put in node straight into head pointer */
    *p_e = make_node(val, pos);
      
      /* check malloc */
    if(!p_e)
      return 1;
    
      /* successful insert */
    return 0;
  }
    /* list doesnt exist but val passed in is 0 so do nothing */
  else if (!(*p_e) && val == 0)
    return 0;
  
      /* list does exist but neet to insert infront of head */
  if(current->pos > pos && val != 0)
  {
      /* allocate node with data */
    insert = make_node(val, pos);
    
      /* check malloc */
    if(!insert)
      return 1;
    
      /* link node to previous head of list */
    insert->next = current;
    
      /* move head pointer to new head */
    *p_e = insert;
      
      /* successful insert */
    return 0;
  }
  
    /* walk list */
  while(current && current->pos < pos)
  {
    previous = current;
    current = current->next;
  }
  
    /* we reach pos, already occupied, with val passed as 0
     * remove the node */
  if(current && (current->pos == pos) && (val == 0))
  {
    delete_element(p_e, pos);
    
    return 0;
  }
  
    /* pos is already occupied and val isnt 0 so update node data */
  if(current && current->pos == pos)
  {
    current->data = val;
    
    return 0;
  }
  
  if(val == 0)
    return 0;
  
    /* allocate node */
  insert = make_node(val, pos);
  
    /* check malloc */
  if(!insert)
    return 1;
  
    /* link up the node */
  insert->next = current;
  
  previous->next = insert;
  
    /* return successful node */
  return 0;
}


/*****************************************************************************/
/*!
  
  Deletes a node in a vector, if it exists.

\param p_e
  A pointer to a pointer to the vector you wish to delete from.
  
\param pos
  Position of the node in the vector to delete.

*/
/*****************************************************************************/
void delete_element( ElementNode_handle *p_e,int pos )
{
    /* two pointers to walk list */
  ElementNode_handle current = *p_e;
  ElementNode_handle previous = current;
  
    /* validate list */
  if(!current)
    return;
  
    /* walk until the end of find the pos requested */
  while(current && current->pos != pos)
  {
    previous = current;
    current = current->next;
  }
  
    /* if current is null we reached end of list
     * therefore pos doesnt exist */
  if(!current)
    return;
  else
  {
      /* move head pointer if deleting head */
    if(current == *p_e)
      *p_e = (*p_e)->next;
    
      /* link up list */
    previous->next = current->next;
    
      /* remove node at pos requested */
    free(current);
  }
}


/*****************************************************************************/
/*!
  
  Retrieves data from a node in the list at specified position, if it exists.

\param p_e
  A const pointer to vector being used.
  
\param pos
  Position in the node to get the data from.

\return
  Returns the data of the node requested, if it exists. Returns 0 if not found.
*/
/*****************************************************************************/
int  get( ConstElementNode_handle p_e, int pos )
{
  ConstElementNode_handle pList = p_e;
  
    /* if first pos in list is > pos we are looking for
     * return a 0 */
  if(pList && pList->pos > pos)
    return 0;
  
    /* go until either we reach the end or find our position, or
     * go past position therefore its a 0 */
  while(pList && pList->pos < pos)
    pList = pList->next;
  
    /* if the pointer is null or pos 'doesnt exist' exactly in our vector
     * return 0, else return the value requested */
  if(!pList || pList->pos != pos)
    return 0;
  else
    return pList->data;
}


/*****************************************************************************/
/*!
  
  Finds the scalar product between two vectors.

\param p_e1
  Constant pointer to first list used.
  
\param p_e2
  Constant pointer to second list used.

\return
  The product of the two lists.
  
*/
/*****************************************************************************/
int scalar_product(ConstElementNode_handle p_e1, ConstElementNode_handle p_e2)
{  
    /* variable to hold positions of both pointer relative
     * to each list, and one to hold product */
  int pos1, pos2, product = 0;
  
    /* while both pointers are still valid */
  while(p_e1 && p_e2)
  {
      /* update positions */
    pos1 = p_e1->pos;
    pos2 = p_e2->pos;
    
      
    if (pos1 < pos2) /* if pos1 if before pos2 move just pos1 */
    {
      p_e1 = p_e1->next;
      continue;
    }
    else if (pos1 > pos2) /* move pos2 if pos2 is ahead of pos1 */
    {
      p_e2 = p_e2->next;
      continue;
    }
    else /* both pointers are at same positions */
    {
        /* multiply data of both lists and add it into product */
      product += p_e1->data * p_e2->data;
      
        /* move both pointers */
      p_e1 = p_e1->next;
      p_e2 = p_e2->next;
      continue;
    }
  }
  
    /* return product of thelists */
  return product;
}


/*****************************************************************************/
/*!
  
  Adds two lists together, puts sum into new list.

\param p_e1
  Constant pointer to first list being used.
  
\param p_e2
  Constant pointer to second list being used.

\return
  Pointer to the list created that is the sum of the two lists passed.
  
*/
/*****************************************************************************/
ElementNode_handle add(ConstElementNode_handle p_e1,
                       ConstElementNode_handle p_e2)
{
    /* pointers to walk lists passed in and one for later */
  ConstElementNode_handle pList1 = p_e1, pList2 = p_e2, extend = 0;
  
    /* pointer to use in new list */
  ElementNode_handle pListAdd;
  
    /* dummy head node */
  ElementNode ListAddHead;
  
    /* start at dummy head of new list */
  pListAdd = &ListAddHead;
  
    /* assign next to null, dont want garbage */
  ListAddHead.next = 0;
  
    /* while both list pointers are valid */
  while(pList1 && pList2)
  {
      /* add only list1 data if list1 pos before list2 position*/
    if (pList1->pos < pList2->pos)
    {
      pListAdd->next = make_node(pList1->data, pList1->pos);
      pListAdd = pListAdd->next;
      pList1 = pList1->next;
      continue;
    }
      /* add only list2 data if list2 pos is after list1 position*/
    else if(pList1->pos > pList2->pos)
    {
      pListAdd->next = make_node(pList2->data, pList2->pos);
      pListAdd= pListAdd->next;
      pList2 = pList2->next;
      continue;
    }
      /*bot position are the same so add tht data of both */
    else 
    {
        /* dont store 0's */
      if(pList1->data + pList2->data != 0)
      {
        pListAdd->next = make_node(pList1->data + pList2->data, pList1->pos);
        pListAdd = pListAdd->next;
      }
      
      pList1 = pList1->next;
      pList2 = pList2->next;
    }
  }
  
    /* incase one list is shorter than other might have to extend new list*/
  if(pList1)
    extend = pList1;
  else if(pList2)
    extend = pList2;
  
    /* add the rest of the longer list */
  while(extend)
  {
    pListAdd->next = make_node(extend->data, extend->pos);
    pListAdd = pListAdd->next;
    extend = extend->next;
  }
  
  
    /* return real head node of new list */
  return ListAddHead.next;
}


/*****************************************************************************/
/*!

  Deallocates a vector.

\param p_e
  vector being freed.

*/
/*****************************************************************************/
void free_elements( ElementNode_handle p_e )
{
  ElementNode_handle temp;
  
  if(!p_e)
    return;
  
  while(p_e)
  {
    temp = p_e->next;
    
    free(p_e);
    
    p_e = temp;
  }
}

/*/////////////////////////////
///////ROW FUNCTIONS///////////
/////////////////////////////*/

/*****************************************************************************/
/*!
  
  Makes a RowNode for use in other functions.

\param pos
  The row position you want in the node.

\return
  A pointer to the node created.
  
*/
/*****************************************************************************/
static RowNode_handle make_row(int pos)
{
    /* create pointer to node */
  RowNode_handle create;
  
    /* allocate node */
  create = (RowNode_handle) malloc(sizeof(RowNode));
  
    /* check malloc */
  if(!create)
    return NULL;
  
    /* assign data */
  create->pos = pos;
  
  create->next = NULL;
  
  /* purposely didnt assign elements memeber per request by header file
   * was instructed to not put null pointers in row node to columns */
  create->elements = 0;
  
    /* return the node created */
  return create;
}


/*****************************************************************************/
/*!
  
  Removes any rows with all zeros in them. Will delete all occurences in one 
  call.

\param p_r
  A pointer to a pointer to the matrix used.

*/
/*****************************************************************************/
static void ZeroRowRemover(RowNode_handle *p_r)
{
  /* function accounts for multiple row deletions in one call doxygen this */
    /* two pointers to walk the rows*/
  RowNode_handle current = *p_r, previous = current;
  
    /* iterate throu all rows */
  while(current)
  {
      /* if columns are empty need to remove this row node*/
    if(!current->elements)
    {
        /* case of deleting head
         * move head pointer to next node */
      if(current == *p_r)
        *p_r = (*p_r)->next;
      
        /* link list */
      previous->next = current->next;
      
        /* free row with all zeros in it */
      free(current);
    }
    
      /* move pointers */
    previous = current;
    current = current->next;
  }
}
  

/*****************************************************************************/
/*!
  
  Inserts a row into a list of RowNodes.

\param p_r 
  A pointer to a pointer to the list being used.

\return
  Based on operation returns 0 if successful, 0 if malloc failed.
  
*/
/*****************************************************************************/
int insert_row( RowNode_handle *p_r,int pos,ElementNode_handle p_e )
{
    /* two pointers to walk list and one to use inserting a node */
  RowNode_handle pRowCurrent = *p_r, pInsert, pRowPrevious = pRowCurrent;
  
    /* case of creating the matrix */
  if(!*p_r)
  {
      /* allocate row */
    *p_r = make_row(pos);
    
      /* check malloc */
    if(!p_r)
      return 1;
    
      /* add columns if valid */
    if(p_e)
      (*p_r)->elements  = p_e;
    
      /* return successful insert */
    return 0;
  }
  
    /* case of inserting at the front */
  if(pRowCurrent->pos > pos)
  {
      /* allocate node to insert */
    pInsert = make_row(pos);
    
      /* check malloc */
    if(!pInsert)
      return 1;
    
      /* add columns if valid */
    if(p_e)
      pInsert->elements = p_e;
    
      /* assign next to previous head row */
    pInsert->next = *p_r;
    
      /* move head pointer */
    *p_r = pInsert;
    
      /* return successful insert */
    return 0;
  }
  
    /* iterate through the rows*/
  while(pRowCurrent && pRowCurrent->pos <= pos)
  {
      /* if row already occupied return 2 */
    if(pRowCurrent->pos == pos)
      return 2;
    
      /* move pointers */
    pRowPrevious = pRowCurrent;
    pRowCurrent = pRowCurrent->next;
  }
  
  /* at this pointer need to insert between previous and current
   * pointers */
  
  
    /* allocate row */
  pInsert = make_row(pos);
  
    /* check malloc */
  if(!pInsert)
    return 1;
    
    /* add columns if valid */
  if(p_e)
    pInsert->elements = p_e;
  
    /* link up the new node */
  pInsert->next = pRowCurrent;
  pRowPrevious->next = pInsert;
  
    /* return successful insert */
  return 0;
}


/*****************************************************************************/
/*!
  
  Inserts an element at specified row, column position. Will create row
  if necessary. Follows same rules as insert_element.

\param pp_r
  A pointer to a pointer to the matrix being used.
  
\param pos_row
  Row to insert into. Will create if needed.
  
\param pos_col
  Column to insert ElementNode.
  
\param val
  Value of data variable in element node being inserted.

\return
  Based on operation returns 0 if successful, 1 if malloc failed.
  
*/
/*****************************************************************************/
int insert_element2( RowNode_handle *pp_r,int pos_row,int pos_col,int val )
{
  RowNode_handle pRow = *pp_r, pRowFind;
  
  int result;
  
    /* dummy element node pointer to use in insert row calls */
  ElementNode_handle pColumns = 0;
  
    /* if matrix doesnt exist */
  if(!pRow && val != 0)
  {
      /* make a row */
    *pp_r = make_row(pos_row);
    
      /* insert an element where desired  */
    result =  insert_element(&(*pp_r)->elements, pos_col, val);
  
      /* remove any rows that have been zero'd out */
    ZeroRowRemover(pp_r);
    
      /* return reuslt of insertion */
    return result;
  }  
  
    /* iterate through the rows */
  while(pRow && pRow->pos != pos_row)
    pRow = pRow->next;
  
    /* insert element in row if found */
  if(pRow && pRow->pos == pos_row)
  {
      /* insert element */
    result = insert_element(&pRow->elements, pos_col, val);
    
      /* remove any rows zero'd out */
    ZeroRowRemover(pp_r);
    
      /* return result of insertion */
    return result;
  }
  else /* if row not found, insert it */
  {
      /* dont create row if val desired in non-existent row is 0 */
    if(val == 0)
      return 0;
    
      /* insert a row into this matrix */
    insert_row(pp_r, pos_row, pColumns);
    
      /* get pointer to row inserted */
    pRowFind = find_row(pp_r, pos_row);
    
      /* insert element in row requested */
    result =  insert_element(&pRowFind->elements, pos_col, val);
    
      /* remove any rows that have been zero'd out */
    ZeroRowRemover(pp_r);
    
      /* return result of insertion */
    return result;
  }
}


/*****************************************************************************/
/*!

  Finds a row in a list of rows, if it exists.

\param pp_r
  A pointer to a pointer to the list being used.
  
\param pos
  The row number you're looking for.

\return
  A pointer to the row found or NULL if row doesnt exist.
  
*/
/*****************************************************************************/
RowNode_handle find_row( RowNode_handle *pp_r,int pos )
{
    /* make pointer to walk through the row */
  RowNode_handle pRow = *pp_r;
  
    /* validate row exists */
  if(!pRow)
    return NULL;
  
    /* if first row pos > pos we are looking for return null */
  if(pRow->pos > pos)
    return NULL;
  
    /* iterate through rows */
  while(pRow)
  {
      /* return pointer if we found row requested */
    if(pRow->pos == pos)
      return pRow;
    
      /* move pointer */
    pRow = pRow->next;
      
      /* if row is greated than requested stop looking */
    if(pRow->pos > pos)
      return NULL;
  }
  
    /*return null if never found */
  return NULL;
}


/*****************************************************************************/
/*!
  
  Transpose a list of rows (matrix). Stores result in newly allocated
  matrix.

\param p_r
  The matrix being transposed.

\return
  A pointer to the transposed matrix.
  
*/
/*****************************************************************************/
RowNode_handle transpose( ConstRowNode_handle p_r )
{
    /* pointer to hold transposed matrix */
  RowNode_handle transpose = 0;
  
    /* walk columns */
  ElementNode_handle columns;
  
    /* iterate entire matrix */
  while(p_r)
  {
      /* start iterating the columns */
    columns = p_r->elements;
    
    while(columns)
    {
        /* add node to transpose matrix */
      insert_element2(&transpose, columns->pos, p_r->pos, columns->data);
      
        /* move pointer */
      columns = columns->next;
    }
    
      /* move to next row */
    p_r = p_r->next;
  }
  
    /* remove any zero'd out rows */
  /*ZeroRowRemover(&transpose);*/
  
    /* return the transposed matrix */
  return transpose;
}


/*****************************************************************************/
/*!
  
  Multiplies two matrices. Stores result in newly allocated matrix.

\param p_r1
  First matrix being used.
  
\param p_r2
  Second matrix being used.

\return
  Pointer the multiplied matrix.
  
*/
/*****************************************************************************/
RowNode_handle mult( ConstRowNode_handle p_r1, ConstRowNode_handle p_r2 )
{
  RowNode_handle transpose2 = transpose(p_r2);
  
  RowNode_handle multiplication =0, p2 = transpose2;
  
  ConstElementNode_handle columns1 = 0, columns2 = 0;
  
  int product = 0;
  
  while(p_r1)
  {
    columns1 = p_r1->elements;
    p2 = transpose2;
    
    while(p2)
    {
      columns2 = p2->elements;
      
      product = scalar_product(columns1, columns2);
      
      insert_element2(&multiplication, p_r1->pos, p2->pos, product);
      
      p2 = p2->next;
    }
    
    p_r1 = p_r1->next;
  }
  
  return multiplication;
  
}


/*****************************************************************************/
/*!
  
  Deallocates a mtrix.

\param p_r
  Matrix being freed.

*/
/*****************************************************************************/
void free_rows( RowNode_handle p_r )
{
    /* pointer to the columns */
  ElementNode_handle pColumn;
  
    /* pointer to traverse the rows */
  RowNode_handle TempRow;
  
    /* validate matrix exists */
  if(!p_r)
    return;
  
    /* while rows are valid */
  while(p_r)
  {
      /* assign column pointer to start of column */
    pColumn = p_r->elements;
    
      /* delete this row */
    free_elements(pColumn);
      
      /* move to next row */
    TempRow = p_r->next;
    
      /* free current row, after columns have been freed */
    free(p_r);
    
      /* move to new current row */
    p_r = TempRow;
  }
}
